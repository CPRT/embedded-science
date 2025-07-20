/*
 * can_blk.c
 *
 *  Created on: Jul 18, 2025
 *      Author: connor
 */
#include "can_blk.h"


static CAN_TxHeaderTypeDef TxHeader = {.ExtId = 0, .IDE = CAN_ID_STD, .RTR = CAN_RTR_DATA, .TransmitGlobalTime = DISABLE};

//TODO(Jon): Move to ctx struct
static uint32_t TxMailbox;
static uint32_t RxMailBox;


void can_init(CAN_HandleTypeDef* hcan) {
	  CAN_FilterTypeDef filterConfig;
	  filterConfig.FilterActivation = ENABLE;
	  filterConfig.FilterBank = 0;
	  filterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	  filterConfig.FilterIdHigh = 0x0000;
	  filterConfig.FilterIdLow = 0x0000;
	  filterConfig.FilterMaskIdHigh = 0x0000;
	  filterConfig.FilterMaskIdLow = 0x0000;
	  filterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	  filterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	  HAL_CAN_ConfigFilter(hcan, &filterConfig);
	  HAL_CAN_Start(hcan);
	  HAL_CAN_ActivateNotification(hcan,CAN_IT_RX_FIFO0_MSG_PENDING);
	return;
}

void can_send(CAN_HandleTypeDef* hcan, uint32_t msg_id, uint8_t* data, size_t length) {

	CAN_TxHeaderTypeDef TxConfig;      // local Txheader configuration

	TxConfig = TxHeader;

	if (length <= 8 )
	{
		TxConfig.StdId = msg_id;
		TxConfig.DLC = length;
		HAL_CAN_AddTxMessage(hcan,&TxConfig,data,&TxMailbox);
	}

	return;
}
