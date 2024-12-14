# 2370_Final_Project
Tetris game for embedded

This ReadMe serves as the coding documentation for my final project write-up.

Note on coding hierarchy: After submitting my code, I realized that I had forgotten to delete some irrelevant files from previous labs. 
This includes InterruptControl, LED_Driver, and GyroControl. 

RNG_Handler:
  This file set simply initializes the MCU's RNG peripheral and includes a function for generating and returning a random number. 

LCD_Driver:
  Added two functions, LCD_Draw_Square_Fill and LCD_Draw_Horizontal_Line to expedite the process of drawing Tetris shapes. 
  I am now realizing I forgot to delete my old shape-drawing functions. Before converting my shapes to matrices,
  I used these functions to draw all of the shapes. 

Tetris_Driver:
  -Block_RegDef_t is a typedef struct containing the pertinent features of a Tetris block
  
  -void gameScreen() displays the game screen as long as the end condition is false. It calls many different functions that display 
  various things on the screen. It also starts the timer and then ends it when the game ends. 

  -void drawTetrisShape() takes in a Block_RegDef_t pointer and draws a Tetris shape on the screen based on the block's parameters

  -void checkTop() checks if a new shape will fit on the board and ends the game if it won't

  -void BlockInit() populates the block struct to allow a shape to be drawn

  -bool isValidMove() checks the space below a block on the game board and returns true if there is room

  -void updateBoard() inserts a Tetris block on the 2D array game board once it stops moving

  -void clearBoard() was supposed to clear a row on the board, but it took too much time and usually crashed the game

  -dropBlock, moveLeft, moveRight check the area around the current block and move it in the respective direction if there is space. 
  Move is done by erasing the old block and drawing the new block at a new location. 

  -void mainMenu() instantiates objects for all 7 shapes and displays them on the screen

  -void saveShape() updates x and y coordinates of a shape object

  -void changeHeight() updates height of a shape object

  -void generateRandomBlock() uses RNG to generate a random number and instantiates a block object based on that number

  -void Rotate90() uses matrix math to rotate a block 90 degrees clockwise and then calls saveShape() and changeHeight() to update the block. 
  Erases unrotated block before drawing the rotated version.
  

  
