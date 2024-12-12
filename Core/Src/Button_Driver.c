/*
 * Button_Driver.c
 *
 *  Created on: Sep 24, 2024
 *      Author: smtur
 */

#include "Button_Driver.h"

void ButtonInit(){
	GPIO_InitTypeDef button = {0};
	button.Pin = GPIO_PIN_0;
	button.Mode = GPIO_MODE_INPUT;
	__HAL_RCC_GPIOA_CLK_ENABLE();
	HAL_GPIO_Init(GPIOA, &button);



}

bool isPressed(){

	uint8_t flag = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
	if(flag == BUTTON_PRESSED){
		return true;
	}
	else{
		return false;
	}
}

void ButtonInterrupt(){
	GPIO_InitTypeDef buttonInterrupt = {0};
	buttonInterrupt.Mode = GPIO_MODE_IT_RISING_FALLING;
	buttonInterrupt.Pin = GPIO_PIN_0;
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_SYSCFG_CLK_ENABLE();
	HAL_GPIO_Init(GPIOA, &buttonInterrupt);
	__NVIC_EnableIRQ(EXTI0_IRQn);
}
