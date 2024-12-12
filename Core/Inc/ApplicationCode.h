/*
 * ApplicationCode.h
 *
 *  Created on: Sep 10, 2024
 *      Author: smtur
 */


#ifndef APPLICATIONCODE_H_
#define APPLICATIONCODE_H_

#include "LED_Driver.h"
#include "Scheduler.h"
#include "Button_Driver.h"
#include "GyroControl.h"
#include "LCD_Driver.h"
#include "RNG_Handler.h"
#include "Tetris_Driver.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>

void ApplicationInit(void);
void LCD_Visual_Demo(void);
void LCD_Main_Menu(void);
#if (COMPILE_TOUCH_FUNCTIONS == 1) && (COMPILE_TOUCH_INTERRUPT_SUPPORT == 0)
void LCD_Touch_Polling_Demo(void);
#endif // (COMPILE_TOUCH_FUNCTIONS == 1) && (COMPILE_TOUCH_INTERRUPT_SUPPORT == 0)
//these macros are used for delays
#define Name_Length 3
#define MagDelay 25000
#define USE_INTERRUPT_FOR_BUTTON	1

//these functions all call functions from other files to allow user to control the device in a more organized way
void applicationInit();

void greenLEDInit();
void redLEDInit();
void toggleGreenLED();
void toggleRedLED();
void activateGreenLED();
void activateRedLED();
void deactivateGreenLED();
void deactivateRedLED();

void userButtonInit();
void executePollingRoutine();
void buttonInterruptInit();

void initializeGyro();
void GetID();
void GetTemp();
void RegConfig();
void GyroPower();
//function to add a delay to a program
void appDelay(uint32_t delay);
void initializeRNG(void);



#endif /* APPLICATIONCODE_H_ */
