/*
 * ApplicationCode.c
 *
 *  Created on: Sep 10, 2024
 *      Author: smtur
 */

#include "ApplicationCode.h"
//all of these functions have been described in their parent files



void applicationInit(){

	initializeGyro();
	RegConfig();
	GyroPower();
	addSchedulerEvent(DELAY_EVENT);
	#if USE_INTERRUPT_FOR_BUTTON == 1

	buttonInterruptInit();

	#elif USE_INTERRUPT_FOR_BUTTON == 0

	userButtonInit();
	addSchedulerEvent(BUTTON_PRESS_EVENT);

	#endif

}

void greenLEDInit(){
	LED_Init(GreenLED);
}

void redLEDInit(){
	LED_Init(RedLED);
}
void toggleGreenLED(){
	ToggleLED(GreenLED);
}
void toggleRedLED(){
	ToggleLED(RedLED);
}
void activateGreenLED(){
	TurnOnLED(GreenLED);
}
void activateRedLED(){
	TurnOnLED(RedLED);
}
void deactivateGreenLED(){
	TurnOffLED(GreenLED);
}
void deactivateRedLED(){
	TurnOffLED(RedLED);
}


#if USE_INTERRUPT_FOR_BUTTON == 0

void executePollingRoutine(){
	if(isPressed()){
		activateGreenLED();
	}
	else if(!isPressed()){
		deactivateGreenLED();
	}
}
void userButtonInit(){
	ButtonInit();
}
#endif

#if USE_INTERRUPT_FOR_BUTTON == 1
void buttonInterruptInit(){
	ButtonInterrupt();
}
#endif

//same as previous lab. executes repeated iteration to create a delay
void appDelay(uint32_t delay){
	char nameArr[Name_Length] = {'s','a','m'};
	[[maybe_unused]] char destinationArr[Name_Length];

	for(int i = 0; i < delay; i++){

		for(int j = 0; j < Name_Length; j++){

			destinationArr[j] = nameArr[j];
		}
	}
}

void EXTI0_IRQHandler(){
	NVIC_DisableIRQ(EXTI0_IRQn);
	addSchedulerEvent(ROTATION_EVENT);

	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0);
	NVIC_EnableIRQ(EXTI0_IRQn);
}

void initializeGyro(){
	Gyro_Init();
}

void GetID(){
	Gyro_GetID();
}

void GetTemp(){
	Gyro_GetTemp();
}

void RegConfig(){
	Gyro_RegConfig();
}

void GyroPower(){
	Gyro_PowerOn();
}

extern void initialise_monitor_handles(void);

#if COMPILE_TOUCH_FUNCTIONS == 1
static STMPE811_TouchData StaticTouchData;
#if TOUCH_INTERRUPT_ENABLED == 1
static EXTI_HandleTypeDef LCDTouchIRQ;
void LCDTouchScreenInterruptGPIOInit(void);
#endif // TOUCH_INTERRUPT_ENABLED
#endif // COMPILE_TOUCH_FUNCTIONS

void ApplicationInit(void)
{
	initialise_monitor_handles(); // Allows printf functionality
	initializeRNG();
	buttonInterruptInit();
	LTCD__Init();
    LTCD_Layer_Init(0);
    LCD_Clear(0,LCD_COLOR_WHITE);

    #if COMPILE_TOUCH_FUNCTIONS == 1
	InitializeLCDTouch();

	// This is the orientation for the board to be direclty up where the buttons are vertically above the screen
	// Top left would be low x value, high y value. Bottom right would be low x value, low y value.
	StaticTouchData.orientation = STMPE811_Orientation_Portrait_2;

	#if TOUCH_INTERRUPT_ENABLED == 1
	LCDTouchScreenInterruptGPIOInit();
	#endif // TOUCH_INTERRUPT_ENABLED

	#endif // COMPILE_TOUCH_FUNCTIONS
}

void LCD_Visual_Demo(void)
{
	visualDemo();
}

