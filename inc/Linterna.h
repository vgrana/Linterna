/*
 * Linterna.h
 *
 *  Created on: 12 oct. 2019
 *      Author: valeria
 */

#ifndef PROGRAMS_PRENDERAPAGAR_SENSOR_INC_LINTERNA_H_
#define PROGRAMS_PRENDERAPAGAR_SENSOR_INC_LINTERNA_H_
#include "sapi.h"

typedef enum {
	PRENDIDA,APAGADA
} EstadoLinterna;

typedef struct Linterna{
	EstadoLinterna estadoDeLaLinterna;
	unsigned char estadoLinterna;
	delay_t ultimoCambioEstado;
	delay_t tiempoDeEncendido;
}LinternaModel;

void linternaInit(LinternaModel * model, unsigned char estado);
void linterna_upDate(LinternaModel * model);
void linternaEncendida(LinternaModel * model);
void linternaApagada(LinternaModel * model);
unsigned char linternaHabilitada(LinternaModel * model);

#endif /* PROGRAMS_PRENDERAPAGAR_SENSOR_INC_LINTERNA_H_ */
