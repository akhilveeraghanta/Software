#include "software/ai/passing/pass_generator.h"

#include <gtest/gtest.h>
#include <string.h>

#include "software/ai/passing/cost_function.h"
#include "software/geom/algorithms/contains.h"
#include "software/test_util/test_util.h"

class PassGeneratorTest : public testing::Test
{
   protected:
    virtual void SetUp()
    {
        pass_generator = std::make_shared<PassGenerator>(world, Point(0, 0),
                                                         PassType::ONE_TOUCH_SHOT, true);
    }

    /**
     * Wait for the pass generator to converge to a pass
     *
     * If the pass generator does not converge within `max_num_seconds`, this will
     * cause the test to fail
     *
     * @param pass_generator Modified in-place
     * @param min_score_diff The minimum difference between two iterations of the pass
     *                       generator below which we consider the generator to be
     *                       converged
     * @param max_iters The maximum number of iterations of the PassGenerator to run
     */
    static void waitForConvergence(std::shared_ptr<PassGenerator> pass_generator,
                                   double min_score_diff, int max_iters)
    {
        double curr_score = 0;
        double prev_score = 0;
        for (int i = 0; i < max_iters; i++)
        {
            prev_score = curr_score;

            auto curr_pass_and_score = pass_generator->getBestPassSoFar();
            curr_score               = curr_pass_and_score.rating;

            // Run until the pass has converged with sufficient tolerance or the given
            // time has expired, whichever comes first. We also check that the score
            // is not small, otherwise we can get "false convergence" as the
            // pass just starts to "move" towards the converged point
            if (std::abs(curr_score - prev_score) < min_score_diff)
            {
                break;
            }
        }
        EXPECT_LE(std::abs(curr_score - prev_score), min_score_diff);
    }

    World world = ::TestUtil::createBlankTestingWorld();
    std::shared_ptr<PassGenerator> pass_generator;
};

TEST_F(PassGeneratorTest, check_pass_converges)
{
    // Test that we can converge to a stable pass in a scenario where there is a
    // fairly clear best pass.
    // It is difficult to update all the timestamps in the world that the pass generator
    // could use, so we don't, and hence this test does not really test convergence
    // of pass start time.

    world.updateBall(
        Ball(BallState(Point(2, 2), Vector(0, 0)), Timestamp::fromSeconds(0)));
    Team friendly_team(Duration::fromSeconds(10));
    friendly_team.updateRobots({
        Robot(3, {1, 0}, {0.5, 0}, Angle::zero(), AngularVelocity::zero(),
              Timestamp::fromSeconds(0)),
    });
    world.updateFriendlyTeamState(friendly_team);
    Team enemy_team(Duration::fromSeconds(10));

    int count = 0;
    std::uniform_real_distribution x_distribution(-world.field().xLength() / 2,
                                                  world.field().xLength() / 2);
    std::uniform_real_distribution y_distribution(-world.field().yLength() / 2,
                                                  world.field().yLength() / 2);
    std::mt19937 random_num_gen(13);
    while (count < 100)
    {
        count++;
    enemy_team.updateRobots({
        Robot(0, world.field().enemyGoalpostNeg(), {0, 0}, Angle::zero(),
              AngularVelocity::zero(), Timestamp::fromSeconds(0)),
        Robot(1, world.field().enemyGoalpostNeg() - Vector(0.1, 0), {0, 0}, Angle::zero(),
              AngularVelocity::zero(), Timestamp::fromSeconds(0)),
        Robot(2, world.field().enemyGoalpostNeg() - Vector(0.2, 0), {0, 0}, Angle::zero(),
              AngularVelocity::zero(), Timestamp::fromSeconds(0)),
        Robot(3, world.field().enemyGoalpostPos(), {0, 0}, Angle::zero(),
              AngularVelocity::zero(), Timestamp::fromSeconds(0)),
        Robot(4, world.field().enemyGoalpostPos() - Vector(0.1, 0), {0, 0}, Angle::zero(),
              AngularVelocity::zero(), Timestamp::fromSeconds(0)),
        Robot(5, world.field().enemyGoalpostPos() - Vector(0.2, 0), {0, 0}, Angle::zero(),
              AngularVelocity::zero(), Timestamp::fromSeconds(0)),
        Robot(6, Point(x_distribution(random_num_gen), y_distribution(random_num_gen)),
              {0, 0}, Angle::zero(), AngularVelocity::zero(), Timestamp::fromSeconds(0)),
        Robot(7, Point(x_distribution(random_num_gen), y_distribution(random_num_gen)),
              {0, 0}, Angle::zero(), AngularVelocity::zero(), Timestamp::fromSeconds(0)),
        Robot(8, Point(x_distribution(random_num_gen), y_distribution(random_num_gen)),
              {0, 0}, Angle::zero(), AngularVelocity::zero(), Timestamp::fromSeconds(0)),
    });
    world.updateEnemyTeamState(enemy_team);

    pass_generator->setWorld(world);
    pass_generator->setPasserPoint(world.ball().position());

    waitForConvergence(pass_generator, 0.0015, 10);
    }

    // Find what pass we converged to
    auto [converged_pass, converged_score] = pass_generator->getBestPassSoFar();

    // Check that we keep converging to the same pass
    for (int i = 0; i < 7; i++)
    {
        auto [pass, score] = pass_generator->getBestPassSoFar();

        EXPECT_EQ(pass.passerPoint(), converged_pass.passerPoint());
        EXPECT_LE((converged_pass.receiverPoint() - pass.receiverPoint()).length(), 0.3);
        EXPECT_LE(abs(converged_pass.speed() - pass.speed()), 0.3);
        EXPECT_LE(abs((converged_pass.startTime() - pass.startTime()).toSeconds()), 0.2);
        UNUSED(score);
    }
    UNUSED(converged_score);
}

