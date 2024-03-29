/*
 * main.c
 *
 *  Created on: 30 sep. 2019
 *      Author: valeria
 */
#include "sapi.h"
#include "Linterna.h"
#include "LinternaRender.h"
#include "Sensor.h"
#include "Tecla.h"
#define TIEMPO 10
MPU9250_address_t addr = MPU9250_ADDRESS_0;


void onMovimento(void * linterna) {
		LinternaModel * model = (LinternaModel *) linterna;
		linternaEncendida(linterna);
}

void sinMovimiento(void * lint) {
}

int main(void) {

	boardConfig();
	gpioInit(GPIO0, GPIO_OUTPUT);

//otra manera de inicializar la direccion de memoria
//int8_t mpu9250Init( MPU9250_address_t address );

	LinternaRender linternaRender;
	Sensor sensor;
	LinternaModel linternaModel;
	Tecla tecla;

	int8_t status;
	status = mpu9250Init(addr);

	float sensibilidadSensor = 0.2;
	printf("Inicializando IMU MPU9250...\r\n");

	bool_t mpuRead;
	mpuRead = mpu9250Read();

	tecla_init(&tecla, TEC1, (void *) &linternaModel);
	tecla_onPress(&tecla,onMovimento);
	tecla_onRelease(&tecla,sinMovimiento);


	linternaInit(&linternaModel, APAGADA);//PRENDIDA
	linternaRender_init(&linternaRender, &linternaModel, GPIO0);

	sensorInitS(&sensor, &linternaModel, status, sensibilidadSensor, mpuRead);
	sensor_sinMovimiento(&sensor,sinMovimiento);
	sensor_conMovimiento(&sensor,onMovimento);

	while (TRUE) {
		tecla_update(&tecla);
		sensor_actualizar5(&sensor, status, mpuRead);
		linterna_upDate(&linternaModel);
		linternaRender_update(&linternaRender);
		delay(1);

	}

	return 0;
}
