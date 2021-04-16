/**
 ******************************************************************************
<<<<<<< HEAD:src/firmware_new/boards/frankie_v1/eth.h
 * File Name          : ETH.h
 * Description        : This file provides code for the configuration
 *                      of the ETH instances.
=======
 * @file    usb_otg.h
 * @brief   This file contains all the function prototypes for
 *          the usb_otg.c file
>>>>>>> jonathan/fix_cubemx:src/firmware_new/boards/frankie_v1/usb_otg.h
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
/* Define to prevent recursive inclusion -------------------------------------*/
<<<<<<< HEAD:src/firmware_new/boards/frankie_v1/eth.h
#ifndef __eth_H
#define __eth_H
=======
#ifndef __USB_OTG_H__
#define __USB_OTG_H__

>>>>>>> jonathan/fix_cubemx:src/firmware_new/boards/frankie_v1/usb_otg.h
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

    /* USER CODE BEGIN Includes */

    /* USER CODE END Includes */

    extern ETH_HandleTypeDef heth;

    /* USER CODE BEGIN Private defines */

    /* USER CODE END Private defines */

    void MX_ETH_Init(void);

    /* USER CODE BEGIN Prototypes */

    /* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
<<<<<<< HEAD:src/firmware_new/boards/frankie_v1/eth.h
#endif /*__ eth_H */

/**
 * @}
 */
=======
>>>>>>> jonathan/fix_cubemx:src/firmware_new/boards/frankie_v1/usb_otg.h

#endif /* __USB_OTG_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
