/*
 * RNG_Handler.h
 *
 *  Created on: Dec 8, 2024
 *      Author: smtur
 */

#ifndef INC_RNG_HANDLER_H_
#define INC_RNG_HANDLER_H_

#include "stm32f429xx.h"
#include "stm32f4xx_hal.h"


void RNG_Init(void);

uint32_t GenerateRandNum(void);


#endif /* INC_RNG_HANDLER_H_ */
