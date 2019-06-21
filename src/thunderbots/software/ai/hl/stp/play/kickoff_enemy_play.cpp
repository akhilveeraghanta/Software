#include "ai/hl/stp/play/kickoff_enemy_play.h"

#include "ai/hl/stp/evaluation/enemy_threat.h"
#include "ai/hl/stp/evaluation/possession.h"
#include "ai/hl/stp/play/play_factory.h"
#include "ai/hl/stp/tactic/move_tactic.h"
#include "ai/hl/stp/tactic/shadow_kickoff_tactic.h"
#include "shared/constants.h"

const std::string KickoffEnemyPlay::name = "KickoffEnemy Play";

std::string KickoffEnemyPlay::getName() const
{
    return KickoffEnemyPlay::name;
}

bool KickoffEnemyPlay::isApplicable(const World &world) const
{
    return true;
}

bool KickoffEnemyPlay::invariantHolds(const World &world) const
{
    return true;
}

void KickoffEnemyPlay::getNextTactics(TacticCoroutine::push_type &yield)
{
    // TODO: This needs to be a goalie tactic
    auto lone_goalie_tactic_0 = std::make_shared<MoveTactic>(true);

    // 3 robots assigned to shadow enemies. Other robots will be assigned positions
    // on the feild to be evenly spread out
    std::vector<std::shared_ptr<ShadowKickoffTactic>> shadow_kickoff_tactics = {
        std::make_shared<ShadowKickoffTactic>(world.field(), true),
        std::make_shared<ShadowKickoffTactic>(world.field(), true),
        std::make_shared<ShadowKickoffTactic>(world.field(), true),
    };

    // these positions are picked according to the following slide
    // https://images.slideplayer.com/32/9922349/slides/slide_2.jpg
    // since we only have 6 robots at the maximum, 3 robots will shadow threats
    // up front, 1 robot is dedicated as the goalie, and the other 2 robots will defend
    // either post (as show in the image, minus the 7th robot)
    //
    // The 3 positions following the first 2 are fallbacks if shadowing
    // is not required as there arent any enough threats to shadow. 
    // Robots will be assigned to those positions in order of priority
    std::vector<std::shared_ptr<Point>> defense_positions = {
        // TODO Update defense points
        std::make_shared<Point>(-2,0),
        std::make_shared<Point>(-2,1),
        std::make_shared<Point>(-2,2),
        std::make_shared<Point>(-2,3),
        std::make_shared<Point>(-2,4),
        //std::make_shared<Point>(world.field().friendlyGoal().x() + world.field().goalWidth(),
                //world.field().friendlyGoal().y()),
        //std::make_shared<Point>(world.field().friendlyGoalpostPos()+Point(2,2)),
        //std::make_shared<Point>(world.field().friendlyGoalpostNeg()+Point(2,2)),
    };

    // these move tactics will be used to go to those positions
    std::vector<std::shared_ptr<MoveTactic>> move_tactics = {
        std::make_shared<MoveTactic>(true),
        std::make_shared<MoveTactic>(true),
        std::make_shared<MoveTactic>(true),
        std::make_shared<MoveTactic>(true),
        std::make_shared<MoveTactic>(true)
    };

    do
    {
        // TODO: Replace placeholder tactic with goalie tactic
        lone_goalie_tactic_0->updateParams(
                world.field().friendlyGoal(),
                (world.ball().position() - world.field().friendlyGoal()).orientation(), 0);

        std::vector<std::shared_ptr<Tactic>> result = {lone_goalie_tactic_0};

        // 5 robots remaining, assign up to 3 to shadow top 3 threats if possible
        auto enemy_threats = Evaluation::getAllEnemyThreats(
                world.field(), world.friendlyTeam(), world.enemyTeam(), world.ball());
        Evaluation::sortThreatsInDecreasingOrder(enemy_threats);

        // keeps track of the next defense position to assign
        int defense_position_index = 0;

        for (int i = 0; i < 3; ++i){
            if (i < enemy_threats.size()){
                shadow_kickoff_tactics.at(i)->updateParams(enemy_threats.at(i).robot.position());
                result.emplace_back(shadow_kickoff_tactics.at(i));
            }
            else{
                move_tactics.at(defense_position_index)->updateParams(
                        *defense_positions.at(defense_position_index), Angle::half(), 0);
                result.emplace_back(move_tactics.at(defense_position_index));
                defense_position_index++;
            }
        }

        // assign the remaining robots to the remaining move tactics. If 3 robots were properly
        // assigned to the top 3 threats, then only the first 2 defense positions will be assigned
        for (defense_position_index; defense_position_index < defense_positions.size(); defense_position_index++){
            move_tactics.at(defense_position_index)->updateParams(
                    *defense_positions.at(defense_position_index), Angle::half(), 0);
            result.emplace_back(move_tactics.at(defense_position_index));

        }

        // yield the Tactics this Play wants to run, in order of priority
        yield(result);
    } while (true);
}

// Register this play in the PlayFactory
static TPlayFactory<KickoffEnemyPlay> factory;
