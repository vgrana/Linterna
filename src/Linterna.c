/*
 * Linterna.c
 *
 *  Created on: 12 oct. 2019
 *      Author: valeria
 */
#include "Linterna.h"
#include "sapi.h"

void initTiempoEncendidoL(LinternaModel * model);
void initDelayCounter9(LinternaModel* linterna);

void linternaInit(LinternaModel * linterna, unsigned char estado) {
	linterna->estadoLinterna = estado;
	initTiempoEncendidoL(linterna);
}

void setEstadoLinterna(LinternaModel * model, unsigned char value) {
	model->estadoLinterna = value;
}
void initTiempoEncendidoL(LinternaModel * linterna) {
	delayInit(&linterna->tiempoDeEncendido, 50);
}

void initDelayCounter9(LinternaModel* linterna) {
	delayInit(&linterna->ultimoCambioEstado, 0);
}

unsigned char linternaHabilitada(LinternaModel * linterna) {
	return linterna->estadoLinterna;
}

void linternaEncendida(LinternaModel * model) {
	setEstadoLinterna(model, 1);
	initTiempoEncendidoL(model);
}

void linternaApagada(LinternaModel * model) {
	setEstadoLinterna(model, 0);
}
void linterna_toggle(LinternaModel * model) {
	setEstadoLinterna(model, !model->estadoLinterna);
}

void linterna_upDate(LinternaModel * linterna) {
	switch (linterna->estadoLinterna) {
	case APAGADA: {
		printf("estoy  en apagada\n");
		if (linterna->estadoLinterna == 1) {
	//		initDelayCounter9(linterna);
		}
		break;
	}
	case PRENDIDA: {
		printf("vale\n");
		if (linterna->estadoLinterna == 0) {
				if (delayRead(&linterna->tiempoDeEncendido)) {
					printf("tiempo encendido\n");
					linternaEncendida(linterna);
					initDelayCounter9(linterna);
					printf("me voy para apagado, \n");
			}
		}
		break;
	}
	}

}

