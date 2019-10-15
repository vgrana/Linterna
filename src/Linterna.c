/*
 * Linterna.c
 *
 *  Created on: 12 oct. 2019
 *      Author: valeria
 */
#include "Linterna.h"
#include "sapi.h"

//void initTiempoEncendidoL(LinternaModel * model);
void initDelayCounter9(LinternaModel* linterna);
void setEstadoLinterna(LinternaModel * model, EstadoLinterna value);
void linternaInit(LinternaModel * linterna, unsigned char estado) {
	linterna->estadoLinterna = estado;
//	linterna->ultimoCambioEstado = tickRead();
//	linterna->tiempoDeEncendido = tickRead();
}

void setEstadoLinterna(LinternaModel * model, unsigned char value) {
	model->estadoLinterna = value;
}
//void initTiempoEncendidoL(LinternaModel * model) {
//	delayInit(&model->tiempoDeEncendido, 10);
//}
void linternaEncendida(LinternaModel * model) {
	setEstadoLinterna(model, 1);
}

void linternaApagada(LinternaModel * model) {
	setEstadoLinterna(model, 0);
}
//void initDelayCounter9(LinternaModel* linterna) {
//	delayInit(&linterna->ultimoCambioEstado, 00);
//}

unsigned char linternaHabilitada(LinternaModel * linterna) {
	return linterna->estadoLinterna;
}

void linterna_upDate(LinternaModel * linterna) {

	int TickActual = tickRead();
	int TiempoEncendido= TickActual - linterna->tiempoDeEncendido;

	switch (linterna->estadoLinterna) {

	case PRENDIDA: {
		if((linterna->estadoLinterna)==0){
					printf("estoy prendida\n");
					setEstadoLinterna(linterna,1);
				}

		break;
	}
	case APAGADA: {

		if ((linterna->estadoLinterna) == 0) {
			printf("estoy apagada");
			if (delayRead(&linterna->ultimoCambioEstado)) {
				setEstadoLinterna(linterna,1);
					linterna->tiempoDeEncendido = TickActual;
//				initDelayCounter9(linterna);
//				initTiempoEncendidoL(linterna);
//				linterna->tiempoDeEncendido = TickActual;
			}
//			linterna->tiempoDeEncendido = TickActual;
//						initDelayCounter9(linterna);
			}
			break;
	}
	}
}
