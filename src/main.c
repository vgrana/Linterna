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


MPU9250_address_t addr = MPU9250_ADDRESS_0;

void onMovimento(void * linterna) {
	((LinternaModel *)linterna)->estadoLinterna=PRENDIDA;

}

void sinMovimiento(void *lint){
	//Maneras diferentes de castear!!
//	LinternaModel * linternaModel = (LinternaModel *) lint;
//		linternaApagada(linternaModel);
	((LinternaModel *)lint)->estadoLinterna=APAGADA;
}

int main(void) {

	boardConfig();
	gpioInit(GPIO0, GPIO_OUTPUT);

//otra manera de inicializar la direccion de memoria
//int8_t mpu9250Init( MPU9250_address_t address );

	LinternaRender linternaRender;
	Sensor sensor;
	LinternaModel linternaModel;

	int8_t status;
	status = mpu9250Init(addr);

	float sensibilidadSensor= 0.2;
	printf("Inicializando IMU MPU9250...\r\n");

	bool_t mpuRead;
	mpuRead = mpu9250Read();

	linternaInit(&linternaModel, 1);
	linternaRender_init(&linternaRender, &linternaModel, GPIO0);
	sensorInitS(&sensor,&linternaModel, status,sensibilidadSensor,mpuRead);
	sensor_conMovimiento(&sensor,onMovimento);
	sensor_sinMovimiento(&sensor,sinMovimiento);


	while (TRUE) {
		sensor_actualizar5(&sensor, status, mpuRead);
		linternaRender_update(&linternaRender);
		linterna_upDate(&linternaModel);
		delay(1);

	}

	return 0;
}
