#pragma once
#include <limits>
#include <memory>

#include "software/proto/ssl_vision_detection_tracked.pb.h"
#include "software/time/timestamp.h"
#include "software/world/ball_state.h"
#include "software/world/robot_state.h"

std::unique_ptr<SSLProto::TrackedBall> createSSLTrackedBall(const BallState& ball);

std::unique_ptr<SSLProto::TrackedRobot> createSSLTrackedRobot(
    const RobotStateWithId& ball, SSLProto::Team team);

std::unique_ptr<SSLProto::TrackedFrame> createSSLTrackedFrame(
    uint32_t frame_number, double timestamp, const std::vector<BallState>& balls,
    const std::vector<RobotStateWithId>& yellow_robots,
    const std::vector<RobotStateWithId>& blue_robots);
