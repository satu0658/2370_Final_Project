/*
 * Tetris_Driver.c
 *
 *  Created on: Dec 9, 2024
 *      Author: smtur
 */

#include "Tetris_Driver.h"

volatile uint8_t FLAG = 1;
static uint8_t gameRunning = 1;
static Block_RegDef_t currentBlock;
static STMPE811_TouchData StaticTouchData;

static uint32_t startTime = 0;
static uint32_t endTime = 0;
static uint32_t elapsedTime = 0;
//static int isRowFull = -1;

static uint8_t tetrisBoard[BOARD_HEIGHT][BOARD_WIDTH] = {

		{1,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1}
};


uint8_t L_Shape[4][4] = {
    {1, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 0, 0, 0}
};

uint8_t O_Shape[4][4] = {
    {1, 1, 0, 0},
    {1, 1, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};

uint8_t I_Shape[4][4] = {
    {1, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 0, 0, 0}
};

uint8_t J_Shape[4][4] = {
    {0, 1, 0, 0},
    {0, 1, 0, 0},
    {1, 1, 0, 0},
    {0, 0, 0, 0}
};

uint8_t T_Shape[4][4] = {
    {1, 1, 1, 0},
    {0, 1, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};

uint8_t S_Shape[4][4] = {
    {0, 1, 1, 0},
    {1, 1, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};

uint8_t Z_Shape[4][4] = {
    {1, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};

uint8_t (*tetrisShapes[7])[4] = {
    L_Shape, O_Shape, I_Shape, J_Shape, T_Shape, S_Shape, Z_Shape
};

const uint16_t allColors[] = {
		LCD_COLOR_GREEN,
		LCD_COLOR_RED,
		LCD_COLOR_CYAN,
		LCD_COLOR_YELLOW,
		LCD_COLOR_MAGENTA,
		LCD_COLOR_BLUE,
		LCD_COLOR_GREY
};

const uint8_t allHeights[] = {3, 2, 4, 3, 2, 2, 2};

const uint8_t designator[] = {1, 2, 3, 4, 5, 6, 7};

void BlockInit(Block_RegDef_t* block, uint8_t shape[4][4], uint16_t x, uint16_t y, uint16_t color, uint16_t lineColor, uint8_t height) {

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            block->Shape[i][j] = shape[i][j];
        }
    }
    // Set position, color, and other properties
    block->x = x;
    block->y = y;
    block->color = color;
    block->lineColor = lineColor;
    block->rotation = 0;
    block->height = height;
}

void gameStart(void){

	while(1){
		if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed){

			HAL_Delay(100);
			gameScreen();
		}

	}
}
void GenerateRandomBlock(Block_RegDef_t* block){

	uint8_t blockSelect = GenerateRandNum() % 7;
	block->color = allColors[blockSelect];
	block->height = allHeights[blockSelect];
	block->designator = designator[blockSelect];
	for (int i = 0; i < 4; i++) {
		    for (int j = 0; j < 4; j++) {
		    	block->Shape[i][j] = tetrisShapes[blockSelect][i][j];
		        }
		 }


}

void drawTetrisShape(Block_RegDef_t* block){

	for (int i = 0; i < 4; i++) {
	    for (int j = 0; j < 4; j++) {
	        if (block->Shape[i][j] == 1) {
	            uint16_t blockX = block->x + j * 24; // Adjust block size if necessary
	            uint16_t blockY = block->y + i * 24;
	            LCD_Draw_Square_Fill(blockX, blockY, blockX + 24, blockY + 24, block->color);
	            LCD_Draw_Vertical_Line(blockX, blockY, 24, block->lineColor);
	            LCD_Draw_Horizontal_Line(blockX, blockY, 24, block->lineColor);
	            LCD_Draw_Vertical_Line(blockX+24, blockY, 24, block->lineColor);
	            LCD_Draw_Horizontal_Line(blockX, blockY+24, 24, block->lineColor);
	            }
	        }
	    }
}




void Rotate90() {
	uint16_t temp = currentBlock.color;
	currentBlock.lineColor = LCD_COLOR_WHITE;
	currentBlock.color = LCD_COLOR_WHITE;
	drawTetrisShape(&currentBlock);
	currentBlock.lineColor = LCD_COLOR_BLACK;
	currentBlock.color = temp;
	uint8_t oldX = currentBlock.x;
	uint8_t oldY = currentBlock.y;

	uint8_t temp_shape[4][4] = {0};
	for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
        	temp_shape[j][4-i-1] = currentBlock.Shape[i][j];
        }
    }
	for (int i = 0; i < 4; i++) {
	    for (int j = 0; j < 4; j++) {
	    	currentBlock.Shape[i][j] = temp_shape[i][j];
	        }
	}

	currentBlock.x = oldX;
	currentBlock.y = oldY;
	changeHeight(&currentBlock);
	//saveShape(&currentBlock, temp_shape);
	drawTetrisShape(&currentBlock);
}

