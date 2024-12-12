/*
 * RNG_Handler.c
 *
 *  Created on: Dec 8, 2024
 *      Author: smtur
 */

#include "RNG_Handler.h"

static RNG_HandleTypeDef random;
HAL_StatusTypeDef statusRNG = HAL_OK;

void RNG_Init(void){

	__HAL_RCC_RNG_CLK_ENABLE();

	random.Instance = RNG;
	HAL_RNG_MspInit(&random);
	statusRNG = HAL_RNG_Init(&random);
}

uint32_t GenerateRandNum(void){

	uint32_t rando = 0;

	statusRNG = HAL_RNG_GenerateRandomNumber(&random, &rando);


	return rando;
}
