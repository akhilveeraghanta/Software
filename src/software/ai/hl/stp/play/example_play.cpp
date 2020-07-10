#include "software/ai/hl/stp/play/example_play.h"

#include "software/ai/hl/stp/tactic/patrol_tactic.h"
#include "software/util/design_patterns/generic_factory.h"

const std::string ExamplePlay::name = "Example Play";

std::string ExamplePlay::getName() const
{
    return ExamplePlay::name;
}

bool ExamplePlay::isApplicable(const World &world) const
{
    // This play is never applicable so it will never be chosen during gameplay
    // This play can be run for testing by using the Play override
    return false;
}

bool ExamplePlay::invariantHolds(const World &world) const
{
    return true;
}

void ExamplePlay::getNextTactics(TacticCoroutine::push_type &yield, const World &world)
{
    // Create MoveTactics that will loop forever
    std::vector<Point> patrol_point_1 = {Point(-3,-2), Point(3,2)};
    std::vector<Point> patrol_point_2 = {Point(3,2), Point(-3,-2)};
    std::vector<Point> patrol_point_3 = {Point(-3,0), Point(3,0)};
    std::vector<Point> patrol_point_4 = {Point(3,0), Point(-3,0)};
    std::vector<Point> patrol_point_5 = {Point(-3,2), Point(3,-2)};
    std::vector<Point> patrol_point_6 = {Point(3,-2), Point(-3,2)};

    auto move_tactic_1 = std::make_shared<PatrolTactic>(patrol_point_1, 0.1, Angle::fromDegrees(0.1), 2);
    auto move_tactic_2 = std::make_shared<PatrolTactic>(patrol_point_2, 0.1, Angle::fromDegrees(0.1), 2);
    auto move_tactic_3 = std::make_shared<PatrolTactic>(patrol_point_3, 0.1, Angle::fromDegrees(0.1), 2);
    auto move_tactic_4 = std::make_shared<PatrolTactic>(patrol_point_4, 0.1, Angle::fromDegrees(0.1), 2);
    auto move_tactic_5 = std::make_shared<PatrolTactic>(patrol_point_5, 0.1, Angle::fromDegrees(0.1), 2);
    auto move_tactic_6 = std::make_shared<PatrolTactic>(patrol_point_6, 0.1, Angle::fromDegrees(0.1), 2);

    // Continue to loop to demonstrate the example play indefinitely
    do
    {
        // yield the Tactics this Play wants to run, in order of priority
        // If there are fewer robots in play, robots at the end of the list will not be
        // assigned
        yield({move_tactic_1, move_tactic_2, move_tactic_3, move_tactic_4, move_tactic_5,
               move_tactic_6});
    } while (true);
}

// Register this play in the genericFactory
static TGenericFactory<std::string, Play, ExamplePlay> factory;
