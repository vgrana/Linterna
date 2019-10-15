/*
 * LinternaRender.h
 *
 *  Created on: 12 oct. 2019
 *      Author: valeria
 */

#ifndef PROGRAMS_PRENDERAPAGAR_SENSOR_INC_LINTERNARENDER_H_
#define PROGRAMS_PRENDERAPAGAR_SENSOR_INC_LINTERNARENDER_H_
#include <sapi.h>
#include "Linterna.h"

//salida
typedef struct{
	gpioMap_t gpio;
	LinternaModel * linternaModel;
}LinternaRender;

void linternaRender_init(LinternaRender * linternaRender, LinternaModel * linterna, gpioMap_t gpio);
void linternaRender_update(LinternaRender * linternaRender);

#endif /* PROGRAMS_PRENDERAPAGAR_SENSOR_INC_LINTERNARENDER_H_ */
