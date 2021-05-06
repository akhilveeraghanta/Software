/**
<<<<<<< HEAD:src/firmware_new/boards/frankie_v1/gpio.c
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
=======
 ******************************************************************************
 * @file    gpio.c
 * @brief   This file provides code for the configuration
 *          of all used GPIO pins.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under Ultimate Liberty license
 * SLA0044, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 *                             www.st.com/SLA0044
 *
 ******************************************************************************
 */
>>>>>>> 919c00729a0a8ac2b2fe4970579e00f263a95854:src/firmware/boards/robot_stm32h7/gpio.c

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins
     PC14-OSC32_IN (OSC32_IN)   ------> RCC_OSC32_IN
     PC15-OSC32_OUT (OSC32_OUT)   ------> RCC_OSC32_OUT
     PH0-OSC_IN (PH0)   ------> RCC_OSC_IN
     PH1-OSC_OUT (PH1)   ------> RCC_OSC_OUT
     PA13 (JTMS/SWDIO)   ------> DEBUG_JTMS-SWDIO
     PA14 (JTCK/SWCLK)   ------> DEBUG_JTCK-SWCLK
     PB3 (JTDO/TRACESWO)   ------> DEBUG_JTDO-SWO
*/
void MX_GPIO_Init(void)
{
<<<<<<< HEAD:src/firmware_new/boards/frankie_v1/gpio.c

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, CHARGE_PWR_BRD_Pin|WHEEL_FRONT_RIGHT_FF1_Pin|IMU_INT1_Pin|USER_LED_2_Pin
                          |USER_LED_3_Pin|WHEEL_BACK_RIGHT_DIR_Pin|WHEEL_BACK_RIGHT_FF1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(IMU_INT2_GPIO_Port, IMU_INT2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, WHEEL_FRONT_RIGHT_RESET_Pin|WHEEL_FRONT_RIGHT_FF2_Pin|RED_IN_RGB_Pin|BLUE_IN_RGB_Pin
                          |GREEN_IN_RGB_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(WHEEL_BACK_RIGHT_RESET_GPIO_Port, WHEEL_BACK_RIGHT_RESET_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, DRIBBLER_RESET_Pin|DRIBBLER_FF1_Pin|DRIBBLER_FF2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, WHEEL_FRONT_LEFT_RESET_Pin|WHEEL_FRONT_LEFT_FF1_Pin|WHEEL_FRONT_LEFT_FF2_Pin|WHEEL_BACK_LEFT_RESET_Pin
                          |WHEEL_BACK_LEFT_FF1_Pin|WHEEL_BACK_LEFT_FF2_Pin|GENEVA_END_STOP_2_Pin|GENEVA_END_STOP_1_Pin
                          |GENEVA_DIR_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, WHEEL_FRONT_RIGHT_DIR_Pin|DRIBBLER_DIR_Pin|WHEEL_FRONT_LEFT_DIR_Pin|WHEEL_BACK_LEFT_DIR_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PEPin PEPin PEPin PEPin
                           PEPin PEPin PEPin */
  GPIO_InitStruct.Pin = CHARGE_PWR_BRD_Pin|WHEEL_FRONT_RIGHT_FF1_Pin|IMU_INT1_Pin|USER_LED_2_Pin
                          |USER_LED_3_Pin|WHEEL_BACK_RIGHT_DIR_Pin|WHEEL_BACK_RIGHT_FF1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PEPin PEPin PEPin PEPin */
  GPIO_InitStruct.Pin = FAULT_PWR_BRD_Pin|DONE_PWR_BRD_Pin|CH_SEL_3_Pin|CH_SEL_4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = IMU_INT2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(IMU_INT2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PFPin PFPin PFPin PFPin
                           PFPin */
  GPIO_InitStruct.Pin = WHEEL_FRONT_RIGHT_RESET_Pin|WHEEL_FRONT_RIGHT_FF2_Pin|RED_IN_RGB_Pin|BLUE_IN_RGB_Pin
                          |GREEN_IN_RGB_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = WHEEL_BACK_RIGHT_RESET_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(WHEEL_BACK_RIGHT_RESET_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PGPin PGPin PGPin */
  GPIO_InitStruct.Pin = CH_SEL_1_Pin|CH_SEL_2_Pin|BREAKBEAM_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : PDPin PDPin PDPin PDPin
                           PDPin */
  GPIO_InitStruct.Pin = WHEEL_BACK_RIGHT_FF2_Pin|ID_SEL_1_Pin|ID_SEL_3_Pin|ID_SEL_2_Pin
                          |ID_SEL_4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PDPin PDPin PDPin */
  GPIO_InitStruct.Pin = DRIBBLER_RESET_Pin|DRIBBLER_FF1_Pin|DRIBBLER_FF2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PGPin PGPin PGPin PGPin
                           PGPin PGPin PGPin PGPin
                           PGPin */
  GPIO_InitStruct.Pin = WHEEL_FRONT_LEFT_RESET_Pin|WHEEL_FRONT_LEFT_FF1_Pin|WHEEL_FRONT_LEFT_FF2_Pin|WHEEL_BACK_LEFT_RESET_Pin
                          |WHEEL_BACK_LEFT_FF1_Pin|WHEEL_BACK_LEFT_FF2_Pin|GENEVA_END_STOP_2_Pin|GENEVA_END_STOP_1_Pin
                          |GENEVA_DIR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : PAPin PAPin PAPin PAPin */
  GPIO_InitStruct.Pin = WHEEL_FRONT_RIGHT_DIR_Pin|DRIBBLER_DIR_Pin|WHEEL_FRONT_LEFT_DIR_Pin|WHEEL_BACK_LEFT_DIR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

=======
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOE,
                      wheel_motor_back_right_esf_Pin | wheel_motor_front_right_reset_Pin |
                          wheel_motor_front_right_coast_Pin,
                      GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(
        GPIOF,
        wheel_motor_front_right_mode_Pin | wheel_motor_front_right_direction_Pin |
            wheel_motor_front_right_brake_Pin | wheel_motor_front_right_esf_Pin,
        GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(
        GPIOC, wheel_motor_back_right_coast_Pin | wheel_motor_back_left_direction_Pin,
        GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOA,
                      wheel_motor_back_right_brake_Pin |
                          wheel_motor_back_right_reset_Pin |
                          wheel_motor_back_right_direction_Pin,
                      GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(
        GPIOB,
        wheel_motor_back_left_brake_Pin | wheel_motor_back_left_esf_Pin |
            wheel_motor_front_left_esf_Pin | wheel_motor_back_left_reset_Pin |
            wheel_motor_back_left_coast_Pin | LD3_Pin | wheel_motor_back_left_mode_Pin |
            wheel_motor_front_left_reset_Pin | wheel_motor_front_left_coast_Pin |
            wheel_motor_front_left_mode_Pin | LD2_Pin |
            wheel_motor_front_left_direction_Pin | wheel_motor_front_left_brake_Pin,
        GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(USB_PowerSwitchOn_GPIO_Port, USB_PowerSwitchOn_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOD, ublox_reset_Pin | wheel_motor_back_right_mode_Pin,
                      GPIO_PIN_RESET);

    /*Configure GPIO pins : PEPin PEPin PEPin */
    GPIO_InitStruct.Pin = wheel_motor_back_right_esf_Pin |
                          wheel_motor_front_right_reset_Pin |
                          wheel_motor_front_right_coast_Pin;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    /*Configure GPIO pin : PtPin */
    GPIO_InitStruct.Pin  = USER_Btn_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(USER_Btn_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pins : PFPin PFPin PFPin PFPin */
    GPIO_InitStruct.Pin =
        wheel_motor_front_right_mode_Pin | wheel_motor_front_right_direction_Pin |
        wheel_motor_front_right_brake_Pin | wheel_motor_front_right_esf_Pin;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    /*Configure GPIO pins : PCPin PCPin */
    GPIO_InitStruct.Pin =
        wheel_motor_back_right_coast_Pin | wheel_motor_back_left_direction_Pin;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /*Configure GPIO pins : PAPin PAPin PAPin */
    GPIO_InitStruct.Pin = wheel_motor_back_right_brake_Pin |
                          wheel_motor_back_right_reset_Pin |
                          wheel_motor_back_right_direction_Pin;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pins : PBPin PBPin PBPin PBPin
                             PBPin PBPin PBPin PBPin
                             PBPin PBPin PBPin PBPin
                             PBPin */
    GPIO_InitStruct.Pin =
        wheel_motor_back_left_brake_Pin | wheel_motor_back_left_esf_Pin |
        wheel_motor_front_left_esf_Pin | wheel_motor_back_left_reset_Pin |
        wheel_motor_back_left_coast_Pin | LD3_Pin | wheel_motor_back_left_mode_Pin |
        wheel_motor_front_left_reset_Pin | wheel_motor_front_left_coast_Pin |
        wheel_motor_front_left_mode_Pin | LD2_Pin | wheel_motor_front_left_direction_Pin |
        wheel_motor_front_left_brake_Pin;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /*Configure GPIO pin : PtPin */
    GPIO_InitStruct.Pin   = USB_PowerSwitchOn_Pin;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(USB_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pin : PtPin */
    GPIO_InitStruct.Pin  = USB_OverCurrent_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(USB_OverCurrent_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pins : PDPin PDPin */
    GPIO_InitStruct.Pin   = ublox_reset_Pin | wheel_motor_back_right_mode_Pin;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
>>>>>>> 919c00729a0a8ac2b2fe4970579e00f263a95854:src/firmware/boards/robot_stm32h7/gpio.c
}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
