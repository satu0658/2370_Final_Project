/*
 * LED_Driver.c
 *
 *  Created on: Sep 10, 2024
 *      Author: smtur
 */

#include "LED_Driver.h"

//uses switching to enable either the reg or green on-board LED on the STM32
void LED_Init(){



	//instantiates a GPIO_PinConfig_t object and sets its members to the desired pin config for the LED. Then calls GPIO_Init() to enable the GPIO

		GPIO_InitTypeDef red;
		red.Pin = GPIO_PIN_13 | GPIO_PIN_14;
		red.Mode = GPIO_MODE_OUTPUT_PP;
		red.Speed = GPIO_SPEED_FREQ_MEDIUM;
		red.Alternate = GPIO_AF5_SPI5;
		red.Pull = GPIO_NOPULL;
		__HAL_RCC_GPIOG_CLK_ENABLE();
		HAL_GPIO_Init(GPIOG, &red);


}
//takes a one bit input and toggles the corresponding LED
void ToggleLED(uint8_t select){

	switch(select){

	case RedLED:
		HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_14);
		break;

	case GreenLED:
		HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_13);
		break;

	}
}

//takes a one bit input and disables the corresponding LED
void TurnOffLED(uint8_t select){

	switch(select){

		case RedLED:
			HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, 0);

		case GreenLED:
			HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, 0);
	}

}

//takes a one bit input and enables the corresponding LED
void TurnOnLED(uint8_t select){

	switch(select){

			case RedLED:
				HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, 1);

			case GreenLED:
				HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, 1);
		}
}
