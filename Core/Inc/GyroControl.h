/*
 * GyroControl.h
 *
 *  Created on: Nov 5, 2024
 *      Author: smtur
 */

#ifndef INC_GYROCONTROL_H_
#define INC_GYROCONTROL_H_
#include "stm32f4xx_hal.h"
#include <stdio.h>

#define WHO_AM_I 0x0F
#define CTRL_REG1 0x20
#define CTRL_REG5 0x24
#define OUT_TEMP 0x26

#define GYRO_READ_BIT (1 << 7)
#define GYRO_WRITE_BIT (0 << 7)
#define TIMEOUT_TEST 100
#define SHIFT_8 	 8
#define POWER_DOWN_MODE (1 << 3)
#define BOOT			(1 << 7)

#define GYRO_SPI5_SCK_PIN	GPIO_PIN_7
#define GYRO_SPI5_MISO_PIN	GPIO_PIN_8
#define GYRO_SPI5_MOSI_PIN	GPIO_PIN_9
#define GYRO_SPI5_CS_PIN	GPIO_PIN_1
#define GYRO_SSM 			9

void Gyro_Init();
void Gyro_GetID();
void Gyro_PowerOn();
void Gyro_GetTemp();
void Gyro_RegConfig();
void Gyro_ReadReg();
void Gyro_HALStatus();
void Gyro_Slave_Enable();
void Gyro_Slave_Disable();


#endif /* INC_GYROCONTROL_H_ */
