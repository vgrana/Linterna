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
}

void setEstadoLinterna(LinternaModel * model, EstadoLinterna value) {
	model->estadoLinterna = value;
}
void initTiempoEncendidoL(LinternaModel * linterna) {
	delayInit(&linterna->tiempoDeEncendido, 500);
}

void initDelayCounter9(LinternaModel* linterna) {
	delayInit(&linterna->ultimoCambioEstado, 0);
}

unsigned char linternaHabilitada(LinternaModel * linterna) {
	return linterna->estadoLinterna;
}

void linternaEncendida(LinternaModel * model) {
	setEstadoLinterna(model, PRENDIDA);
	initTiempoEncendidoL(model);
}

void linternaApagada(LinternaModel * model) {
	setEstadoLinterna(model, APAGADA);
}
void linterna_toggle(LinternaModel * model) {
	setEstadoLinterna(model, !model->estadoLinterna);
}

void linterna_upDate(LinternaModel * linterna) {
	switch (linterna->estadoLinterna) {
	case APAGADA: {
		break;
	}
	case PRENDIDA: {
				if (delayRead(&linterna->tiempoDeEncendido)) {
					linternaApagada(linterna);
		}
		break;
	}
	}

}

