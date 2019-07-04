#include "ai/hl/stp/play/example_play.h"
#include "ai/hl/stp/tactic/shoot_goal_tactic.h"
#include "ai/hl/stp/play/play_factory.h"
#include "ai/hl/stp/tactic/move_tactic.h"
#include "ai/hl/stp/tactic/goalie_tactic.h"
#include "shared/constants.h"
#include "ai/hl/stp/tactic/grab_ball_tactic.h"

const std::string ExamplePlay::name = "Example Play";

std::string ExamplePlay::getName() const
{
    return ExamplePlay::name;
}

bool ExamplePlay::isApplicable(const World &world) const
{
    return false;
}

bool ExamplePlay::invariantHolds(const World &world) const
{
    return false;
}

void ExamplePlay::getNextTactics(TacticCoroutine::push_type &yield)
{
    // Create MoveTactics that will loop forever
    auto shoot_or_chip_tactic = std::make_shared<ShootGoalTactic>(
        world.field(), world.friendlyTeam(), world.enemyTeam(), world.ball(),
        Angle::ofDegrees(4), std::nullopt, false);

    auto goalie_tactic = std::make_shared<GoalieTactic>(
        world.ball(), world.field(), world.friendlyTeam(), world.enemyTeam());

    do
    {
        // The angle between each robot spaced out in a circle around the ball
        Angle angle_between_robots = Angle::full() / world.friendlyTeam().numRobots();

        // Move the robots in a circle around the ball, facing the ball
        //move_tactic_1->updateParams(world.field(), world.ball(), world.enemyTeam());
        shoot_or_chip_tactic->updateParams(world.field(), world.friendlyTeam(),
                                           world.enemyTeam(), world.ball(), Point(0,0));
        goalie_tactic->updateParams(world.ball(), world.field(), world.friendlyTeam(),
                                    world.enemyTeam());
//        move_tactic_2->updateParams(
//            world.ball().position() + Point::createFromAngle(angle_between_robots * 2),
//            (angle_between_robots * 2) + Angle::half(), 0);
//        move_tactic_3->updateParams(
//            world.ball().position() + Point::createFromAngle(angle_between_robots * 3),
//            (angle_between_robots * 3) + Angle::half(), 0);
//        move_tactic_4->updateParams(
//            world.ball().position() + Point::createFromAngle(angle_between_robots * 4),
//            (angle_between_robots * 4) + Angle::half(), 0);
//        move_tactic_5->updateParams(
//            world.ball().position() + Point::createFromAngle(angle_between_robots * 5),
//            (angle_between_robots * 5) + Angle::half(), 0);
//        move_tactic_6->updateParams(
//            world.ball().position() + Point::createFromAngle(angle_between_robots * 6),
//            (angle_between_robots * 6) + Angle::half(), 0);

        // yield the Tactics this Play wants to run, in order of priority
//        yield({move_tactic_1, move_tactic_2, move_tactic_3, move_tactic_4, move_tactic_5,
//               move_tactic_6});
        yield({goalie_tactic, shoot_or_chip_tactic});
    } while (true);
}

// Register this play in the PlayFactory
static TPlayFactory<ExamplePlay> factory;
