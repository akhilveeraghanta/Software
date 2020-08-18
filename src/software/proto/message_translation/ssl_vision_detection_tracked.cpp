#include <limits>
#include <memory>

#include "software/proto/message_translation/ssl_vision_detection_tracked.h"
#include "software/proto/ssl_vision_detection_tracked.pb.h"
#include "software/proto/ssl_gc_geometry.pb.h"
#include "software/proto/ssl_gc_common.pb.h"

std::unique_ptr<SSLProto::Vector2> createVector2(const Vector& vect) {
    auto vector_2 = std::make_unique<SSLProto::Vector2>();

    vector_2->set_x(vect.x());
    vector_2->set_y(vect.y());

    return std::move(vector_2);
}

// TODO add tbots geom for 3d vectors
std::unique_ptr<SSLProto::Vector3> createVector3(const Vector& vect, float height) {
    auto vector_3 = std::make_unique<SSLProto::Vector3>();

    vector_3->set_x(vect.x());
    vector_3->set_y(vect.y());

    return std::move(vector_3);
}

std::unique_ptr<SSLProto::RobotId> createRobotId(int robot_id, SSLProto::Team team){
    auto id = std::make_unique<SSLProto::RobotId>();

    id->set_id(robot_id);
    id->set_team(team);

    return std::move(id);
}

std::unique_ptr<SSLProto::TrackedBall> createSSLTrackedBall(
    const BallState& ball) {

    auto tracked_ball = std::make_unique<SSLProto::TrackedBall>();

    // TODO properly deal w/ 3d vectors
    tracked_ball->set_allocated_pos(createVector3(ball.position().toVector(), 0).release());
    tracked_ball->set_allocated_vel(createVector3(ball.velocity(), 0).release());

    return std::move(tracked_ball);
}

std::unique_ptr<SSLProto::TrackedRobot> createSSLTrackedRobot(
    const RobotStateWithId& robot, SSLProto::Team team) {

    auto tracked_robot = std::make_unique<SSLProto::TrackedRobot>();

    tracked_robot->set_allocated_robot_id(createRobotId(robot.id, team).release());
    tracked_robot->set_allocated_pos(createVector2(robot.robot_state.position().toVector()).release());
    tracked_robot->set_allocated_vel(createVector2(robot.robot_state.velocity()).release());
    tracked_robot->set_orientation(robot.robot_state.orientation().toRadians());
    tracked_robot->set_vel_angular(robot.robot_state.angularVelocity().toRadians());

    return std::move(tracked_robot);
}

std::unique_ptr<SSLProto::TrackedFrame> createSSLTrackedFrame(
    uint32_t frame_number, double timestamp,
    const std::vector<BallState>& balls,
    const std::vector<RobotStateWithId>& yellow_robots,
    const std::vector<RobotStateWithId>& blue_robots) {

    auto tracked_frame = std::make_unique<SSLProto::TrackedFrame>();

    tracked_frame->set_frame_number(frame_number);
    tracked_frame->set_timestamp(timestamp);

    for (const auto& ball_state : balls)
    {
        *(tracked_frame->add_balls()) = *createSSLTrackedBall(ball_state);
    }

    for (const auto& yellow_robot : yellow_robots)
    {
        *(tracked_frame->add_robots()) = *createSSLTrackedRobot(yellow_robot, SSLProto::Team::YELLOW);
    }

    for (const auto& blue_robot : blue_robots)
    {
        *(tracked_frame->add_robots()) = *createSSLTrackedRobot(blue_robot, SSLProto::Team::BLUE);
    }

    // TODO populate?
    // optional KickedBall kicked_ball = 5;
    // repeated Capability capabilities = 6;
}