void saveShape(Block_RegDef_t* block, uint8_t shape[4][4]){

	for (int i = 0; i < 4; i++) {
		    for (int j = 0; j < 4; j++) {
		    	block->Shape[i][j] = shape[i][j];
		        }
		}
}



void dropBlock(void){



		uint16_t temp = currentBlock.color;
		currentBlock.lineColor = LCD_COLOR_WHITE;
		currentBlock.color = LCD_COLOR_WHITE;
		drawTetrisShape(&currentBlock);
		//clearBoard(&currentBlock);
		currentBlock.y += 24;
		currentBlock.lineColor = LCD_COLOR_BLACK;
		currentBlock.color = temp;
		drawTetrisShape(&currentBlock);
		//updateBoard(&currentBlock);


}
void moveLeft(void){

	bool flag = true;
	for (int i = 0; i < 4; i++) {
		    for (int j = 0; j < 4; j++) {
		        if (currentBlock.Shape[i][j] == 1){
		        	if(tetrisBoard[((currentBlock.y/24)) + i][(currentBlock.x/24) + j - 1] == 1){
		        		flag = false;
		        	}
		        }
		    }
		}
	if(flag == true){
		uint16_t temp = currentBlock.color;
		currentBlock.lineColor = LCD_COLOR_WHITE;
		currentBlock.color = LCD_COLOR_WHITE;
		drawTetrisShape(&currentBlock);
		currentBlock.x -= 24;
		currentBlock.lineColor = LCD_COLOR_BLACK;
		currentBlock.color = temp;
	}
	else{

	}


}

void moveRight(void){

	bool flag = true;
	for (int i = 0; i < 4; i++) {
		    for (int j = 0; j < 4; j++) {
		        if (currentBlock.Shape[i][j] == 1){
		        	if(tetrisBoard[((currentBlock.y/24)) + i][(currentBlock.x/24) + j + 1] == 1){
		        		flag = false;
		        	}
		        }
		    }
		}
	if(flag == true){
		uint16_t temp = currentBlock.color;
		currentBlock.lineColor = LCD_COLOR_WHITE;
		currentBlock.color = LCD_COLOR_WHITE;
		drawTetrisShape(&currentBlock);
		currentBlock.x += 24;
		currentBlock.lineColor = LCD_COLOR_BLACK;
		currentBlock.color = temp;
	}
	else{

	}

}

bool isValidMove(Block_RegDef_t * block){

	bool flag = true;

	if(((block->y/24) + block->height) >= BOARD_HEIGHT){
		flag = false;
	}

	for (int i = 0; i < 4; i++) {
	    for (int j = 0; j < 4; j++) {
	        if (block->Shape[i][j] == 1){
	        	if((block->y/24) + i >=  BOARD_HEIGHT || (block->x/24) + j >= BOARD_WIDTH || (block->x/24) + j <= 0 || tetrisBoard[((block->y/24)) + i + 1][(block->x/24) + j] == 1){
	        		flag = false;
	        	}
	        }
	    }
	}
	return flag;
}

