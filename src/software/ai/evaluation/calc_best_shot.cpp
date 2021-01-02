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
    //
    // Convert all the robots into a pair of angles that define the "bounding angles"
    // of the robot. Any ray with an angle between the first and second angle would be
    // blocked by the robot.
    std::vector<std::pair<Angle, Angle>> robot_obstacles_as_pair_of_angles;

    for (Robot robot : robot_obstacles)
    {
        Angle perpendicular_segment_angle =
            Angle::fromDegrees(90) + (robot.position() - shot_origin).orientation();

        // The angle of the ray one and two that are tangent to either side of the robot
        Angle one =
            ((robot.position() + (ROBOT_MAX_RADIUS_METERS)*Vector::createFromAngle(
                                     perpendicular_segment_angle)) -
             shot_origin)
                .orientation();
        Angle two =
            ((robot.position() - (ROBOT_MAX_RADIUS_METERS)*Vector::createFromAngle(
                                     perpendicular_segment_angle)) -
             shot_origin)
                .orientation();

        // We make sure the first angle in the pair is ahead of the second angle in the
        // counterclockwise direction
        if (one > two)
        {
            robot_obstacles_as_pair_of_angles.emplace_back(std::make_pair(one, two));
        }
        else
        {
            robot_obstacles_as_pair_of_angles.emplace_back(std::make_pair(two, one));
        }
    }

    double segment_step = goal_post.length() / goal_post_search_points;

    Segment max_segment       = Segment(goal_post.getStart(), goal_post.getStart());
    Segment current_segment   = Segment(goal_post.getStart(), goal_post.getStart());
    Vector direction = goal_post.toVector().normalize();

    bool at_least_one_blocker = false;

    for (int search_point = 0; search_point <= goal_post_search_points; ++search_point)
    {
        Point point_on_goal_post =
            goal_post.getStart() +
            (search_point * segment_step) * direction;
        Angle angle_to_point_on_goal_post =
            (point_on_goal_post - shot_origin).orientation();
        bool point_on_goal_post_blocked = false;

        // The angle pair represent the angles formed by the rays that are tangent
        // to either side of the obstacles. Any rays that are between these two 
        // bounding rays, would be blocked by the obstacle.
        for (std::pair<Angle, Angle> angle_pair : robot_obstacles_as_pair_of_angles)
        {
            if (angle_pair.first > angle_to_point_on_goal_post &&
                angle_to_point_on_goal_post > angle_pair.second)
            {
                point_on_goal_post_blocked = true;
                at_least_one_blocker       = true;
                break;
            }
        }

        // If the point_on_goal_post is blocked, we finish off the current_segment
        // by setting the end of the segment to the current point_on_goal_post. We then
        // store max(max_segment, current_segment) in max_segment. current_segment start is set
        // to the current point_on_goal_post and we continue.
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

    if (!at_least_one_blocker)
    {
        max_segment = goal_post;
    }

    if (max_segment.length() != 0)
    {
        return std::make_optional<Shot>(
            max_segment.midPoint(),
            (max_segment.getStart() - shot_origin)
                .orientation()
                .minDiff((max_segment.getEnd() - shot_origin).orientation()));
    }

    return std::nullopt;
}
