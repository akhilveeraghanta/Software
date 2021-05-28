#include "software/ai/hl/stp/tactic/shadow_enemy/shadow_enemy_tactic.h"

#include "software/ai/hl/stp/action/stop_action.h"  // TODO (#1888): remove this dependency


ShadowEnemyTactic::ShadowEnemyTactic()
    : Tactic(false, {RobotCapability::Move, RobotCapability::Kick}),
      fsm(),
      control_params{ShadowEnemyFSM::ControlParams{.enemy_threat    = std::nullopt,
                                                   .shadow_distance = 0}}
{
}

void ShadowEnemyTactic::updateWorldParams(const World &world) {}

void ShadowEnemyTactic::updateControlParams(std::optional<EnemyThreat> enemy_threat,
                                            double shadow_distance)
{
    control_params.enemy_threat    = enemy_threat;
    control_params.shadow_distance = shadow_distance;
}

void ShadowEnemyTactic::calculateNextAction(ActionCoroutine::push_type &yield)
{
    auto stop_action = std::make_shared<StopAction>(false);

    do
    {
        stop_action->updateControlParams(*robot_, false);
        yield(stop_action);
    } while (!stop_action->done());
}

bool ShadowEnemyTactic::done() const
{
    return fsm.is(boost::sml::X);
}

void ShadowEnemyTactic::updateIntent(const TacticUpdate &tactic_update)
{
    fsm.process_event(ShadowEnemyFSM::Update(control_params, tactic_update));
}

void ShadowEnemyTactic::accept(TacticVisitor &visitor) const
{
    visitor.visit(*this);
}