void changeHeight(Block_RegDef_t* block){

	uint8_t d = block->designator;
	uint8_t h = block->height;

	if(d == 3){
		if(h == 4){
			block->height = 1;
		}else{block->height = 4;}
	}
	else if(d == 1 || d == 4 || d == 5 || d == 6 || d == 7){
		if(h == 3){
			block->height = 2;
		}else{block->height = 3;}
	}
	else{

	}
}

void updateBoard(Block_RegDef_t* block) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (block->Shape[i][j] == 1) {
                // Mark the game board at the block's position as filled
                if ((block->y/24) + i < BOARD_HEIGHT && (block->x/24) + j < BOARD_WIDTH) {
                    tetrisBoard[(block->y/24) + i][(block->x/24) + j] = 1;
                }
            }
        }
    }
}

void clearBoard(Block_RegDef_t* block) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (block->Shape[i][j] == 1) {
                // Mark the game board at the block's position as filled
                if ((block->y/24) + i < BOARD_HEIGHT && (block->x/24) + j < BOARD_WIDTH) {
                    tetrisBoard[(block->y/24) + i][(block->x/24) + j] = 0;
                }
            }
        }
    }
}

void mainMenu(void){

	LCD_Clear(0, LCD_COLOR_WHITE);
	LCD_SetTextColor(LCD_COLOR_BLACK);
	LCD_SetFont(&Font16x24);

	LCD_DisplayChar(70,40,'T');
	LCD_DisplayChar(85,40,'E');
	LCD_DisplayChar(100,40,'T');
	LCD_DisplayChar(115,40,'R');
	LCD_DisplayChar(130,40,'I');
	LCD_DisplayChar(145,40,'S');

	LCD_DisplayChar(90,200,'S');
	LCD_DisplayChar(100,200,'t');
	LCD_DisplayChar(110,200,'a');
	LCD_DisplayChar(120,200,'r');
	LCD_DisplayChar(130,200,'t');
	Block_RegDef_t allBlocks[7];
	BlockInit(&allBlocks[0], O_Shape, 96, 136, LCD_COLOR_RED, LCD_COLOR_BLACK, allHeights[0]);
	BlockInit(&allBlocks[1], I_Shape, 24, 24,LCD_COLOR_CYAN, LCD_COLOR_BLACK, allHeights[1]);
	BlockInit(&allBlocks[2], T_Shape, 160, 240,LCD_COLOR_MAGENTA, LCD_COLOR_BLACK, allHeights[2]);
	BlockInit(&allBlocks[3], L_Shape, 24, 220,LCD_COLOR_GREEN, LCD_COLOR_BLACK, allHeights[3]);
	BlockInit(&allBlocks[4], J_Shape, 180, 24,LCD_COLOR_YELLOW, LCD_COLOR_BLACK, allHeights[4]);
	BlockInit(&allBlocks[5], S_Shape, 12, 136,LCD_COLOR_BLUE, LCD_COLOR_BLACK, allHeights[5]);
	BlockInit(&allBlocks[6], Z_Shape, 156,136,LCD_COLOR_GREY, LCD_COLOR_BLACK, allHeights[6]);

	for(int i = 0; i < 7; i++){
		drawTetrisShape(&allBlocks[i]);
	}

	gameStart();
}

void checkTop(void){
	for(int i = 1; i < BOARD_WIDTH - 1; i++){
		if(tetrisBoard[0][i] == 1){
			gameRunning = 0;
		}
	}
}

