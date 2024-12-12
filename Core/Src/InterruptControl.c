/*
 * InterruptControl.c
 *
 *  Created on: Sep 26, 2024
 *      Author: smtur
 */

#include "InterruptControl.h"
//
//void IRQ_Enable(uint8_t IRQ_Num){
//	if(IRQ_Num < 32){
//		*NVIC_ISER0_ADDR |= (1 << IRQ_Num);
//	}
////	else if(IRQ_Num >= 32 && IRQ_Num < 64){
////		*NVIC_ISER1_ADDR |= (1 << (IRQ_Num % 32));
////	}
//}
//void IRQ_Disable(uint8_t IRQ_Num){
//	if(IRQ_Num < 32){
//		*NVIC_ICER0_ADDR |= (1 << IRQ_Num);
//		}
////	else if(IRQ_Num >= 32 && IRQ_Num < 64){
////		*NVIC_ICER1_ADDR |= (1 << (IRQ_Num % 32));
////	}
//}
//void IRQ_Set(uint8_t IRQ_Num){
//	if(IRQ_Num < 32){
//		*NVIC_ISPR0_ADDR |= (1 << IRQ_Num);
//		}
////	else if(IRQ_Num >= 32 && IRQ_Num < 64){
////		*NVIC_ISPR1_ADDR |= (1 << (IRQ_Num % 32));
////	}
//}
//void IRQ_Clear(uint8_t IRQ_Num){
//	if(IRQ_Num < 32){
//		*NVIC_ICPR0_ADDR |= (1 << IRQ_Num);
//		}
////	else if(IRQ_Num >= 32 && IRQ_Num < 64){
////		*NVIC_ICPR1_ADDR |= (1 << (IRQ_Num % 32));
////	}
//}
//void EXTI_Clear(){
//	(EXTI->PR |= (1 << Pin_Num));


//}
