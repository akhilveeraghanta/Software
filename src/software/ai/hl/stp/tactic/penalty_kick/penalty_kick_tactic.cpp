/**
 * Implementation of the PenaltyKickTactic
 */
#include "software/ai/hl/stp/tactic/penalty_kick/penalty_kick_tactic.h"

PenaltyKickTactic::PenaltyKickTactic()
    : Tactic(false,
             {RobotCapability::Move, RobotCapability::Dribble, RobotCapability::Kick})
{
}

void PenaltyKickTactic::updateWorldParams(const World& world) {}

void PenaltyKickTactic::updateControlParams() {}

void PenaltyKickTactic::calculateNextAction(ActionCoroutine::push_type& yield)
{
    auto stop_action = std::make_shared<StopAction>(false);

    do
    {
        stop_action->updateControlParams(*robot_, true);
        yield(stop_action);
    } while (!stop_action->done());
}

void PenaltyKickTactic::accept(TacticVisitor& visitor) const
{
    visitor.visit(*this);
}

bool PenaltyKickTactic::done() const
{
    return fsm.is(boost::sml::X);
}

void PenaltyKickTactic::updateIntent(const TacticUpdate& tactic_update)
{
    fsm.process_event(PenaltyKickTacticFSM::Update({}, tactic_update));
}
