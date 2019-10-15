/*
 * LinternaRender.c
 *
 *  Created on: 12 oct. 2019
 *      Author: valeria
 */

#include "LinternaRender.h"
void linternaRender_init(LinternaRender * linternaRender, LinternaModel * linterna, gpioMap_t gpio){
	linternaRender->linternaModel=linterna;
	linternaRender->gpio=gpio;
}

void linternaRender_update(LinternaRender * linternaRender){
	gpioWrite(linternaRender->gpio,linternaHabilitada(linternaRender->linternaModel));
}
