/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under Ultimate Liberty license
 * SLA0044, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 *                             www.st.com/SLA0044
 *
 ******************************************************************************
 */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"

#include "cmsis_os.h"
#include "main.h"
#include "task.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#pragma GCC diagnostic pop
#include "firmware/app/logger/logger.h"
#include "firmware/app/primitives/primitive_manager.h"
#include "firmware/app/world/firmware_robot.h"
#include "firmware/app/world/firmware_world.h"
#include "firmware/boards/robot_stm32h7/io/breakbeam.h"
#include "firmware/boards/robot_stm32h7/io/charger.h"
#include "firmware/boards/robot_stm32h7/io/chicker.h"
#include "firmware/boards/robot_stm32h7/io/dribbler.h"
#include "firmware/boards/robot_stm32h7/io/drivetrain.h"
#include "firmware/boards/robot_stm32h7/io/network_logger.h"
#include "firmware/boards/robot_stm32h7/io/power_monitor.h"
#include "firmware/boards/robot_stm32h7/io/primitive_executor.h"
#include "firmware/boards/robot_stm32h7/io/proto_multicast.h"
#include "firmware/boards/robot_stm32h7/io/proto_multicast_communication_profile.h"
#include "firmware/boards/robot_stm32h7/io/robot_status.h"
#include "firmware/boards/robot_stm32h7/io/uart_logger.h"
#include "firmware/boards/robot_stm32h7/io/ublox_odinw262_communicator.h"
#include "firmware/boards/robot_stm32h7/io/vision.h"
#include "firmware/boards/robot_stm32h7/tim.h"
#include "firmware/boards/robot_stm32h7/usart.h"
#include "firmware/shared/physics.h"
#include "shared/constants.h"
#include "shared/proto/robot_log_msg.nanopb.h"
#include "shared/proto/robot_status_msg.nanopb.h"
#include "shared/proto/tbots_software_msgs.nanopb.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t osStaticThreadDef_t;
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

ProtoMulticastCommunicationProfile_t *robot_status_msg_sender_profile;
ProtoMulticastCommunicationProfile_t *robot_log_msg_sender_profile;
ProtoMulticastCommunicationProfile_t *vision_msg_listener_profile;
ProtoMulticastCommunicationProfile_t *primitive_msg_listener_profile;

static TbotsProto_Vision vision_msg;
static TbotsProto_RobotStatus robot_status_msg;
static TbotsProto_RobotLog robot_log_msg;
static TbotsProto_PrimitiveSet primitive_set_msg;

