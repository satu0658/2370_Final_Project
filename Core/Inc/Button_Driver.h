/*
 * Button_Driver.h
 *
 *  Created on: Sep 24, 2024
 *      Author: smtur
 */
#include "InterruptControl.h"
#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdbool.h>
#ifndef BUTTON_DRIVER_H_
#define BUTTON_DRIVER_H_

#define BUTTON_PORT GPIOA
#define BUTTON_PIN GPIO_PIN_0
#define BUTTON_PRESSED 1
#define BUTTON_UNPRESSED 0

void ButtonInit();
bool isPressed();
void ButtonInterrupt();

#endif /* BUTTON_DRIVER_H_ */
