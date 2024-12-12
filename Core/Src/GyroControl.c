/*
 * GyroControl.c
 *
 *  Created on: Nov 5, 2024
 *      Author: smtur
 */

#include "GyroControl.h"

static SPI_HandleTypeDef Spi;
static HAL_StatusTypeDef Error;

void Gyro_Init(){
	GPIO_InitTypeDef F;
	F.Pin = GYRO_SPI5_SCK_PIN | GYRO_SPI5_MISO_PIN | GYRO_SPI5_MOSI_PIN;
	F.Mode = GPIO_MODE_AF_PP;
	F.Speed = GPIO_SPEED_FREQ_MEDIUM;
	F.Alternate = GPIO_AF5_SPI5;
	F.Pull = GPIO_NOPULL;
	__HAL_RCC_GPIOF_CLK_ENABLE();
	HAL_GPIO_Init(GPIOF, &F);

	GPIO_InitTypeDef C;
	C.Pin = GYRO_SPI5_CS_PIN;
	C.Mode = GPIO_MODE_OUTPUT_PP;
	C.Speed = GPIO_SPEED_FREQ_MEDIUM;
	C.Pull = GPIO_NOPULL;
	__HAL_RCC_GPIOC_CLK_ENABLE();
	HAL_GPIO_Init(GPIOC, &C);

	Spi.Instance = SPI5;
	Spi.Init.CLKPolarity = SPI_POLARITY_HIGH;
	Spi.Init.CLKPhase = SPI_PHASE_2EDGE;
	Spi.Init.FirstBit = SPI_FIRSTBIT_MSB;
	Spi.Init.Mode = SPI_MODE_MASTER;
	Spi.Init.DataSize = SPI_DATASIZE_8BIT;
	Spi.Init.NSS = SPI_NSS_SOFT;
	Spi.Init.Direction = SPI_DIRECTION_2LINES;
	Spi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	__HAL_RCC_SPI5_CLK_ENABLE();
	HAL_SPI_Init(&Spi);
}

void Gyro_GetID(){
	uint16_t commandToSend = (GYRO_READ_BIT | WHO_AM_I);
	uint16_t receivedData = 0x00;
	uint16_t DataReturned = 0x00;
	Gyro_Slave_Enable();

	while(HAL_GPIO_ReadPin(GPIOC, GYRO_SPI5_CS_PIN) != GPIO_PIN_RESET);

	Error = HAL_SPI_TransmitReceive(&Spi,(uint8_t*) &commandToSend, (uint8_t*) &receivedData, 2, TIMEOUT_TEST);

	if(Error != HAL_OK){
		for(;;);
	}

	DataReturned = (0xFF00 & receivedData) >> SHIFT_8;
	printf("The Device ID is: 0x%X \n", DataReturned);
	Gyro_Slave_Disable();
}

void Gyro_PowerOn(){
	uint16_t commandToSend = (GYRO_WRITE_BIT | CTRL_REG1) | (POWER_DOWN_MODE << SHIFT_8);
	uint16_t receivedData = 0x00;

	Gyro_Slave_Enable();

	while(HAL_GPIO_ReadPin(GPIOC, GYRO_SPI5_CS_PIN) != GPIO_PIN_RESET);

	Error = HAL_SPI_TransmitReceive(&Spi, (uint8_t*) &commandToSend, (uint8_t*) &receivedData, 2, TIMEOUT_TEST);

	if(Error != HAL_OK){
		for(;;);
	}

	Gyro_Slave_Disable();
}

void Gyro_GetTemp(){
	uint16_t commandToSend = (GYRO_READ_BIT | OUT_TEMP);
	uint16_t receivedData = 0x00;
	uint16_t DataReturned = 0x00;
	Gyro_Slave_Enable();

	while(HAL_GPIO_ReadPin(GPIOC, GYRO_SPI5_CS_PIN) != GPIO_PIN_RESET);

	Error = HAL_SPI_TransmitReceive(&Spi,(uint8_t*) &commandToSend, (uint8_t*) &receivedData, 2, TIMEOUT_TEST);

	if(Error != HAL_OK){
		for(;;);
	}

	DataReturned = (0xFF00 & receivedData) >> SHIFT_8;
	printf("The Temperature Is: %d \n", DataReturned);
	Gyro_Slave_Disable();
}

void Gyro_RegConfig(){
	uint16_t commandToSend = (GYRO_WRITE_BIT | CTRL_REG1) | (POWER_DOWN_MODE << SHIFT_8);
	uint16_t receivedData = 0x00;

	Gyro_Slave_Enable();

	while(HAL_GPIO_ReadPin(GPIOC, GYRO_SPI5_CS_PIN) != GPIO_PIN_RESET);

	Error = HAL_SPI_TransmitReceive(&Spi, (uint8_t*) &commandToSend, (uint8_t*) &receivedData, 1, TIMEOUT_TEST);

	if(Error != HAL_OK){
		for(;;);
	}

	Gyro_Slave_Disable();

	commandToSend = (GYRO_WRITE_BIT | CTRL_REG5) | (BOOT << SHIFT_8);
	receivedData = 0x00;
	Gyro_Slave_Enable();

	while(HAL_GPIO_ReadPin(GPIOC, GYRO_SPI5_CS_PIN) != GPIO_PIN_RESET);

	Error = HAL_SPI_TransmitReceive(&Spi, (uint8_t*) &commandToSend, (uint8_t*) &receivedData, 1, TIMEOUT_TEST);

	if(Error != HAL_OK){
		for(;;);
	}

	Gyro_Slave_Disable();
}

void Gyro_ReadReg(){

}

void Gyro_Slave_Enable(){

	HAL_GPIO_WritePin(GPIOC, GYRO_SPI5_CS_PIN, GPIO_PIN_RESET);
}

void Gyro_Slave_Disable(){

	HAL_GPIO_WritePin(GPIOC, GYRO_SPI5_CS_PIN, GPIO_PIN_SET);
}
