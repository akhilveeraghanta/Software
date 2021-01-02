#include "software/ai/evaluation/calc_best_shot.h"

#include "software/ai/evaluation/calc_best_shot_impl.h"
#include "software/geom/algorithms/acute_angle.h"
#include "software/geom/algorithms/multiple_segments.h"
#include "software/geom/ray.h"
#include "software/geom/algorithms/projection.h"

std::optional<Shot> calcBestShotOnGoal(const Segment &goal_post, const Point &shot_origin,
                                       const std::vector<Robot> &robot_obstacles)
{
    // Use shot evaluation function to get the best Shot
    std::vector<Circle> obs;
    for (Robot robot : robot_obstacles)
    {
        obs.push_back(Circle(robot.position(), ROBOT_MAX_RADIUS_METERS));
    }
    return calcMostOpenDirectionFromCircleObstacles(shot_origin, goal_post, obs);
}

std::optional<Shot> calcBestShotOnGoal(const Field &field, const Team &friendly_team,
                                       const Team &enemy_team, const Point &shot_origin,
                                       TeamType goal,
                                       const std::vector<Robot> &robots_to_ignore,
                                       double radius)
{
    std::vector<Robot> obstacles;
    for (const Robot &enemy_robot : enemy_team.getAllRobots())
    {
        // Only add the robot to the obstacles if it is not ignored
        if (std::count(robots_to_ignore.begin(), robots_to_ignore.end(), enemy_robot) ==
            0)
        {
            obstacles.emplace_back(enemy_robot);
        }
    }
    for (const Robot &friendly_robot : friendly_team.getAllRobots())
    {
        // Only add the robot to the obstacles if it is not ignored
        if (std::count(robots_to_ignore.begin(), robots_to_ignore.end(),
                       friendly_robot) == 0)
        {
            obstacles.emplace_back(friendly_robot);
        }
    }

    // Calculate the best_shot based on what goal we're shooting at
    if (goal == TeamType::FRIENDLY)
    {
        return calcBestShotOnGoal(
            Segment(field.friendlyGoalpostNeg(), field.friendlyGoalpostPos()),
            shot_origin, obstacles);
    }
    else
    {
        return calcBestShotOnGoal(
            Segment(field.enemyGoalpostNeg(), field.enemyGoalpostPos()), shot_origin,
            obstacles);
    }
}

std::optional<Shot> approximateBestShotOnGoal(const Segment &goal_post, const Point &shot_origin,
                                       const std::vector<Robot> &robot_obstacles)
{
    // We sweep the ray between goal_post.getStart() and goal_post.getEnd(), searching for the largest
    // segment that is unblocked. This will give us a pretty good approximation of the best shot without
    // caclulating it exactly.
    //
    // TODO: This function can be removed when calcBestShotOnGoal is more performant. 
    // https://github.com/UBC-Thunderbots/Software/issues/1788
    Angle ray_sweep_increment = Angle::fromDegrees(0.5);

    Angle best_shot_angle = Angle::zero();

    Ray sweep_start_ray = Ray(shot_origin, goal_post.getStart() - shot_origin);
    Ray sweep_end_ray = Ray(shot_origin, goal_post.getEnd() - shot_origin);

    // If the sweep_start_ray is ahead in the counter-clockwise direction of the sweep_end_ray,
    // we need to swap the start with the end ray because we do a counter-clockwise sweep.
    if((sweep_start_ray.getDirection() - sweep_end_ray.getDirection()) > Angle::fromDegrees(0))
    {
        Ray temp = sweep_end_ray;
        sweep_start_ray = sweep_end_ray;
        sweep_end_ray = sweep_start_ray;
    }

    // This is O(r*n) where r is the number of robot obstacles, and n is the number
    // of rays that fit between the start and stop sweep ray.
    for(Ray sweep_ray = sweep_start_ray; sweep_ray.getDirection() <= sweep_end_ray.getDirection(); sweep_ray.rotate(ray_sweep_increment))
    {
        for (Robot robot : robot_obstacles)
        {


        }
    }
}
