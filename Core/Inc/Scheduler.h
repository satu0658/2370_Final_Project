/*
 * Scheduler.h
 *
 *  Created on: Sep 10, 2024
 *      Author: smtur
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_


//This file defines the scheduler for the program. The scheduler allows us to encode a 32-bit number that our main.c will decode as a set of instructions
#include <stdio.h>
#include <stdint.h>
#define LED_TOGGLE_EVENT	(1 << 0)
#define DELAY_EVENT		    (1 << 1)
#define BUTTON_PRESS_EVENT  (1 << 2)
#define DEVICE_ID_AND_TEMP_EVENT (1 << 3)
#define ROTATION_EVENT			 (1 << 4)

uint32_t getScheduledEvents();
void addSchedulerEvent(uint32_t eventToBeScheduled);
void removeSchedulerEvent(uint32_t eventToBeRemoved);


#endif /* SCHEDULER_H_ */
