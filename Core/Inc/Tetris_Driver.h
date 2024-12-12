/*
 * Tetris_Driver.h
 *
 *  Created on: Dec 9, 2024
 *      Author: smtur
 */

#ifndef INC_TETRIS_DRIVER_H_
#define INC_TETRIS_DRIVER_H_

#include "stm32f4xx_hal.h"
#include "ili9341.h"
#include "fonts.h"
#include "stmpe811.h"
#include "RNG_Handler.h"
#include "Scheduler.h"
#include "Tetris_Driver.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "LCD_Driver.h"

#define NINETY 90
#define X_START 96
#define Y_START 0
#define ZERO_DEGREES 0
#define BOARD_WIDTH  12
#define BOARD_HEIGHT 14
#define THREE_SECONDS 3000
typedef struct{

	uint8_t Shape[4][4];
	uint16_t x;
	uint16_t y;
	uint16_t lineColor;
	uint16_t color;
	uint16_t rotation;
	uint8_t height;
	uint8_t designator;
}Block_RegDef_t;

void gameScreen(void);
void checkTop(void);
void drawTetrisShape(Block_RegDef_t * block);
void BlockInit(Block_RegDef_t* block, uint8_t shape[4][4], uint16_t x, uint16_t y, uint16_t color, uint16_t lineColor, uint8_t height);

bool isValidMove(Block_RegDef_t * block);

void updateBoard(Block_RegDef_t* block);
void clearBoard(Block_RegDef_t* block);
void dropBlock(void);
void moveLeft(void);
void moveRight(void);
void gameStart(void);
void LCD_Error_Handler(void);

void mainMenu(void);

void saveShape(Block_RegDef_t* block, uint8_t shape[4][4]);

void changeHeight(Block_RegDef_t* block);

void GenerateRandomBlock(Block_RegDef_t* block);

void Rotate90(void);
//int checkRow(void);
//void clearRow(uint8_t row);

#endif /* INC_TETRIS_DRIVER_H_ */
