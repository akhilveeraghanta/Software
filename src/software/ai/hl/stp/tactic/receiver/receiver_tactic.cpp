#include "software/ai/hl/stp/tactic/receiver/receiver_tactic.h"

#include "shared/constants.h"
#include "software/ai/evaluation/calc_best_shot.h"
#include "software/ai/hl/stp/action/move_action.h"
#include "software/ai/hl/stp/action/stop_action.h"
#include "software/geom/algorithms/acute_angle.h"
#include "software/geom/algorithms/closest_point.h"
#include "software/logger/logger.h"

ReceiverTactic::ReceiverTactic(const Pass pass, bool loop_forever)
    : Tactic(loop_forever, {RobotCapability::Move}),
      pass(std::move(pass)),
      fsm()
{
}

void ReceiverTactic::updateWorldParams(const World& world) {}

void ReceiverTactic::updateControlParams(const Pass& updated_pass)
{
    // Update the control parameters stored by this Tactic
    control_params.pass = updated_pass;
}

void ReceiverTactic::updateIntent(const TacticUpdate &tactic_update)
{
    fsm.process_event(ReceiverFSM::Update(control_params, tactic_update));
}

bool ReceiverTactic::done() const
{
    return fsm.is(boost::sml::X);
}

double ReceiverTactic::calculateRobotCost(const Robot& robot, const World& world) const
{
    // Prefer robots closer to the pass receive position
    // We normalize with the total field length so that robots that are within the field
    // have a cost less than 1
    double cost =
        (robot.position() - pass.receiverPoint()).length() / world.field().totalXLength();
    return std::clamp<double>(cost, 0, 1);
}

