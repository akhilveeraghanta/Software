#pragma once
/**
 * This file is an abstraction around the Allegro A3931 Motor Driver
 */

#include "firmware_new/boards/frankie_v1/Drivers/STM32H7xx_HAL_Driver/Inc/stm32h7xx_hal.h"
#include "firmware_new/boards/frankie_v1/lwip.h"


typedef struct AICommunicator AllegroA3931MotorDriver_t;

/**
 * Create an AI Communicator
 * 
 * @param multicast_group The string representing the multicast group to join
 * @param vision_port The port the robot will receive vision from AI
 * @param primitive_port The port the robot will receive primitives from AI
 * @param robot_status_port The port the robot will send robot_status over
 *
 * @return an AI Communicator will all the sockets required
 */
AICommunicator_t* io_ai_communicator_create(
    const char* multicast_group,
    unsigned vision_port,
    unsigned primitive_port,
    unsigned robot_status_port
);
