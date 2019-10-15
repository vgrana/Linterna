/*
 * Tecla.h
 *
 *  Created on: 30 sep. 2019
 *      Author: valeria
 */

#ifndef PROGRAMS_PRENDERAPAGAR_SENSOR_INC_TECLA_H_
#define PROGRAMS_PRENDERAPAGAR_SENSOR_INC_TECLA_H_
#include "sapi.h"
#include "sapi.h"

typedef enum {
	UP, FALLING, DOWN, RISING,
} TeclaState;

typedef void (*ButtonEventHandler)(void *);

typedef struct Tecla {
	gpioMap_t gpio;
	ButtonEventHandler onPress;
	ButtonEventHandler onRelease;
	void * model;
	TeclaState teclaState;
	delay_t delay;
} Tecla;



void tecla_init(Tecla * button , gpioMap_t gpio, void * model);

void tecla_onPress(Tecla * button, void * model);
void tecla_onRelease(Tecla * button, ButtonEventHandler handler);
void tecla_update(Tecla * button);


#endif /* PROGRAMS_PRENDERAPAGAR_SENSOR_INC_TECLA_H_ */
