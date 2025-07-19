/*
 * can_blk.c
 *
 *  Created on: Jul 18, 2025
 *      Author: connor
 */
#include "can_blk.h"
#include "stm32f1xx_hal.h"


static CAN_HandleTypeDef hcan;
static CAN_TxHeaderTypeDef TxHeader = {.ExtId = 0, .IDE = CAN_ID_STD, .RTR = CAN_RTR_DATA, .TransmitGlobalTime = DISABLE};

static uint32_t TxMailbox;
static uint32_t RxMailBox;


void can_init(/*take in any parameters needed*/) {
	  HAL_CAN_Start(&hcan);
	  HAL_CAN_ActivateNotification(&hcan,CAN_IT_RX_FIFO0_MSG_PENDING);
	return;
}

void can_send(uint32_t msg_id, uint8_t* data, size_t length) {

	CAN_TxHeaderTypeDef TxConfig;      // local Txheader configuration

	TxConfig = TxHeader;

	if (length <= 8 )
	{

		TxConfig.StdId = msg_id;
		TxConfig.DLC = length;
		HAL_CAN_AddTxMessage(&hcan,&TxConfig,data,&TxMailbox);
	}

	return;
}
