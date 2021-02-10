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

    World world = ::TestUtil::createBlankTestingWorld();
    std::shared_ptr<PassGenerator> pass_generator;
};

TEST_F(PassGeneratorTest, check_pass_converges)
{
    auto t1 = std::chrono::high_resolution_clock::now();
    auto matrix = pass_generator->generatePassMatrix();

    world.updateBall(
        Ball(BallState(Point(0, 0), Vector(0, 0)), Timestamp::fromSeconds(0)));
    Team friendly_team(Duration::fromSeconds(10));
    friendly_team.updateRobots({
        Robot(6, {1, 0}, {0.5, 0}, Angle::zero(), AngularVelocity::zero(),
              Timestamp::fromSeconds(0)),
    });
    world.updateFriendlyTeamState(friendly_team);
    Team enemy_team(Duration::fromSeconds(10));
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
        Robot(6, {-1, 0}, {0, 0}, Angle::zero(), AngularVelocity::zero(),
              Timestamp::fromSeconds(0)),
        Robot(7, {-1, 0.5}, {0, 0}, Angle::zero(), AngularVelocity::zero(),
              Timestamp::fromSeconds(0)),
        Robot(8, {-1, -0.5}, {0, 0}, Angle::zero(), AngularVelocity::zero(),
              Timestamp::fromSeconds(0)),
    });
    world.updateEnemyTeamState(enemy_team);

    pass_generator = std::make_shared<PassGenerator>(world, Point(0, 0),
                                                         PassType::ONE_TOUCH_SHOT, true);
    CostMatrix rate_pass_matrix(45, 30);

    for (int x = 0; x<45; x++)
    {
        for (int y = 0; y<30; y++)
        {
            rate_pass_matrix(x, y) = pass_generator->ratePass(matrix[x][y]);
        }
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

    std::cout << duration;
    std::cout << rate_pass_matrix<<std::endl;
}
