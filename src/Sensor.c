/*
 * Sensor.c
 *
 *  Created on: 4 oct. 2019
 *      Author: valeria
 */
#include "Sensor.h"
#include "sapi.h"
#include "Linterna.h"

void nullHandler1(void *);
void cambioEstado(Sensor *sensor, EstadoSensor estadoSensor);
void initTiempoEntreMediciones(Sensor * sensor);

void sensorInitS(Sensor * sensor, void * model, int8_t direccionInicial,
		float sensibilidadSensor, bool_t estadoInicial) {
	mpu9250Read();
	sensor->direccionInicial = direccionInicial;
	sensor->model = model;
	sensor->estadoInicial = mpu9250Read();
	sensor->ultimoCambioX = mpu9250GetAccelX_mss();
	sensor->ultimoCambioY = mpu9250GetAccelY_mss();
	sensor->ultimoCambioZ = mpu9250GetAccelZ_mss();
	sensor->estadoSensor = Up;
	sensor->enMovimiento = nullHandler1;
	sensor->sinMovimiento = nullHandler1;
	sensor->sensibilidadSensor = sensibilidadSensor;

}

void sensor_conMovimiento(Sensor * sensor, EventHandler event) {
	sensor->enMovimiento = event;
}
void sensor_sinMovimiento(Sensor * sensor, EventHandler event) {
	sensor->sinMovimiento = event;
}
void nullHandler1(void * model) {
}

void cambioEstado(Sensor *sensor, EstadoSensor estadoSensor) {
	sensor->estadoSensor = estadoSensor;
}
void initTiempoEntreMediciones(Sensor * sensor) {
	delayInit(&sensor->tiempoEntreMedicion, 100);
}

void sensor_actualizar5(Sensor * sensor, int8_t direccion, bool_t estadoInicial) {
	sensor->direccionInicial = direccion;
	mpu9250Read();
	float estadoActualX = mpu9250GetAccelX_mss();
	float estadoActualY = mpu9250GetAccelY_mss();
	float estadoActualZ = mpu9250GetAccelZ_mss();

	float variacionX = estadoActualX - sensor->ultimoCambioX;
	float variacionY = estadoActualY - sensor->ultimoCambioY;
	float variacionZ = estadoActualZ - sensor->ultimoCambioZ;

	switch (sensor->estadoSensor) {

	case Up: {
		if ((variacionX > sensor->sensibilidadSensor)
				|| (variacionY > sensor->sensibilidadSensor)
				|| (variacionZ > sensor->sensibilidadSensor)) {

			cambioEstado(sensor, Movido);
			initTiempoEntreMediciones(sensor);

			sensor->ultimoCambioX = estadoActualX;
			sensor->ultimoCambioY = estadoActualY;
			sensor->ultimoCambioZ = estadoActualZ;

		} else {
			cambioEstado(sensor, Estatico);
		}
		break;
	}

	case Movido: {
		if (delayRead(&sensor->tiempoEntreMedicion)) {
			if ((variacionX > sensor->sensibilidadSensor)
					|| (variacionY > sensor->sensibilidadSensor)
					|| (variacionZ > sensor->sensibilidadSensor)) {

				cambioEstado(sensor, Up);
				initTiempoEntreMediciones(sensor);
				sensor->enMovimiento(sensor->model);
				printf(
						"estoy en movido  estadoActualX %f ,últimoCambioX: %f ,variaciónX%f \n",
						estadoActualX, sensor->ultimoCambioX, variacionX);
				printf("estoy en movido estadoActualY= %f, %f últimoCambio, "
						"%variaciónY  %f \n", estadoActualY,
						sensor->ultimoCambioY, variacionY);
				printf("estoy en movido estadoActualz= %f, %f últimoCambio, "
						"%variaciónZ  %f \n", estadoActualZ,
						sensor->ultimoCambioZ, variacionZ);

			} else {
				cambioEstado(sensor, Estatico);
				initTiempoEntreMediciones(sensor);

			}
		}
		break;
	}
	case Estatico: {
		if (delayRead(&sensor->tiempoEntreMedicion)) {
			if ((variacionX < sensor->sensibilidadSensor)
					|| (variacionY < sensor->sensibilidadSensor)
					|| (variacionZ < sensor->sensibilidadSensor)) {

				cambioEstado(sensor, Up);
				initTiempoEntreMediciones(sensor);
				sensor->sinMovimiento(sensor->model);
				printf("estoy en estático\n ");
				printf(
						"estoy en estático estadoActualX %f  , últimoCambioX: %f,variaciónX%f \n",
						estadoActualX, sensor->ultimoCambioX, variacionX);

				printf(
						"estoy en estático estadoActualY %f, últimoCambioX: %f, variaciónY %f\n",
						estadoActualY, sensor->ultimoCambioY, variacionY);

				printf(
						"estoy en estático  estadoActualZ %f, últimoCambioZ %f, variaciónZ: %f \n \n",
						estadoActualZ, sensor->ultimoCambioZ, variacionZ);

			} else {
				cambioEstado(sensor, Movido);
				initTiempoEntreMediciones(sensor);
				sensor->ultimoCambioX = estadoActualX;
				sensor->ultimoCambioY = estadoActualY;
				sensor->ultimoCambioZ = estadoActualZ;

			}
		}
		break;
	}
	}
}
