/*
 * ozone_sensor_blk.h
 *
 *  Created on: Jul 18, 2025
 *      Author: connor
 */

#ifndef INC_OZONE_SENSOR_BLK_H_
#define INC_OZONE_SENSOR_BLK_H_
#include "stm32f1xx_hal.h"


typedef struct {
    I2C_HandleTypeDef *hi2c;
    uint8_t address;
} OzoneSensor;

uint8_t ozone_sensor_init(OzoneSensor *sensor, I2C_HandleTypeDef *hi2c, uint8_t address);

double ozone_sensor_read(OzoneSensor *sensor);

#endif /* INC_OZONE_SENSOR_BLK_H_ */
