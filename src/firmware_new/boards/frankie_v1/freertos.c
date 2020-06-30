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
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"

#include "cmsis_os.h"
#include "main.h"
#include "task.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
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

/* USER CODE END Variables */
/* Definitions for NetStartTask */
osThreadId_t NetStartTaskHandle;
const osThreadAttr_t NetStartTask_attributes = {.name     = "NetStartTask",
                                                .priority = (osPriority_t)osPriorityHigh7,
                                                .stack_size = 1024 * 4};
/* Definitions for RobotStatusTask */
osThreadId_t RobotStatusTaskHandle;
const osThreadAttr_t RobotStatusTask_attributes = {
    .name       = "RobotStatusTask",
    .priority   = (osPriority_t)osPriorityHigh7,
    .stack_size = 1024 * 4};
/* Definitions for VisionMsgTask */
osThreadId_t VisionMsgTaskHandle;
const osThreadAttr_t VisionMsgTask_attributes = {
    .name       = "VisionMsgTask",
    .priority   = (osPriority_t)osPriorityHigh7,
    .stack_size = 1024 * 4};
/* Definitions for PrimMsgTask */
osThreadId_t PrimMsgTaskHandle;
const osThreadAttr_t PrimMsgTask_attributes = {.name     = "PrimMsgTask",
                                               .priority = (osPriority_t)osPriorityHigh7,
                                               .stack_size = 1024 * 4};
/* Definitions for testMsgUpdate */
osThreadId_t testMsgUpdateHandle;
const osThreadAttr_t testMsgUpdate_attributes = {
    .name       = "testMsgUpdate",
    .priority   = (osPriority_t)osPriorityNormal1,
    .stack_size = 1024 * 4};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void io_proto_multicast_startNetworkingTask(void *argument);
extern void io_proto_multicast_sender_task(void *argument);
extern void io_proto_multicast_listener_task(void *argument);
void test_msg_update(void *argument);

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

    /* USER CODE BEGIN RTOS_QUEUES */
    /* add queues, ... */
    /* USER CODE END RTOS_QUEUES */

    /* Create the thread(s) */
    /* creation of NetStartTask */
    NetStartTaskHandle = osThreadNew(io_proto_multicast_startNetworkingTask, NULL,
                                     &NetStartTask_attributes);

    /* creation of RobotStatusTask */
    RobotStatusTaskHandle =
        osThreadNew(io_proto_multicast_sender_task,
                    (void *)tbots_robot_msg_sender_profile, &RobotStatusTask_attributes);

    /* creation of VisionMsgTask */
    VisionMsgTaskHandle =
        osThreadNew(io_proto_multicast_listener_task, (void *)vision_msg_listener_profile,
                    &VisionMsgTask_attributes);

    /* creation of PrimMsgTask */
    PrimMsgTaskHandle =
        osThreadNew(io_proto_multicast_listener_task,
                    (void *)primitive_msg_listener_profile, &PrimMsgTask_attributes);

    /* creation of testMsgUpdate */
    testMsgUpdateHandle =
        osThreadNew(test_msg_update, (void *)tbots_robot_msg_sender_profile,
                    &testMsgUpdate_attributes);

    /* USER CODE BEGIN RTOS_THREADS */
    /* add threads, ... */
    /* USER CODE END RTOS_THREADS */
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
    /* Infinite loop */
    for (;;)
    {
        osDelay(1);
    }
    /* USER CODE END io_proto_multicast_startNetworkingTask */
}

/* USER CODE BEGIN Header_test_msg_update */
/**
 * @brief Function implementing the testMsgUpdate thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_test_msg_update */
void test_msg_update(void *argument)
{
    /* USER CODE BEGIN test_msg_update */
    /* Infinite loop */
    for (;;)
    {
        osDelay(1);
    }
    /* USER CODE END test_msg_update */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
