#pragma once
#include "software/proto/message_translation/ssl_vision_detection_tracked.h"
#include "software/proto/ssl_gc_common.pb.h"
#include "software/proto/ssl_gc_geometry.pb.h"
#include "software/proto/ssl_vision_detection_tracked.pb.h"
#include "software/proto/ssl_vision_wrapper_tracked.pb.h"

std::unique_ptr<SSLProto::TrackerWrapperPacket> createTrackerWrapperPacket(
    uint32_t frame_number, double timestamp, const std::vector<BallState>& balls,
    const std::vector<RobotStateWithId>& yellow_robots,
    const std::vector<RobotStateWithId>& blue_robots);
