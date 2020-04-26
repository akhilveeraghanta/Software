#include "firmware_new/boards/frankie_v1/io/allegro_a3931_motor_driver.h"

#include <stdlib.h>

typedef struct AICommunicator
{
    struct netconn *receive_vision_conn;
    struct netconn *receive_primitive_conn;
    struct netconn *send_status_conn;
    struct netbuf *rx_buf;
    struct netbuf *tx_buf;
} AICommunicator_t;

AICommunicator_t* io_ai_communicator_create(
        const char* multicast_group,
        unsigned vision_port,
        unsigned primitive_port,
        unsigned robot_status_port
) {

    AICommunicator_t* ai_communicator =
            (AICommunicator_t*)malloc(sizeof(AICommunicator_t));

    // create connections, we need one connection per port
    ai_communicator->receive_vision_conn = netconn_new(netconn_udp_ipv6);
    ai_communicator->receive_primitive_conn = netconn_new(netconn_udp_ipv6);
    ai_communicator->send_status_conn = netconn_new(netconn_udp_ipv6);

    // Bind the socket to the multicast address and port
    // we then use that connection profile to join the specified
    // multicast group.
    netconn_bind(ai_communicator->receive_vision_conn, multicast_group, vision_port);
    netconn_bind(ai_communicator->receive_primitive_conn, multicast_group, primitive_port);
    netconn_bind(ai_communicator->send_status_conn,  multicast_group, robot_status_port);

    // This will remain the same regardless of communicating over ethernet
    // or WiFi because both of those media use the ETH interface
    netconn_join_leave_group(ai_communicator->receive_vision_conn,
                             multicast_group, NULL, NETCONN_JOIN);
    netconn_join_leave_group(ai_communicator->receive_vision_conn,
                             multicast_group, NULL, NETCONN_JOIN);
    netconn_join_leave_group(ai_communicator->send_status_conn,
                             multicast_group, NULL, NETCONN_JOIN);

    return ai_communicator;
}


void io_ai_communicator_receiveVision(AICommunicator_t* ai_communicator){

}

void io_ai_communicator_receivePrimitives(){

}


void io_ai_communicator_sendTbotsRobotStatus(){

}


void io_ai_communicator_destroy(AICommunicator_t* ai_communicator)
{
    // we leave the multicast group before destroying the connections
    netconn_join_leave_group(ai_communicator->receive_vision_conn,
                             multicast_group, NULL, NETCONN_LEAVE);
    netconn_join_leave_group(ai_communicator->receive_vision_conn,
                             multicast_group, NULL, NETCONN_LEAVE);
    netconn_join_leave_group(ai_communicator->send_status_conn,
                             multicast_group, NULL, NETCONN_LEAVE);

    // delete all the connections
    netconn_delete(ai_communicator->receive_vision_conn);
    netconn_delete(ai_communicator->receive_primitive_conn);
    netconn_delete(ai_communicator->send_status_conn);

    free(ai_communicator);
}
