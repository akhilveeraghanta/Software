#include "software/proto/ssl_gc_ci.pb.h"
#include "software/proto/ssl_gc_common.pb.h"

std::unique_ptr<SSLProto::CiInput> createSSLCiInput(
    std::unique_ptr<SSLProto::TrackerWrapperPacket> tracker_packet)
{
    auto ci_input = std::make_unique<SSLProto::CiInput>();

    ci_input->set_timestamp(std::time(0));
    ci_input->set_allocated_tracker_packet(tracker_packet.release());

    return std::move(ci_input);
}
