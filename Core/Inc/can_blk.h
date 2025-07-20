/*
 * can_blk.h
 *
 *  Created on: Jul 18, 2025
 *      Author: connor
 */

#ifndef INC_CAN_BLK_H_
#define INC_CAN_BLK_H_
#include <stdint.h>
#include <stddef.h>
#include "stm32f1xx_hal.h"

void can_init(CAN_HandleTypeDef* hcan);

void can_send(CAN_HandleTypeDef* hcan, uint32_t msg_id, uint8_t* data, size_t length);



#endif /* INC_CAN_BLK_H_ */