/* USER CODE END Variables */
/* Definitions for NetStartTask */
osThreadId_t NetStartTaskHandle;
uint32_t NetStartTaskBuffer[1024];
osStaticThreadDef_t NetStartTaskControlBlock;
const osThreadAttr_t NetStartTask_attributes = {
    .name       = "NetStartTask",
    .cb_mem     = &NetStartTaskControlBlock,
    .cb_size    = sizeof(NetStartTaskControlBlock),
    .stack_mem  = &NetStartTaskBuffer[0],
    .stack_size = sizeof(NetStartTaskBuffer),
    .priority   = (osPriority_t)osPriorityNormal,
};
/* Definitions for VisionMsgTask */
osThreadId_t VisionMsgTaskHandle;
uint32_t VisionMsgTaskBuffer[1024];
osStaticThreadDef_t VisionMsgTaskControlBlock;
const osThreadAttr_t VisionMsgTask_attributes = {
    .name       = "VisionMsgTask",
    .cb_mem     = &VisionMsgTaskControlBlock,
    .cb_size    = sizeof(VisionMsgTaskControlBlock),
    .stack_mem  = &VisionMsgTaskBuffer[0],
    .stack_size = sizeof(VisionMsgTaskBuffer),
    .priority   = (osPriority_t)osPriorityNormal,
};
/* Definitions for PrimMsgTask */
osThreadId_t PrimMsgTaskHandle;
uint32_t PrimMsgTaskBuffer[1024];
osStaticThreadDef_t PrimMsgTaskControlBlock;
const osThreadAttr_t PrimMsgTask_attributes = {
    .name       = "PrimMsgTask",
    .cb_mem     = &PrimMsgTaskControlBlock,
    .cb_size    = sizeof(PrimMsgTaskControlBlock),
    .stack_mem  = &PrimMsgTaskBuffer[0],
    .stack_size = sizeof(PrimMsgTaskBuffer),
    .priority   = (osPriority_t)osPriorityNormal,
};
/* Definitions for RobotStatus */
osThreadId_t RobotStatusHandle;
uint32_t RobotStatusBuffer[1024];
osStaticThreadDef_t RobotStatusControlBlock;
const osThreadAttr_t RobotStatus_attributes = {
    .name       = "RobotStatus",
    .cb_mem     = &RobotStatusControlBlock,
    .cb_size    = sizeof(RobotStatusControlBlock),
    .stack_mem  = &RobotStatusBuffer[0],
    .stack_size = sizeof(RobotStatusBuffer),
    .priority   = (osPriority_t)osPriorityNormal,
};
/* Definitions for RobotLogMsgSend */
osThreadId_t RobotLogMsgSendHandle;
uint32_t RobotLogMsgSendBuffer[1024];
osStaticThreadDef_t RobotLogMsgSendControlBlock;
const osThreadAttr_t RobotLogMsgSend_attributes = {
    .name       = "RobotLogMsgSend",
    .cb_mem     = &RobotLogMsgSendControlBlock,
    .cb_size    = sizeof(RobotLogMsgSendControlBlock),
    .stack_mem  = &RobotLogMsgSendBuffer[0],
    .stack_size = sizeof(RobotLogMsgSendBuffer),
    .priority   = (osPriority_t)osPriorityNormal,
};
/* Definitions for NetworkRobotLog */
osThreadId_t NetworkRobotLogHandle;
uint32_t NetworkRobotLogBuffer[1024];
osStaticThreadDef_t NetworkRobotLogControlBlock;
const osThreadAttr_t NetworkRobotLog_attributes = {
    .name       = "NetworkRobotLog",
    .cb_mem     = &NetworkRobotLogControlBlock,
    .cb_size    = sizeof(NetworkRobotLogControlBlock),
    .stack_mem  = &NetworkRobotLogBuffer[0],
    .stack_size = sizeof(NetworkRobotLogBuffer),
    .priority   = (osPriority_t)osPriorityNormal,
};
/* Definitions for RobotStatusSend */
osThreadId_t RobotStatusSendHandle;
uint32_t RobotStatusSendBuffer[1024];
osStaticThreadDef_t RobotStatusSendControlBlock;
const osThreadAttr_t RobotStatusSend_attributes = {
    .name       = "RobotStatusSend",
    .cb_mem     = &RobotStatusSendControlBlock,
    .cb_size    = sizeof(RobotStatusSendControlBlock),
    .stack_mem  = &RobotStatusSendBuffer[0],
    .stack_size = sizeof(RobotStatusSendBuffer),
    .priority   = (osPriority_t)osPriorityNormal,
};
/* Definitions for PrimExectuor */
osThreadId_t PrimExectuorHandle;
uint32_t PrimExectuorBuffer[1024];
osStaticThreadDef_t PrimExectuorControlBlock;
const osThreadAttr_t PrimExectuor_attributes = {
    .name       = "PrimExectuor",
    .cb_mem     = &PrimExectuorControlBlock,
    .cb_size    = sizeof(PrimExectuorControlBlock),
    .stack_mem  = &PrimExectuorBuffer[0],
    .stack_size = sizeof(PrimExectuorBuffer),
    .priority   = (osPriority_t)osPriorityNormal1,
};
/* Definitions for PrimStarter */
osThreadId_t PrimStarterHandle;
uint32_t PrimStarterBuffer[1024];
osStaticThreadDef_t PrimStarterControlBlock;
const osThreadAttr_t PrimStarter_attributes = {
    .name       = "PrimStarter",
    .cb_mem     = &PrimStarterControlBlock,
    .cb_size    = sizeof(PrimStarterControlBlock),
    .stack_mem  = &PrimStarterBuffer[0],
    .stack_size = sizeof(PrimStarterBuffer),
    .priority   = (osPriority_t)osPriorityNormal,
};
/* Definitions for RobotLogProtoQ */
osMessageQueueId_t RobotLogProtoQHandle;
const osMessageQueueAttr_t RobotLogProtoQ_attributes = {.name = "RobotLogProtoQ"};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void io_proto_multicast_startNetworkingTask(void *argument);
extern void io_proto_multicast_listenerTask(void *argument);
extern void io_robot_status_task(void *argument);
extern void io_proto_multicast_senderTask(void *argument);
extern void io_network_logger_task(void *argument);
extern void io_primitive_executor_task(void *argument);
extern void io_primitive_starter_task(void *argument);

