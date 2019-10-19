/*
 * Tecla.c
 *
 *  Created on: 30 sep. 2019
 *      Author: valeria
 */
#include "Tecla.h"

void nullHandler(void *);
void initDelayCounter(Tecla * button);
void changeState(Tecla * button, TeclaState state);


void tecla_init(Tecla * button, gpioMap_t gpio, void * model) {
	button->gpio = gpio;
	button->onPress = nullHandler;
	button->onRelease = nullHandler;
	button->teclaState = UP1;
	button->model = model;
}


void nullHandler(void * model){
}

void tecla_onPress(Tecla * button, ButtonEventHandler eventHandler) {
	button->onPress = eventHandler;
}

void tecla_onRelease(Tecla * button, ButtonEventHandler eventHandler) {
	button->onRelease = eventHandler;
}

void changeState(Tecla * button, TeclaState state) {
	button->teclaState = state;
}

void initDelayCounter(Tecla * button) {
	delayInit(&button->delay, 40);
}

void tecla_update(Tecla * tecla) {
//guardo el estado del boton
	bool_t readed = gpioRead( tecla->gpio );

	bool_t pressed = !readed;
	switch(tecla->teclaState) {

		case UP1 : {
			if(pressed) {
				changeState(tecla, FALLING1);
				initDelayCounter(tecla);
			}
			break;
		};
		case DOWN1 : {
			if(!pressed) {
				changeState(tecla, RISING1);
				initDelayCounter(tecla);
			}
			break;
		};
		case FALLING1 : {
			if(delayRead(&tecla->delay)) {
				if(pressed) {
					changeState(tecla, DOWN1);
					tecla->onPress(tecla->model);
				}
				else {
					changeState(tecla, UP1);
				}
			}
			break;
		}
		case RISING1 : {
			if(delayRead(&tecla->delay)) {
				if(!pressed) {
					changeState(tecla, UP1);
					tecla->onRelease(tecla->model);
				}
				else {
					changeState(tecla, DOWN1);
				}
			}
			break;
		}
		default : {
			//error
			changeState(tecla, pressed ? DOWN1 : UP1);
		}

	}
}

