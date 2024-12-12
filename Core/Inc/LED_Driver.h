/*
 * LED_Driver.h
 *
 *  Created on: Sep 10, 2024
 *      Author: smtur
 */
#include "stm32f4xx_hal.h"
#include <stdint.h>


#ifndef LED_DRIVER_H_
#define LED_DRIVER_H_

#define GreenLED 1
#define RedLED 0


void LED_Init(); //initializes a GPIO that contains the pins that correspond to the on-board LEDs of the STM32
void ToggleLED(uint8_t select); //toggles LED on/off
void TurnOffLED(uint8_t select); //turns on LED
void TurnOnLED(uint8_t select); //turns off LED


#endif /* LED_DRIVER_H_ */