extern void MX_LWIP_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
 * @brief  FreeRTOS initialization
 * @param  None
 * @retval None
 */
void MX_FREERTOS_Init(void)
{
    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* USER CODE BEGIN RTOS_MUTEX */
    /* add mutexes, ... */
    /* USER CODE END RTOS_MUTEX */

    /* USER CODE BEGIN RTOS_SEMAPHORES */
    /* add semaphores, ... */
    /* USER CODE END RTOS_SEMAPHORES */

    /* USER CODE BEGIN RTOS_TIMERS */
    /* start timers, add new ones, ... */
    /* USER CODE END RTOS_TIMERS */

    /* Create the queue(s) */
    /* creation of RobotLogProtoQ */
    RobotLogProtoQHandle =
        osMessageQueueNew(16, sizeof(TbotsProto_RobotLog), &RobotLogProtoQ_attributes);

    /* USER CODE BEGIN RTOS_QUEUES */
    /* add queues, ... */
    /* USER CODE END RTOS_QUEUES */

    /* Create the thread(s) */
    /* creation of NetStartTask */
    NetStartTaskHandle = osThreadNew(io_proto_multicast_startNetworkingTask, NULL,
                                     &NetStartTask_attributes);

    /* creation of VisionMsgTask */
    VisionMsgTaskHandle =
        osThreadNew(io_proto_multicast_listenerTask, (void *)vision_msg_listener_profile,
                    &VisionMsgTask_attributes);

    /* creation of PrimMsgTask */
    PrimMsgTaskHandle =
        osThreadNew(io_proto_multicast_listenerTask,
                    (void *)primitive_msg_listener_profile, &PrimMsgTask_attributes);

    /* creation of RobotStatus */
    RobotStatusHandle =
        osThreadNew(io_robot_status_task, (void *)robot_status_msg_sender_profile,
                    &RobotStatus_attributes);

    /* creation of RobotLogMsgSend */
    RobotLogMsgSendHandle =
        osThreadNew(io_proto_multicast_senderTask, (void *)robot_log_msg_sender_profile,
                    &RobotLogMsgSend_attributes);

    /* creation of NetworkRobotLog */
    NetworkRobotLogHandle =
        osThreadNew(io_network_logger_task, (void *)robot_log_msg_sender_profile,
                    &NetworkRobotLog_attributes);

    /* creation of RobotStatusSend */
    RobotStatusSendHandle =
        osThreadNew(io_proto_multicast_senderTask,
                    (void *)robot_status_msg_sender_profile, &RobotStatusSend_attributes);

    /* creation of PrimExectuor */
    PrimExectuorHandle =
        osThreadNew(io_primitive_executor_task, NULL, &PrimExectuor_attributes);

    /* creation of PrimStarter */
    PrimStarterHandle =
        osThreadNew(io_primitive_starter_task, (void *)primitive_msg_listener_profile,
                    &PrimStarter_attributes);

    /* USER CODE BEGIN RTOS_THREADS */
    /* USER CODE END RTOS_THREADS */

    /* USER CODE BEGIN RTOS_EVENTS */
    /* add events, ... */
    /* USER CODE END RTOS_EVENTS */
}

/* USER CODE BEGIN Header_io_proto_multicast_startNetworkingTask */
/**
 * @brief  Function implementing the NetStartTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_io_proto_multicast_startNetworkingTask */
