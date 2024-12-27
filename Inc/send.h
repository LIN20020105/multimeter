/**
  ******************************************************************************
  * @file    send.h
  * @brief   This file contains all the function prototypes for
  *          the send.c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SEND_H__
#define __SEND_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

typedef unsigned int u32;
typedef unsigned short u16;
typedef short s16;
typedef unsigned char u8;
#define PI 3.1415926
#define UID_BASE_ADDRESS 0x1FFFF7E8
typedef struct ReportStruct {
  u32 header;
  u32 deviceId;
  u32 timestamp;
  u32 checkSum;
  u16 U1, U2, U3;
  u16 o1, o2, o3;
} ReportStruct;
/* USER CODE END Private defines */


/* USER CODE BEGIN Prototypes */
void resetReporter(ReportStruct *log);
void pack(ReportStruct *log,u32 uid,u8 O1,u8 O2,u8 O3,u32 U1,u32 U2,u32 U3);
void fillReportData(u8 O1,u8 O2,u8 O3,u32 U1,u32 U2,u32 U3);
void GetChipID ( void );
uint32_t murmur3_32_simple(uint32_t k);
uint32_t hash_cpu_id(uint32_t cpu_id0, uint32_t cpu_id1, uint32_t cpu_id2);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ SEND_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
