#include "software/ai/hl/stp/tactic/dribble/dribble_tactic.h"

#include <algorithm>

#include "software/ai/hl/stp/action/stop_action.h"  // TODO (#1888): remove this dependency

DribbleTactic::DribbleTactic()
    : Tactic(false,
             {RobotCapability::Move, RobotCapability::Dribble, RobotCapability::Kick}),
      fsm(),
      control_params{DribbleFSM::ControlParams{.dribble_destination       = std::nullopt,
                                               .final_dribble_orientation = std::nullopt,
                                               .allow_excessive_dribbling = false}}
{
}

void DribbleTactic::updateWorldParams(const World &world) {}

void DribbleTactic::updateControlParams(std::optional<Point> dribble_destination,
                                        std::optional<Angle> final_dribble_orientation,
                                        bool allow_excessive_dribbling)
{
    control_params.dribble_destination       = dribble_destination;
    control_params.final_dribble_orientation = final_dribble_orientation;
    control_params.allow_excessive_dribbling = allow_excessive_dribbling;
}

void DribbleTactic::calculateNextAction(ActionCoroutine::push_type &yield)
{
    auto stop_action = std::make_shared<StopAction>(false);

    do
    {
        stop_action->updateControlParams(*robot_, false);
        yield(stop_action);
    } while (!stop_action->done());
}

bool DribbleTactic::done() const
{
    return fsm.is(boost::sml::X);
}

void DribbleTactic::updateIntent(const TacticUpdate &tactic_update)
{
    fsm.process_event(DribbleFSM::Update(control_params, tactic_update));
}

void DribbleTactic::accept(TacticVisitor &visitor) const
{
    visitor.visit(*this);
}
