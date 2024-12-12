/*
 * Scheduler.c
 *
 *  Created on: Sep 10, 2024
 *      Author: smtur
 */

#include "Scheduler.h"

static uint32_t scheduledEvents;

//adds to the scheduler
void addSchedulerEvent(uint32_t eventToBeScheduled){
	scheduledEvents |= eventToBeScheduled;
}

//removes from the scheduler
void removeSchedulerEvent(uint32_t eventToBeRemoved){
	scheduledEvents &= ~(eventToBeRemoved);
}

//returns the 32-bit scheduler instruction
uint32_t getScheduledEvents(){
	return scheduledEvents;
}
