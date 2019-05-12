#include "ai/navigator/star_navigator/star_navigator.h"
#include "ai/navigator/util.h"

std::vector<std::unique_ptr<Primitive>> StarNavigator::getAssignedPrimitives(
        const World &world, const std::vector<std::unique_ptr<Intent>> &assignedIntents)
{
    this->world = world;

    auto assigned_primitives = std::vector<std::unique_ptr<Primitive>>();
    for (const auto &intent : assignedIntents)
    {
        intent->accept(*this);
        assigned_primitives.emplace_back(std::move(current_primitive));
    }

    return assigned_primitives;
}

void StarNavigator::visit(const CatchIntent &catch_intent)
{
    auto p            = std::make_unique<CatchPrimitive>(catch_intent);
    current_primitive = std::move(p);
}

void StarNavigator::visit(const ChipIntent &chip_intent)
{
    auto p            = std::make_unique<ChipPrimitive>(chip_intent);
    current_primitive = std::move(p);
}

void StarNavigator::visit(const DirectVelocityIntent &direct_velocity_intent)
{
    auto p            = std::make_unique<DirectVelocityPrimitive>(direct_velocity_intent);
    current_primitive = std::move(p);
}

void StarNavigator::visit(const DirectWheelsIntent &direct_wheels_intent)
{
    auto p            = std::make_unique<DirectWheelsPrimitive>(direct_wheels_intent);
    current_primitive = std::move(p);
}

void StarNavigator::visit(const DribbleIntent &dribble_intent)
{
    auto p            = std::make_unique<DribblePrimitive>(dribble_intent);
    current_primitive = std::move(p);
}

void StarNavigator::visit(const KickIntent &kick_intent)
{
    auto p            = std::make_unique<KickPrimitive>(kick_intent);
    current_primitive = std::move(p);
}

static double StarNavigator::place_holder_violation_func(const Point &input_point){
    return 0.0;
}

void StarNavigator::visit(const MoveIntent &move_intent)
{
    auto p            = std::make_unique<MovePrimitive>(move_intent);
    auto path_planner = std::make_unique<StraightLinePathPlanner>();

    std::function<double(const Point& p)> test_violation_func = StarNavigator::place_holder_violation_func;
    std::vector<Obstacle> no_obstacles;

    auto path_in_points = path_planner->findPath(
            this->world.friendlyTeam().getRobotById(p->getRobotId()).position(),
            p.getDestination(), no_obstacles, test_violation_func);

    auto move_primtives = convertToMovePrimitives(p->getRobotId(), 
        std::optional<std::vector<Point>> StraightLinePathPlanner::findPath(

    current_primitive = std::move(move_primtives[0]);
}

void StarNavigator::visit(const MoveSpinIntent &move_spin_intent)
{
    auto p            = std::make_unique<MoveSpinPrimitive>(move_spin_intent);
    current_primitive = std::move(p);
}

void StarNavigator::visit(const PivotIntent &pivot_intent)
{
    auto p            = std::make_unique<PivotPrimitive>(pivot_intent);
    current_primitive = std::move(p);
}

void StarNavigator::visit(const StopIntent &stop_intent)
{
    auto p            = std::make_unique<StopPrimitive>(stop_intent);
    current_primitive = std::move(p);
}
