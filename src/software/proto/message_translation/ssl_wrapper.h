#pragma once

#include <memory>

#include "software/proto/ssl_vision_detection.pb.h"
#include "software/proto/ssl_vision_geometry.pb.h"
#include "software/proto/ssl_vision_wrapper.pb.h"

/**
 * Creates a WrapperPacket from the given data
 *
 * @param geometry_data The geometry data to add to the wrapper packet. If null,
 * no data is added
 * @param detection_frame The detection frame data to add to the wrapper packet.
 * If null, no data is added
 *
 * @return A WrapperPacket containing the given data
 */
std::unique_ptr<SSLProto::SSL_WrapperPacket> createSSLWrapperPacket(
    std::unique_ptr<SSLProto::SSL_GeometryData> geometry_data,
    std::unique_ptr<SSLProto::SSL_DetectionFrame> detection_frame);
