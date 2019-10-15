/*
 * Sensor.h
 *
 *  Created on: 4 oct. 2019
 *      Author: valeria
 */

#ifndef PROGRAMS_PRENDERAPAGAR_SENSOR_INC_SENSOR_H_
#define PROGRAMS_PRENDERAPAGAR_SENSOR_INC_SENSOR_H_

#include <sapi.h>
typedef enum {
	Up, Movido, Estatico,
} EstadoSensor;

typedef void (*EventHandler)(void *);

typedef struct {
	void * model;
	EstadoSensor estadoSensor;
	int8_t direccionInicial;
	EventHandler enMovimiento;
	EventHandler sinMovimiento;
	float ultimoCambioX;
	float ultimoCambioY;
	float ultimoCambioZ;
	float sensibilidadSensor;
	delay_t tiempoEntreMedicion;
	delay_t ultimaVezMedido;
	bool_t estadoInicial;

} Sensor;

void sensorInitS(Sensor * sensor, void * model, int8_t direccionInicial,float sensibilidadSensor, bool_t estadoInicial);
void sensor_conMovimiento(Sensor * sensor, EventHandler event);
void sensor_sinMovimiento(Sensor * sensor, EventHandler handler);
void sensor_actualizar5(Sensor * sensor, int8_t direccionInicial,bool_t estadoInicial);
#endif /* PROGRAMS_PRENDERAPAGAR_SENSOR_INC_SENSOR_H_ */
