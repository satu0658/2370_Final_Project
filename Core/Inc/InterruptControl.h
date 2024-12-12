/*
 * InterruptControl.h
 *
 *  Created on: Sep 26, 2024
 *      Author: smtur
 */

#ifndef INTERRUPTCONTROL_H_
#define INTERRUPTCONTROL_H_

#include <stdint.h>
#include "stm32f4xx_hal.h"
#define EXTI0_IRQ_NUM    6

void IRQ_Enable(uint8_t);
void IRQ_Disable(uint8_t);
void IRQ_Set(uint8_t);
void IRQ_Clear(uint8_t);
void EXTI_Clear();

#endif /* INTERRUPTCONTROL_H_ */
