#include "software/ai/hl/stp/tactic/passer/passer_tactic.h"

#include "shared/constants.h"
#include "software/ai/hl/stp/action/intercept_ball_action.h"
#include "software/ai/hl/stp/action/kick_action.h"
#include "software/ai/hl/stp/action/move_action.h"
#include "software/ai/hl/stp/action/stop_action.h"
#include "software/logger/logger.h"
#include "software/world/ball.h"

PasserTactic::PasserTactic(Pass pass)
    : Tactic(false, {RobotCapability::Kick, RobotCapability::Move}),
      pass(std::move(pass)),
      fsm()
{
}

void PasserTactic::updateWorldParams(const World& world) {}

void PasserTactic::updateControlParams(const Pass& updated_pass)
{
    // Update the control parameters stored by this Tactic
    control_params.pass = updated_pass;
}

void PasserTactic::updateIntent(const TacticUpdate& tactic_update)
{
    fsm.process_event(PasserFSM::Update(control_params, tactic_update));
}

bool PasserTactic::done() const
{
    return fsm.is(boost::sml::X);
}

void PasserTactic::calculateNextAction(ActionCoroutine::push_type& yield)
{
    auto stop_action = std::make_shared<StopAction>(false);
    yield({stop_action});
}

void PasserTactic::accept(TacticVisitor& visitor) const
{
    visitor.visit(*this);
}
