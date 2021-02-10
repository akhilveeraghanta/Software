#include "software/ai/passing/pass_generator.h"

#include <Eigen/Dense>
#include <algorithm>
#include <numeric>

#include "software/ai/passing/cost_function.h"
#include "software/time/timestamp.h"
#include "software/ai/passing/pass_generator.h"

static CostMatrix pass_shoot_score;
static CostMatrix rate_pass_shoot_score;
static CostMatrix calculate_intercept_risk;
static CostMatrix rate_pass_friendly_capability;
static CostMatrix static_position_quality;

PassGenerator::PassGenerator(const World& world, const Point& passer_point,
                             const PassType& pass_type, bool running_deterministically)
    : world(world),
      optimizer(optimizer_param_weights),
      passer_point(passer_point),
      // We initialize the random number generator with a specific value to
      // allow generated passes to be deterministic. The value used here has
      // no special meaning.
      random_num_gen(13),
      pass_type(pass_type)
{
}

PassWithRating PassGenerator::getBestPassSoFar()
{
    auto pass = updateAndOptimizeAndPrunePasses();
    return PassWithRating{std::move(pass), ratePass(pass)};
}

Pass PassGenerator::updateAndOptimizeAndPrunePasses()
{
    PassMatrix pass_matrix = generatePassMatrix();
    return Pass(Point(0,0), Point(0,0), 10.0, Timestamp::fromSeconds(1));
}

void PassGenerator::optimizePasses()
{
    // The objective function we minimize in gradient descent to improve each pass
    // that we're optimizing
    const auto objective_function =
        [this](const std::array<double, NUM_PARAMS_TO_OPTIMIZE>& pass_array) {
            try
            {
                Pass pass = convertArrayToPass(pass_array);
                return ratePass(pass);
            }
            catch (std::invalid_argument& e)
            {
                return 0.0;
            }
        };

    // Run gradient descent to optimize the passes to for the requested number
    // of iterations
    // NOTE: Parallelizing this `for` loop would probably be safe and potentially more
    //       performant
    std::vector<Pass> updated_passes;
    for (Pass& pass : passes_to_optimize)
    {
        auto pass_array =
            optimizer.maximize(objective_function, convertPassToArray(pass),
                               DynamicParameters->getAiConfig()
                                   ->getPassingConfig()
                                   ->getNumberOfGradientDescentStepsPerIter()
                                   ->value());
        try
        {
            updated_passes.emplace_back(convertArrayToPass(pass_array));
        }
        catch (std::invalid_argument& e)
        {
            // Sometimes the gradient descent algorithm could return an invalid pass, if
            // so, we can just ignore it and carry on
        }
    }
    passes_to_optimize = updated_passes;
}

void PassGenerator::pruneAndReplacePasses()
{
    // Sort the passes by decreasing quality
    std::sort(passes_to_optimize.begin(), passes_to_optimize.end(),
              [this](Pass p1, Pass p2) { return comparePassQuality(p1, p2); });

    // Merge Passes That Are Similar
    // We start by assuming that the most similar passes will be right beside each other,
    // then iterate over the entire list, building a new list as we go by only adding
    // elements when they are dissimilar enough from the last element we added
    // NOTE: This flips the passes so they are sorted by increasing quality
    passes_to_optimize = std::accumulate(
        passes_to_optimize.begin(), passes_to_optimize.end(), std::vector<Pass>(),
        [this](std::vector<Pass>& passes, Pass curr_pass) {
            // Check if we have no passes, or if this pass is too similar to the
            // last pass we added to the list
            if (passes.empty() || !passesEqual(curr_pass, passes.back()))
            {
                passes.emplace_back(curr_pass);
            }
            return passes;
        });

    // Replace the least promising passes
    passes_to_optimize.erase(
        passes_to_optimize.begin() + getNumPassesToKeepAfterPruning(),
        passes_to_optimize.end());

    // Generate new passes to replace the ones we just removed
    int num_new_passes =
        getNumPassesToOptimize() - static_cast<int>(passes_to_optimize.size());
    if (num_new_passes > 0)
    {
        //std::vector<Pass> new_passes = generatePasses(num_new_passes);
        // Append our newly generated passes to replace the passes we just removed
        //passes_to_optimize.insert(passes_to_optimize.end(), new_passes.begin(),
                                  //new_passes.end());
    }
}

unsigned int PassGenerator::getNumPassesToKeepAfterPruning()
{
    // We want to use the parameter value for this, but clamp it so that it is
    // <= the number of passes we're optimizing
    return std::min(static_cast<unsigned int>(DynamicParameters->getAiConfig()
                                                  ->getPassingConfig()
                                                  ->getNumPassesToKeepAfterPruning()
                                                  ->value()),
                    getNumPassesToOptimize());
}