void LCD_Main_Menu(void){

	mainMenu();

}
#if COMPILE_TOUCH_FUNCTIONS == 1
void LCD_Touch_Polling_Demo(void)
{
	LCD_Clear(0,LCD_COLOR_GREEN);
	while (1) {
		/* If touch pressed */
		if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed) {
			/* Touch valid */
			printf("\nX: %03d\nY: %03d\n", StaticTouchData.x, StaticTouchData.y);
			LCD_Clear(0, LCD_COLOR_RED);
		} else {
			/* Touch not pressed */
			printf("Not Pressed\n\n");
			LCD_Clear(0, LCD_COLOR_GREEN);
		}
	}
}
void initializeRNG(void){
	RNG_Init();
}

// TouchScreen Interrupt
#if TOUCH_INTERRUPT_ENABLED == 1

void LCDTouchScreenInterruptGPIOInit(void)
{
	GPIO_InitTypeDef LCDConfig = {0};
    LCDConfig.Pin = GPIO_PIN_15;
    LCDConfig.Mode = GPIO_MODE_IT_RISING_FALLING;
    LCDConfig.Pull = GPIO_NOPULL;
    LCDConfig.Speed = GPIO_SPEED_FREQ_HIGH;

    // Clock enable
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // GPIO Init
    HAL_GPIO_Init(GPIOA, &LCDConfig);

    // Interrupt Configuration
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

	LCDTouchIRQ.Line = EXTI_LINE_15;

}

#define TOUCH_DETECTED_IRQ_STATUS_BIT   (1 << 0)  // Touchscreen detected bitmask

static uint8_t statusFlag;

void EXTI15_10_IRQHandler()
{
	HAL_NVIC_DisableIRQ(EXTI15_10_IRQn); // May consider making this a universial interrupt guard
	bool isTouchDetected = false;

	static uint32_t count;
	count = 0;
	while(count == 0){
		count = STMPE811_Read(STMPE811_FIFO_SIZE);
	}

	// Disable touch interrupt bit on the STMPE811
	uint8_t currentIRQEnables = ReadRegisterFromTouchModule(STMPE811_INT_EN);
	WriteDataToTouchModule(STMPE811_INT_EN, 0x00);

	// Clear the interrupt bit in the STMPE811
	statusFlag = ReadRegisterFromTouchModule(STMPE811_INT_STA);
	uint8_t clearIRQData = (statusFlag | TOUCH_DETECTED_IRQ_STATUS_BIT); // Write one to clear bit
	WriteDataToTouchModule(STMPE811_INT_STA, clearIRQData);

	uint8_t ctrlReg = ReadRegisterFromTouchModule(STMPE811_TSC_CTRL);
	if (ctrlReg & 0x80)
	{
		isTouchDetected = true;
	}

	// Determine if it is pressed or unpressed
	if(isTouchDetected) // Touch has been detected
	{
		printf("\nPressed");
		// May need to do numerous retries?
		DetermineTouchPosition(&StaticTouchData);
		/* Touch valid */
		printf("\nX: %03d\nY: %03d \n", StaticTouchData.x, StaticTouchData.y);
		LCD_Clear(0, LCD_COLOR_RED);

	}else{

		/* Touch not pressed */
		printf("\nNot pressed \n");
		LCD_Clear(0, LCD_COLOR_GREEN);
	}

	STMPE811_Write(STMPE811_FIFO_STA, 0x01);
	STMPE811_Write(STMPE811_FIFO_STA, 0x00);

	// Re-enable IRQs
    WriteDataToTouchModule(STMPE811_INT_EN, currentIRQEnables);
	HAL_EXTI_ClearPending(&LCDTouchIRQ, EXTI_TRIGGER_RISING_FALLING);

	HAL_NVIC_ClearPendingIRQ(EXTI15_10_IRQn);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

	//Potential ERRATA? Clearing IRQ bit again due to an IRQ being triggered DURING the handling of this IRQ..
	WriteDataToTouchModule(STMPE811_INT_STA, clearIRQData);

}
#endif // TOUCH_INTERRUPT_ENABLED
#endif // COMPILE_TOUCH_FUNCTIONS
