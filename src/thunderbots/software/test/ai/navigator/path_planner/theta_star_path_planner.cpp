#include "ai/navigator/path_planner/theta_star_path_planner.h"

#include <gtest/gtest.h>

#include "../shared/constants.h"
#include "geom/point.h"
#include "test/test_util/test_util.h"

TEST(TestThetaStarPathPlanner, test_theta_star_path_planner)
{
    Field field = ::Test::TestUtil::createSSLDivBField();
    Ball ball   = Ball({0, 0}, {0, 0}, Timestamp::fromSeconds(5));
    Point start{0, 0}, dest{1, 1};

    std::vector<Obstacle> obstacles = std::vector<Obstacle>();

    Timestamp current_time = Timestamp::fromSeconds(123);
    Robot robot = Robot(3, Point(0.0, 0.0), Vector(0.0, 0.0), Angle::ofRadians(2.2),
                        AngularVelocity::ofRadians(-0.6), current_time);
    obstacles.push_back(Obstacle::createRobotObstacleWithScalingParams(robot, 1.0, 1.0));

    std::unique_ptr<PathPlanner> planner =
        std::make_unique<ThetaStarPathPlanner>(field, ball, obstacles);

    PathPlanner::ViolationFunction vf = [](const Point& point) { return 0; };

    auto path_points = *planner->findPath(start, dest, obstacles, vf);
    EXPECT_EQ(path_points[0], start);
    EXPECT_EQ(path_points[1], dest);
}

int main(int argc, char** argv)
{
    std::cout << argv[0] << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