unsigned int PassGenerator::getNumPassesToOptimize()
{
    // We want to use the parameter value for this, but clamp it so that it is
    // >= 1 so we are always optimizing at least one pass
    return std::max(static_cast<unsigned int>(DynamicParameters->getAiConfig()
                                                  ->getPassingConfig()
                                                  ->getNumPassesToOptimize()
                                                  ->value()),
                    static_cast<unsigned int>(1));
}

double PassGenerator::ratePass(const Pass& pass)
{
    double rating = 0;
    try
    {
        rating = ::ratePass(world, pass, pass_type);
    }
    catch (std::invalid_argument& e)
    {
        // If the pass is invalid, just rate it as poorly as possible
        rating = 0;
    }

    return rating;
}

PassMatrix PassGenerator::generatePassMatrix()
{
    std::uniform_real_distribution x_distribution(-world.field().xLength() / 2,
                                                  world.field().xLength() / 2);
    std::uniform_real_distribution y_distribution(-world.field().yLength() / 2,
                                                  world.field().yLength() / 2);

    double curr_time             = world.getMostRecentTimestamp().toSeconds();
    double min_start_time_offset = DynamicParameters->getAiConfig()
                                       ->getPassingConfig()
                                       ->getMinTimeOffsetForPassSeconds()
                                       ->value();
    double max_start_time_offset = DynamicParameters->getAiConfig()
                                       ->getPassingConfig()
                                       ->getMaxTimeOffsetForPassSeconds()
                                       ->value();
    std::uniform_real_distribution start_time_distribution(
        curr_time + min_start_time_offset, curr_time + max_start_time_offset);
    std::uniform_real_distribution speed_distribution(DynamicParameters->getAiConfig()
                                                          ->getPassingConfig()
                                                          ->getMinPassSpeedMPerS()
                                                          ->value(),
                                                      DynamicParameters->getAiConfig()
                                                          ->getPassingConfig()
                                                          ->getMaxPassSpeedMPerS()
                                                          ->value());
    PassMatrix pass_matrix;

    for (unsigned x = 0; x < 45; x++)
    {
        for (unsigned y = 0; y < 30; y++)
        {
            Point receiver_point(x_distribution(random_num_gen),
                                 y_distribution(random_num_gen));
            Timestamp start_time =
                Timestamp::fromSeconds(start_time_distribution(random_num_gen));
            double pass_speed = speed_distribution(random_num_gen);

            Pass p(passer_point, receiver_point, pass_speed, start_time);
            pass_matrix(x, y) = p;
        }
    }

    return pass_matrix;
}

bool PassGenerator::comparePassQuality(const Pass& pass1, const Pass& pass2)
{
    return ratePass(pass1) > ratePass(pass2);
}

bool PassGenerator::passesEqual(Pass pass1, Pass pass2)
{
    double max_position_difference_meters =
        DynamicParameters->getAiConfig()
            ->getPassingConfig()
            ->getPassEqualityMaxPositionDifferenceMeters()
            ->value();
    double max_time_difference_seconds =
        DynamicParameters->getAiConfig()
            ->getPassingConfig()
            ->getPassEqualityMaxStartTimeDifferenceSeconds()
            ->value();
    double max_speed_difference = DynamicParameters->getAiConfig()
                                      ->getPassingConfig()
                                      ->getPassEqualityMaxSpeedDifferenceMetersPerSecond()
                                      ->value();

    double receiver_position_difference =
        (pass1.receiverPoint() - pass2.receiverPoint()).length();
    double passer_position_difference =
        (pass1.passerPoint() - pass2.passerPoint()).length();
    double time_difference  = (pass1.startTime() - pass2.startTime()).toSeconds();
    double speed_difference = pass1.speed() - pass2.speed();

    return std::abs(receiver_position_difference) < max_position_difference_meters &&
           std::abs(passer_position_difference) < max_position_difference_meters &&
           std::abs(time_difference) < max_time_difference_seconds &&
           std::abs(speed_difference) < max_speed_difference;
}

std::array<double, PassGenerator::NUM_PARAMS_TO_OPTIMIZE>
PassGenerator::convertPassToArray(const Pass& pass)
{
    return {pass.receiverPoint().x(), pass.receiverPoint().y(), pass.speed(),
            pass.startTime().toSeconds()};
}

Pass PassGenerator::convertArrayToPass(
    const std::array<double, PassGenerator::NUM_PARAMS_TO_OPTIMIZE>& array)
{
    // Clamp the time to be >= 0, otherwise the TimeStamp will throw an exception
    double time_offset_seconds = std::max(0.0, array.at(3));

    return Pass(passer_point, Point(array.at(0), array.at(1)), array.at(2),
                Timestamp::fromSeconds(time_offset_seconds));
}