void ReceiverTactic::calculateNextAction(ActionCoroutine::push_type& yield)
{
    auto stop_action = std::make_shared<StopAction>(true);
    while (true)
    {
        yield({stop_action});
    }

    //// Setup for the pass. We want to use any free time before the pass starts putting
    //// ourselves in the best position possible to take the pass
    //// We wait for the ball to start moving at least a bit to make sure the passer
    //// has actually started the pass
    //while (ball.velocity().length() < 0.5)
    //{
        //// If there is a feasible shot we can take, we want to wait for the pass at the
        //// halfway point between the angle required to receive the ball and the angle
        //// for a one-time shot
        //std::optional<Shot> shot = findFeasibleShot();
        //Angle desired_angle      = pass.receiverOrientation();
        //if (shot)
        //{
            //Point target_position = shot->getPointToShootAt();

            //Angle shot_angle = (target_position - robot_->position()).orientation();

            //// If we do have a valid shot on net, orient the robot to face in-between
            //// the pass vector and shot vector, so the robot can quickly orient itself
            //// to either receive the pass, or take the shot. Also, not directly facing
            //// where we plan on kicking may throw off the enemy AI
            //desired_angle = (shot_angle + pass.receiverOrientation()) / 2;
        //}
        //// We want the robot to move to the receiving position for the shot and also
        //// rotate to the correct orientation
        //move_action->updateControlParams(*robot_, pass.receiverPoint(), desired_angle, 0,
                                         //DribblerMode::OFF, BallCollisionType::ALLOW);
        //yield(move_action);
    //}

    //// Vector from the ball to the robot
    //Vector ball_to_robot_vector   = ball.position() - robot_->position();
    //std::optional<Shot> best_shot = findFeasibleShot();
    //if (best_shot)
    //{
        //LOG(DEBUG) << "Taking one-touch shot";
        //auto best_shot_target = best_shot->getPointToShootAt();

        //// The angle between the ball velocity and a vector from the ball to the robot
        //Vector ball_velocity = ball.velocity();
        //ball_to_robot_vector = robot_->position() - ball.position();
        //Angle ball_robot_angle =
            //ball_velocity.orientation().minDiff(ball_to_robot_vector.orientation());

        //// Keep trying to shoot the ball while it's traveling roughly towards the robot
        //// (or moving slowly because we can't be certain of the velocity vector if it is)
        //while (ball_robot_angle.abs() < Angle::fromDegrees(90) ||
               //ball_velocity.length() < 0.5)
        //{
            //Shot shot =
                //getOneTimeShotPositionAndOrientation(*robot_, ball, best_shot_target);
            //Point ideal_position    = shot.getPointToShootAt();
            //Angle ideal_orientation = shot.getOpenAngle();

            //// Kicking at less than ball max speed to make sure we don't break rules
            //move_action->updateControlParams(
                //*robot_, ideal_position, ideal_orientation, 0, DribblerMode::OFF,
                //BallCollisionType::ALLOW,
                //{AutoChipOrKickMode::AUTOKICK, BALL_MAX_SPEED_METERS_PER_SECOND - 1});
            //yield(move_action);

            //// Calculations to check for termination conditions
            //ball_to_robot_vector = robot_->position() - ball.position();
            //ball_robot_angle =
                //ball_velocity.orientation().minDiff(ball_to_robot_vector.orientation());
        //}
    //}
    //// If we can't shoot on the enemy goal, just try to receive the pass as cleanly as
    //// possible
    //else
    //{
        //LOG(DEBUG) << "Receiving and dribbling";
        //while ((ball.position() - robot_->position()).length() >
               //DIST_TO_FRONT_OF_ROBOT_METERS + 2 * BALL_MAX_RADIUS_METERS)
        //{
            //Point ball_receive_pos = ball.position();
            //if (ball.velocity().length() != 0)
            //{
                //ball_receive_pos = closestPoint(
                    //robot_->position(),
                    //Line(ball.position(), ball.position() + ball.velocity()));
            //}
            //Angle ball_receive_orientation =
                //(ball.position() - robot_->position()).orientation();

            //// Move into position with the dribbler on
            //move_action->updateControlParams(
                //*robot_, ball_receive_pos, ball_receive_orientation, 0,
                //DribblerMode::MAX_FORCE, BallCollisionType::ALLOW);
            //yield(move_action);
        //}
    //}
    //LOG(DEBUG) << "Finished";
}

    //static std::optional<Shot> findFeasibleShot()
    //{
        //// Check if we can shoot on the enemy goal from the receiver position
        //std::optional<Shot> best_shot_opt =
            //calcBestShotOnGoal(field, friendly_team, enemy_team, robot_->position(),
                               //TeamType::ENEMY, {*this->getAssignedRobot()});

        //// Vector from the ball to the robot
        //Vector robot_to_ball = ball.position() - robot_->position();

        //// The angle the robot will have to deflect the ball to shoot
        //Angle abs_angle_between_pass_and_shot_vectors;
        //// The percentage of open net the robot would shoot on
        //double net_percent_open;
        //if (best_shot_opt)
        //{
            //Vector robot_to_shot_target =
                //best_shot_opt->getPointToShootAt() - robot_->position();
            //abs_angle_between_pass_and_shot_vectors =
                //(robot_to_ball.orientation() - robot_to_shot_target.orientation())
                    //.clamp()
                    //.abs();

            //Angle goal_angle = acuteAngle(field.friendlyGoalpostPos(), robot_->position(),
                                          //field.friendlyGoalpostNeg())
                                   //.abs();
            //net_percent_open =
                //best_shot_opt->getOpenAngle().toDegrees() / goal_angle.toDegrees();
        //}

        //// If we have a shot with a sufficiently large enough opening, and the
        //// deflection angle that is reasonable, we should one-touch kick the ball
        //// towards the enemy net
        //if (best_shot_opt && net_percent_open > MIN_SHOT_NET_PERCENT_OPEN &&
            //abs_angle_between_pass_and_shot_vectors < MAX_DEFLECTION_FOR_ONE_TOUCH_SHOT)
        //{
            //return best_shot_opt;
        //}
        //return std::nullopt;
    //}


void ReceiverTactic::accept(TacticVisitor& visitor) const
{
    visitor.visit(*this);
}