//int checkRow(void){
//	uint8_t count = 0;
//	uint8_t row = 0;
//	for(int i = 0;i< BOARD_HEIGHT - 1;i++){
//		count = 0;
//		for(int j = 1;j<BOARD_WIDTH - 1;j++){
//			if(tetrisBoard[i][j] == 1){
//				count += 1;
//				if(count == 10){
//					row = i;
//					return row;
//				}
//			}
//		}
//	}
//
//return -1;
//}
//
//void clearRow(uint8_t row){
//
//	for(int i = 1; i < BOARD_WIDTH - 1;i++){
//		tetrisBoard[row][i] = 0;
//		LCD_Draw_Square_Fill(0, row *24, 239, (row *24) + 24, LCD_COLOR_WHITE);
//	}
//}
void gameEnd(void){

	LCD_Clear(0, LCD_COLOR_BLACK);
	LCD_SetTextColor(LCD_COLOR_WHITE);
	LCD_SetFont(&Font16x24);

	LCD_DisplayChar(70,40,'U');
	LCD_DisplayChar(95,40,'T');
	LCD_DisplayChar(110,40,'R');
	LCD_DisplayChar(125,40,'A');
	LCD_DisplayChar(140,40,'S');
	LCD_DisplayChar(155,40,'H');


	char elapsed[] = {'E','l','a','p','s','e','d',' ','T','i','m','e',':'};
	for(int i = 0; i < 13; i++){
		if(i < 7){
			LCD_SetTextColor(allColors[i]);
		}
		else{
			LCD_SetTextColor(allColors[i-7]);
		}

		LCD_DisplayChar(50 + (11*i),80,elapsed[i]);
	}
	LCD_SetTextColor(LCD_COLOR_WHITE);
	//elapsedTime = (endTime - startTime) / 1000;
	uint32_t hours = elapsedTime / 3600;
	elapsedTime %= 60;
	uint32_t minutes = elapsedTime / 60;
	uint32_t seconds = elapsedTime % 60;

	char Hrs[] = {'X','X'};
	char Mins[] = {'X','X'};
	char Secs[] = {'X','X'};

	itoa(hours, Hrs, 10);
	itoa(minutes, Mins, 10);
	itoa(seconds, Secs, 10);

	LCD_DisplayChar(65,115,'0');
	LCD_DisplayChar(80,115,Hrs[0]);
	LCD_DisplayChar(92,115,':');
	LCD_DisplayChar(105,115,'0');
	LCD_DisplayChar(120,115,Mins[0]);
	LCD_DisplayChar(132,115,':');
	LCD_DisplayChar(142,115,Secs[0]);
	LCD_DisplayChar(157,115,Secs[1]);
	LCD_DisplayChar(167,115,'s');
}
void gameScreen(void){


	LCD_Clear(0, LCD_COLOR_WHITE);
	LCD_SetTextColor(LCD_COLOR_BLACK);
	LCD_SetFont(&Font16x24);
	LCD_Draw_Horizontal_Line(0, 312, 239, LCD_COLOR_BLACK);

	HAL_Delay(100);

	while(gameRunning){

		checkTop();
		currentBlock.x = X_START;
		currentBlock.y = Y_START;
		currentBlock.lineColor = LCD_COLOR_BLACK;
		currentBlock.rotation = ZERO_DEGREES;
		GenerateRandomBlock(&currentBlock);
		drawTetrisShape(&currentBlock);
		startTime = HAL_GetTick();
		HAL_Delay(100);


		while(isValidMove(&currentBlock) == true){

			HAL_Delay(500);
			dropBlock();

			if(getScheduledEvents() & ROTATION_EVENT){

				Rotate90();
				removeSchedulerEvent(ROTATION_EVENT);
			}
			if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed){

						if(StaticTouchData.x < 120){
							HAL_Delay(100);
							moveRight();
						}
						else if(StaticTouchData.x > 120){
							HAL_Delay(100);
							moveLeft();
						}


					}




		}
		endTime = HAL_GetTick();
		elapsedTime += (endTime - startTime) / 1000;
		startTime = 0;
		endTime = 0;
		Block_RegDef_t newBlock;
		BlockInit(&newBlock, currentBlock.Shape, currentBlock.x, currentBlock.y, currentBlock.color, LCD_COLOR_BLACK, currentBlock.height);
		drawTetrisShape(&newBlock);
		updateBoard(&newBlock);
//		isRowFull = checkRow();
//		if(isRowFull != -1){
//			clearRow(isRowFull);
//			isRowFull = -1;
//		}
	}


//	for(int i = 0; i < BOARD_HEIGHT+1; i++){
//		printf("\n");
//		for(int j=0; j < BOARD_WIDTH;j++){
//			printf("%d",tetrisBoard[i][j]);
//		}
//
//	}

	gameEnd();
}

