#include "software/proto/message_translation/ssl_vision_detection_tracked.h"
#include "software/proto/message_translation/ssl_vision_wrapper_tracked.h"
#include "software/proto/ssl_gc_ci.pb.h"
#include "software/proto/ssl_gc_common.pb.h"

std::unique_ptr<SSLProto::CiInput> createSSLCiInput(
    std::unique_ptr<SSLProto::TrackerWrapperPacket> tracker_packet);
