/*
 * hydrogen_sensor_blk.c
 *
 *  Created on: Jul 18, 2025
 *      Author: connor
 */

#include "hydrogen_sensor_blk.h"
#include <string.h>
#include <math.h>

#define RL_VALUE 10
#define RO_CLEAN_AIR_FACTOR 9.21

float sense;
char msg[20];
float H2Curve[3] = {2.3, 0.93, -1.44};
float Ro = 10;

void hydrogen_sensor_init(/*add any parameters needed*/) {
	float MQResistanceCalculation(float raw_adc){
	return (((float)RL_VALUE*(4095-raw_adc)/raw_adc));
}

float MQCalibration(){
	float val = 0;
	for (int i = 0; i < 50; i++){
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, 20);
		val += MQResistanceCalculation(HAL_ADC_GetValue(&hadc1));
		HAL_Delay(50);
	}
	val = val/50;
	val = val/RO_CLEAN_AIR_FACTOR;
	return val;
}

float MQRead(){
	float rs = 0;
	for(int i = 0; i <50; i++){
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, 20);
		rs += MQResistanceCalculation(HAL_ADC_GetValue(&hadc1));
		HAL_Delay(50);
	}

	rs = rs/50;
	return rs;
}
	return;
}

double hydrogen_sensor_read() {
	//TODO: Implement me
	return 1.0;
}
