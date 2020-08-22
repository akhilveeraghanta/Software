#include "software/proto/message_translation/ssl_vision_wrapper_tracked.h"

#include "software/proto/message_translation/ssl_vision_detection_tracked.h"
#include "software/proto/ssl_gc_common.pb.h"

std::unique_ptr<SSLProto::TrackerWrapperPacket> createTrackerWrapperPacket(
    uint32_t frame_number, double timestamp, const std::vector<BallState>& balls,
    const std::vector<RobotStateWithId>& yellow_robots,
    const std::vector<RobotStateWithId>& blue_robots)
{
    auto tracked_wrapper_packet = std::make_unique<SSLProto::TrackerWrapperPacket>();

    tracked_wrapper_packet->set_uuid("30fab37e-e0fd-11ea-87d0-0242ac130003");
    tracked_wrapper_packet->set_source_name("UBC-THUNDERBOTS");
    tracked_wrapper_packet->set_allocated_tracked_frame(
        createSSLTrackedFrame(frame_number, timestamp, balls, yellow_robots, blue_robots)
            .release());

    return std::move(tracked_wrapper_packet);
}