__weak void io_proto_multicast_startNetworkingTask(void *argument)
{
    /* init code for LWIP */
    MX_LWIP_Init();
    /* USER CODE BEGIN io_proto_multicast_startNetworkingTask */
    /* USER CODE END io_proto_multicast_startNetworkingTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void initIoNetworking(void)
{
    // TODO channel and robot_id need to be hooked up to the dials on the robot, when
    // available https://github.com/UBC-Thunderbots/Software/issues/1517
    unsigned short int channel = 0;

    // Initialize multicast communication
    io_proto_multicast_init(NETWORK_TIMEOUT_MS);

    primitive_msg_listener_profile = io_proto_multicast_communication_profile_create(
        "primitive_msg_listener_profile", MULTICAST_CHANNELS[channel], PRIMITIVE_PORT,
        &primitive_set_msg, TbotsProto_PrimitiveSet_fields, MAXIMUM_TRANSFER_UNIT_BYTES);

    vision_msg_listener_profile = io_proto_multicast_communication_profile_create(
        "vision_msg_listener_profile", MULTICAST_CHANNELS[channel], VISION_PORT,
        &vision_msg, TbotsProto_Vision_fields, MAXIMUM_TRANSFER_UNIT_BYTES);

    robot_status_msg_sender_profile = io_proto_multicast_communication_profile_create(
        "robot_status_msg_sender", MULTICAST_CHANNELS[channel], ROBOT_STATUS_PORT,
        &robot_status_msg, TbotsProto_RobotStatus_fields, MAXIMUM_TRANSFER_UNIT_BYTES);

    robot_log_msg_sender_profile = io_proto_multicast_communication_profile_create(
        "robot_log_msg_sender", MULTICAST_CHANNELS[channel], ROBOT_LOGS_PORT,
        &robot_log_msg, TbotsProto_RobotLog_fields, MAXIMUM_TRANSFER_UNIT_BYTES);

    // TODO (#2064) mainboard rev 2.0 doens't have a reset pin for the u-blox chip
    // so we can't enable the communicator.
    GpioPin_t *ublox_reset_pin =
        io_gpio_pin_create(ID_SEL_4_GPIO_Port, ID_SEL_4_Pin, ACTIVE_LOW);

    // Initialize the ublox communicator
    io_ublox_odinw262_communicator_init(&huart4, ublox_reset_pin, 2);

    // Initialize network logger
    io_network_logger_init(RobotLogProtoQHandle);
}

void initIoDrivetrain(void)
{
    GpioPin_t *back_left_wheel_reset_pin = io_gpio_pin_create(
        WHEEL_BACK_LEFT_RESET_GPIO_Port, WHEEL_BACK_LEFT_RESET_Pin, ACTIVE_HIGH);
    GpioPin_t *back_left_wheel_mode_pin = io_gpio_pin_create(
        WHEEL_BACK_LEFT_MODE_GPIO_Port, WHEEL_BACK_LEFT_MODE_Pin, ACTIVE_HIGH);
    GpioPin_t *back_left_wheel_dir_pin = io_gpio_pin_create(
        WHEEL_BACK_LEFT_DIR_GPIO_Port, WHEEL_BACK_LEFT_DIR_Pin, ACTIVE_HIGH);

    GpioPin_t *front_left_wheel_reset_pin = io_gpio_pin_create(
        WHEEL_FRONT_LEFT_RESET_GPIO_Port, WHEEL_FRONT_LEFT_RESET_Pin, ACTIVE_HIGH);
    GpioPin_t *front_left_wheel_mode_pin = io_gpio_pin_create(
        WHEEL_FRONT_LEFT_MODE_GPIO_Port, WHEEL_FRONT_LEFT_MODE_Pin, ACTIVE_HIGH);
    GpioPin_t *front_left_wheel_dir_pin = io_gpio_pin_create(
        WHEEL_FRONT_LEFT_DIR_GPIO_Port, WHEEL_FRONT_LEFT_DIR_Pin, ACTIVE_HIGH);

    GpioPin_t *dribbler_reset_pin =
        io_gpio_pin_create(DRIBBLE_RESET_GPIO_Port, DRIBBLE_RESET_Pin, ACTIVE_HIGH);
    GpioPin_t *dribbler_mode_pin =
        io_gpio_pin_create(DRIBBLE_MODE_GPIO_Port, DRIBBLE_MODE_Pin, ACTIVE_HIGH);
    GpioPin_t *dribbler_dir_pin =
        io_gpio_pin_create(DRIBBLE_DIR_GPIO_Port, DRIBBLE_DIR_Pin, ACTIVE_HIGH);

    GpioPin_t *back_right_wheel_reset_pin = io_gpio_pin_create(
        WHEEL_BACK_RIGHT_RESET_GPIO_Port, WHEEL_BACK_RIGHT_RESET_Pin, ACTIVE_HIGH);
    GpioPin_t *back_right_wheel_mode_pin = io_gpio_pin_create(
        WHEEL_BACK_RIGHT_MODE_GPIO_Port, WHEEL_BACK_RIGHT_MODE_Pin, ACTIVE_HIGH);
    GpioPin_t *back_right_wheel_dir_pin = io_gpio_pin_create(
        WHEEL_BACK_RIGHT_DIR_GPIO_Port, WHEEL_BACK_RIGHT_DIR_Pin, ACTIVE_HIGH);

    GpioPin_t *front_right_wheel_reset_pin = io_gpio_pin_create(
        WHEEL_FRONT_RIGHT_RESET_GPIO_Port, WHEEL_FRONT_RIGHT_RESET_Pin, ACTIVE_HIGH);
    GpioPin_t *front_right_wheel_mode_pin = io_gpio_pin_create(
        WHEEL_FRONT_RIGHT_MODE_GPIO_Port, WHEEL_FRONT_RIGHT_MODE_Pin, ACTIVE_HIGH);
    GpioPin_t *front_right_wheel_dir_pin = io_gpio_pin_create(
        WHEEL_FRONT_RIGHT_DIR_GPIO_Port, WHEEL_FRONT_RIGHT_DIR_Pin, ACTIVE_HIGH);

    PwmPin_t *back_left_wheel_pwm_pin   = io_pwm_pin_create(&htim15, TIM_CHANNEL_2);
    PwmPin_t *front_left_wheel_pwm_pin  = io_pwm_pin_create(&htim3, TIM_CHANNEL_2);
    PwmPin_t *dribbler_pwm_pin          = io_pwm_pin_create(&htim1, TIM_CHANNEL_3);
    PwmPin_t *back_right_wheel_pwm_pin  = io_pwm_pin_create(&htim8, TIM_CHANNEL_1);
    PwmPin_t *front_right_wheel_pwm_pin = io_pwm_pin_create(&htim1, TIM_CHANNEL_2);

    AllegroA3931MotorDriver_t *back_left_wheel_driver =
        io_allegro_a3931_motor_driver_create(
            back_left_wheel_pwm_pin, back_left_wheel_reset_pin, back_left_wheel_mode_pin,
            back_left_wheel_dir_pin);
    AllegroA3931MotorDriver_t *front_left_wheel_driver =
        io_allegro_a3931_motor_driver_create(
            front_left_wheel_pwm_pin, front_left_wheel_reset_pin,
            front_left_wheel_mode_pin, front_left_wheel_dir_pin);
    AllegroA3931MotorDriver_t *dribbler_driver = io_allegro_a3931_motor_driver_create(
        dribbler_pwm_pin, dribbler_reset_pin, dribbler_mode_pin, dribbler_dir_pin);
    AllegroA3931MotorDriver_t *back_right_wheel_driver =
        io_allegro_a3931_motor_driver_create(
            back_right_wheel_pwm_pin, back_right_wheel_reset_pin,
            back_right_wheel_mode_pin, back_right_wheel_dir_pin);
    AllegroA3931MotorDriver_t *front_right_wheel_driver =
        io_allegro_a3931_motor_driver_create(
            front_right_wheel_pwm_pin, front_right_wheel_reset_pin,
            front_right_wheel_mode_pin, front_right_wheel_dir_pin);

    DrivetrainUnit_t *drivetrain_unit_back_left_wheel =
        io_drivetrain_unit_create(back_left_wheel_driver);
    DrivetrainUnit_t *drivetrain_unit_front_left_wheel =
        io_drivetrain_unit_create(front_left_wheel_driver);
    DrivetrainUnit_t *drivetrain_unit_back_right_wheel =
        io_drivetrain_unit_create(back_right_wheel_driver);
    DrivetrainUnit_t *drivetrain_unit_front_right_wheel =
        io_drivetrain_unit_create(front_right_wheel_driver);

    io_drivetrain_init(drivetrain_unit_front_left_wheel,
                       drivetrain_unit_front_right_wheel, drivetrain_unit_back_left_wheel,
                       drivetrain_unit_back_right_wheel);

    io_allegro_a3931_motor_setPwmPercentage(dribbler_driver, 0.0f);
}

void initIoPowerMonitor(void)
{
    // TODO (#2097) re-enable once the new mainboard and powerboard revs are in
    //
    // io_power_monitor_init(I2C1, INA226_ADDRESS,
    //                       INA226_MODE_CONT_SHUNT_AND_BUS | INA226_VBUS_140uS |
    //                           INA226_VBUS_140uS | INA226_AVG_1024);
}

void initIoChicker(void)
{
    GpioPin_t *breakbeam_pin =
        io_gpio_pin_create(BREAKBEAM_GPIO_Port, BREAKBEAM_Pin, ACTIVE_HIGH);

    Breakbeam_t *breakbeam = io_breakbeam_create(breakbeam_pin);

    io_chicker_init(breakbeam);
}

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
