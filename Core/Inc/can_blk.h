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

void can_init(/*take in any parameters needed*/);

void can_send(uint32_t msg_id, uint8_t* data, size_t length);



#endif /* INC_CAN_BLK_H_ */
