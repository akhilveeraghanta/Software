#include "software/ai/evaluation/calc_best_shot.h"

#include "software/ai/evaluation/calc_best_shot_impl.h"
#include "software/geom/algorithms/acute_angle.h"
#include "software/geom/algorithms/intersects.h"
#include "software/geom/algorithms/multiple_segments.h"
#include "software/geom/algorithms/projection.h"
#include "software/geom/ray.h"

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

std::optional<Shot> approximateBestShotOnGoal(const Segment &goal_post,
                                              const Point &shot_origin,
                                              const std::vector<Robot> &robot_obstacles,
                                              int goal_post_search_points)
{
    // We sweep the segment between goal_post.getStart() and goal_post.getEnd(), searching
    // for the largest segment that is unblocked. This will give us a pretty good
    // approximation of the best shot without caclulating it exactly.
    //
    // TODO: This function can be removed when calcBestShotOnGoal is more performant.
    // https://github.com/UBC-Thunderbots/Software/issues/1788

    // Convert all the robots into segments, perpendicular to the vector from the
    // shot_origin to the robot position
    std::vector<Segment> robot_obstacles_as_segments;

    for (Robot robot : robot_obstacles)
    {
        Angle perpendicular_segment_angle =
            Angle::fromDegrees(90) + (robot.position() - shot_origin).orientation();

        Segment robot_as_segment =
            Segment(robot.position() + (ROBOT_MAX_RADIUS_METERS)*Vector::createFromAngle(
                                           perpendicular_segment_angle),
                    robot.position() - (ROBOT_MAX_RADIUS_METERS)*Vector::createFromAngle(
                                           perpendicular_segment_angle));

        robot_obstacles_as_segments.emplace_back(robot_as_segment);
    }

    double segment_step = goal_post.length() / goal_post_search_points;

    Segment max_segment       = Segment(goal_post.getStart(), goal_post.getStart());
    Segment current_segment   = Segment(goal_post.getStart(), goal_post.getStart());
    bool at_least_one_blocker = false;

    for (int k = 0; k <= goal_post_search_points; k++)
    {
        Point point_on_goal_post =
            goal_post.getStart() + (k * segment_step) * goal_post.toVector().normalize();
        bool point_on_goal_post_blocked = false;

        for (Segment robot_seg : robot_obstacles_as_segments)
        {
            if (intersects(robot_seg, Segment(shot_origin, point_on_goal_post)))
            {
                point_on_goal_post_blocked = true;
                at_least_one_blocker       = true;
            }
        }

        if (point_on_goal_post_blocked)
        {
            current_segment.setEnd(point_on_goal_post);

            if (current_segment.length() > max_segment.length())
            {
                max_segment = current_segment;
            }

            current_segment.setStart(point_on_goal_post);
        }
    }

    if (max_segment.length() != 0)
    {
        return std::make_optional<Shot>(
            max_segment.midPoint(),
            (max_segment.getStart() - shot_origin)
                .orientation()
                .minDiff((max_segment.getEnd() - shot_origin).orientation()));
    }

    if (!at_least_one_blocker)
    {
        return std::make_optional<Shot>(
            goal_post.midPoint(),
            (goal_post.getStart() - shot_origin)
                .orientation()
                .minDiff((goal_post.getEnd() - shot_origin).orientation()));
    }

    return std::nullopt;
}
