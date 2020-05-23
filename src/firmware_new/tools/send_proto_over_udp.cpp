#include <chrono>
#include <thread>

#include "boost/array.hpp"
#include "boost/asio.hpp"
#include "boost/bind.hpp"
#include "firmware_new/boards/frankie_v1/constants.h"
#include "firmware_new/proto/control.pb.h"
#include "google/protobuf/message.h"
#include "software/logger/logger.h"
#include "software/networking/proto_multicast_sender.h"


using boost::asio::ip::udp;
using google::protobuf::Message;

int main(int argc, char* argv[])
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    // we create a wheel control msg, and request wheel 1 to spin at 100 rpm forwards
    // these wheel profile will be used across multiple wheels
    WheelSpeedMsg WheelControl;
    WheelControl.set_rpm(69);
    WheelControl.set_forwards(true);

    // turn two of the wheels on with this profile
    // NOTE that the other two wheels are not being populated
    ControlMsg control_req;
    control_req.mutable_wheel_1_control()->CopyFrom(WheelControl);
    control_req.mutable_wheel_2_control()->CopyFrom(WheelControl);
    control_req.mutable_wheel_2_control()->CopyFrom(WheelControl);

    // create an io service and run it in a thread to handle async calls
    boost::asio::io_service io_service;
    auto io_service_thread = std::thread([&]() { io_service.run(); });

    // create ProtoMulticastSender to send proto
    auto sender = std::make_unique<ProtoMulticastSender<ControlMsg>>(
        io_service, std::string(AI_MULTICAST_ADDRESS) + "%enp3s0f1",
        AI_MULTICAST_SEND_PORT);

    while (1)
    {
        sender->sendProto(control_req);

        // 4000 hz test
        std::this_thread::sleep_for(std::chrono::nanoseconds(250000));
    }

    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}
