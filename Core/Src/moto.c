#include "moto.h"
#include "angle.h"
#include "pid.h"


void Moto_Init(void)
{
CanFilter_Init();
Tx_Moto_Init();
Rx_Moto_Init();
Rx_Moto_Init2();
HAL_CAN_ActivateNotification(&hcan1,CAN_IT_RX_FIFO0_MSG_PENDING);//ʹ���жϣ���FIFO0���ܵ�����ʱ�����ж�
HAL_CAN_ActivateNotification(&hcan2,CAN_IT_RX_FIFO0_MSG_PENDING);
}


/*��������ʼ��*/
void CanFilter_Init(void)
{
 CAN_FilterTypeDef Canfilter;

 Canfilter.FilterMode=CAN_FILTERMODE_IDMASK;
 Canfilter.FilterScale=CAN_FILTERSCALE_32BIT;
 Canfilter.FilterIdHigh=0x0200<<5;
 Canfilter.FilterIdLow=0x0000;
 Canfilter.FilterMaskIdHigh=0x03F0<<5;
 Canfilter.FilterMaskIdLow=0x0000;
 Canfilter.FilterFIFOAssignment=CAN_FilterFIFO0;
 Canfilter.FilterActivation=CAN_FILTER_ENABLE;
 Canfilter.FilterBank=0;
 Canfilter.SlaveStartFilterBank=14;

 HAL_CAN_ConfigFilter(&hcan1,&Canfilter);
	
	
CAN_FilterTypeDef Canfilter2;
 
 Canfilter2.FilterMode=CAN_FILTERMODE_IDMASK;
 Canfilter2.FilterScale=CAN_FILTERSCALE_32BIT;
 Canfilter2.FilterIdHigh=0x0200<<5;
 Canfilter2.FilterIdLow=0x0000;
 Canfilter2.FilterMaskIdHigh=0x03F0<<5;
 Canfilter2.FilterMaskIdLow=0x0000;
 Canfilter2.FilterFIFOAssignment=CAN_FilterFIFO0;
 Canfilter2.FilterActivation=CAN_FILTER_ENABLE;
 Canfilter2.FilterBank=14;

 HAL_CAN_ConfigFilter(&hcan2,&Canfilter2);
}


/*���ͳ�ʼ��*/
CAN_TxHeaderTypeDef Can_HandleTxMsg2;
CAN_TxHeaderTypeDef Can_HandleTxMsg;
void Tx_Moto_Init(void)
{
Can_HandleTxMsg.StdId=0x200;
Can_HandleTxMsg.ExtId=0x00;
Can_HandleTxMsg.IDE=CAN_ID_STD;
Can_HandleTxMsg.RTR=CAN_RTR_DATA;
Can_HandleTxMsg.DLC=8;
Can_HandleTxMsg.TransmitGlobalTime=DISABLE;
		
Can_HandleTxMsg2.StdId=0x1FF;
Can_HandleTxMsg2.ExtId=0x00;
Can_HandleTxMsg2.IDE=CAN_ID_STD;
Can_HandleTxMsg2.RTR=CAN_RTR_DATA;
Can_HandleTxMsg2.DLC=8;
Can_HandleTxMsg2.TransmitGlobalTime=DISABLE;
}


/*�������ݴ���*/
uint8_t TX_MOTO_CURRENT[8];
void Moto_Current_Output(int16_t Current1,int16_t Current2,int16_t Current3,int16_t Current4)
{

	
 TX_MOTO_CURRENT[0]=(uint8_t)(Current1>>8);
 TX_MOTO_CURRENT[1]=(uint8_t)Current1;
	
 TX_MOTO_CURRENT[2]=(uint8_t)(Current2>>8);
 TX_MOTO_CURRENT[3]=(uint8_t)Current2;
	
 TX_MOTO_CURRENT[4]=(uint8_t)(Current3>>8);
 TX_MOTO_CURRENT[5]=(uint8_t)Current3;
	
 TX_MOTO_CURRENT[6]=(uint8_t)(Current4>>8);
 TX_MOTO_CURRENT[7]=(uint8_t)Current4;
	
 HAL_CAN_AddTxMessage(&hcan1,&Can_HandleTxMsg,TX_MOTO_CURRENT,0);
}


uint8_t TX_MOTO_CURRENT2[8];//���1-4�ŵ��ٶ�(����)���ݴ���
void Moto_Current_Output2(int16_t Current1,int16_t Current2,int16_t Current3,int16_t Current4)
{ 
	
 TX_MOTO_CURRENT2[0]=(uint8_t)(Current1>>8);
 TX_MOTO_CURRENT2[1]=(uint8_t)Current1;
	
 TX_MOTO_CURRENT2[2]=(uint8_t)(Current2>>8);
 TX_MOTO_CURRENT2[3]=(uint8_t)Current2;
	
 TX_MOTO_CURRENT2[4]=(uint8_t)(Current3>>8);
 TX_MOTO_CURRENT2[5]=(uint8_t)Current3;
	
 TX_MOTO_CURRENT2[6]=(uint8_t)(Current4>>8);
 TX_MOTO_CURRENT2[7]=(uint8_t)Current4;
	
 HAL_CAN_AddTxMessage(&hcan1,&Can_HandleTxMsg2,TX_MOTO_CURRENT2,0);
 HAL_CAN_AddTxMessage(&hcan2,&Can_HandleTxMsg2,TX_MOTO_CURRENT2,0);
}	


/*�������ݳ�ʼ��*/
CAN_RxHeaderTypeDef CAN_HandleRxMsg;
CAN_RxHeaderTypeDef CAN_HandleRxMsg2;
void Rx_Moto_Init(void)
{
CAN_HandleRxMsg.StdId=0x01;
CAN_HandleRxMsg.ExtId=0x00;
CAN_HandleRxMsg.IDE=CAN_ID_STD;
CAN_HandleRxMsg.RTR=CAN_RTR_DATA;
CAN_HandleRxMsg.DLC=0;
CAN_HandleRxMsg.Timestamp=0;
CAN_HandleRxMsg.FilterMatchIndex=0;
	
}

void Rx_Moto_Init2(void)
{
CAN_HandleRxMsg2.StdId=0x01;
CAN_HandleRxMsg2.ExtId=0x00;
CAN_HandleRxMsg2.IDE=CAN_ID_STD;
CAN_HandleRxMsg2.RTR=CAN_RTR_DATA;
CAN_HandleRxMsg2.DLC=0;
CAN_HandleRxMsg2.Timestamp=0;
CAN_HandleRxMsg2.FilterMatchIndex=0;
}


/*�����жϣ�can�������ݷ��������ݽṹ��*/
uint8_t RX_MOTO_DATA[8];
uint8_t RX_MOTO_DATA2[8];
uint32_t Protect_Number6;
uint32_t Protect_Number7;
int32_t mot1_output_last;

MotoNumber_TypeDef MotoData;
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	if(hcan == &hcan1)//�����ǲ���can1�����ݣ���ߵ���õö����Ҫ����can2�����������һ���������
	{
	HAL_CAN_GetRxMessage(&hcan1,CAN_RX_FIFO0,&CAN_HandleRxMsg,RX_MOTO_DATA);///�����жϺ��ٵ���һ�ν��պ������������Ž��գ�����ͣ�½�������
	switch(CAN_HandleRxMsg.StdId)
	{
		case 0x201:
		{
		MotoData.moto_1.Rx.angle=((uint16_t)RX_MOTO_DATA[0]<<8|(uint16_t)RX_MOTO_DATA[1]);
		MotoData.moto_1.Rx.speed=((uint16_t)RX_MOTO_DATA[2]<<8|(uint16_t)RX_MOTO_DATA[3]);
		MotoData.moto_1.Rx.current=((uint16_t)RX_MOTO_DATA[4]<<8|(uint16_t)RX_MOTO_DATA[5]);
		MotoData.moto_1.Rx.temperature=(uint16_t)RX_MOTO_DATA[6];
		mot1_output_last=Pid.ZL.No1.output;
		}break;
		case 0x202:
		{
		MotoData.moto_2.Rx.angle=((uint16_t)RX_MOTO_DATA[0]<<8|(uint16_t)RX_MOTO_DATA[1]);
		MotoData.moto_2.Rx.speed=((uint16_t)RX_MOTO_DATA[2]<<8|(uint16_t)RX_MOTO_DATA[3]);
		MotoData.moto_2.Rx.current=((uint16_t)RX_MOTO_DATA[4]<<8|(uint16_t)RX_MOTO_DATA[5]);
		MotoData.moto_2.Rx.temperature=(uint16_t)RX_MOTO_DATA[6];
		}break;
    case 0x203:
		{
		MotoData.moto_3.Rx.angle=((uint16_t)RX_MOTO_DATA[0]<<8|(uint16_t)RX_MOTO_DATA[1]);
		MotoData.moto_3.Rx.speed=((uint16_t)RX_MOTO_DATA[2]<<8|(uint16_t)RX_MOTO_DATA[3]);
		MotoData.moto_3.Rx.current=((uint16_t)RX_MOTO_DATA[4]<<8|(uint16_t)RX_MOTO_DATA[5]);
		MotoData.moto_3.Rx.temperature=(uint16_t)RX_MOTO_DATA[6];
		}break;	
		case 0x204:
		{
		MotoData.moto_4.Rx.angle=((uint16_t)RX_MOTO_DATA[0]<<8|(uint16_t)RX_MOTO_DATA[1]);
		MotoData.moto_4.Rx.speed=((uint16_t)RX_MOTO_DATA[2]<<8|(uint16_t)RX_MOTO_DATA[3]);
		MotoData.moto_4.Rx.current=((uint16_t)RX_MOTO_DATA[4]<<8|(uint16_t)RX_MOTO_DATA[5]);
		MotoData.moto_4.Rx.temperature=(uint16_t)RX_MOTO_DATA[6];
		}break;
		case 0x205:
		{
		MotoData.moto_5.Rx.angle=((uint16_t)RX_MOTO_DATA[0]<<8|(uint16_t)RX_MOTO_DATA[1]);
		MotoData.moto_5.Rx.speed=((uint16_t)RX_MOTO_DATA[2]<<8|(uint16_t)RX_MOTO_DATA[3]);
		MotoData.moto_5.Rx.current=((uint16_t)RX_MOTO_DATA[4]<<8|(uint16_t)RX_MOTO_DATA[5]);
		MotoData.moto_5.Rx.temperature=(uint16_t)RX_MOTO_DATA[6];
		}break;
  }
	if(HAL_CAN_ActivateNotification(&hcan1,CAN_IT_RX_FIFO0_MSG_PENDING)!=HAL_OK)///����жϹ����Ƿ�����������Ļ�����������
	  {
		  __HAL_CAN_ENABLE_IT(&hcan1,CAN_IT_RX_FIFO0_MSG_PENDING);
   	}
	 Angle_Turn(&MotoData.moto_5.Rx,&Angle.No5,8192);
	}
if(hcan == &hcan2)//�����ǲ���can1�����ݣ���ߵ���õö����Ҫ����can2�����������һ���������
	{
	HAL_CAN_GetRxMessage(&hcan2,CAN_RX_FIFO0,&CAN_HandleRxMsg2,RX_MOTO_DATA2);///�����жϺ��ٵ���һ�ν��պ������������Ž��գ�����ͣ�½�������
	switch(CAN_HandleRxMsg2.StdId)
	{
		case 0x206:
		{
		MotoData.moto_6.Rx.angle=((uint16_t)RX_MOTO_DATA2[0]<<8|(uint16_t)RX_MOTO_DATA2[1]);
		MotoData.moto_6.Rx.speed=((uint16_t)RX_MOTO_DATA2[2]<<8|(uint16_t)RX_MOTO_DATA2[3]);
		MotoData.moto_6.Rx.current=((uint16_t)RX_MOTO_DATA2[4]<<8|(uint16_t)RX_MOTO_DATA2[5]);
		MotoData.moto_6.Rx.temperature=(uint16_t)RX_MOTO_DATA2[6];
		Protect_Number6=1;
		}break;
		case 0x207:
		{
		MotoData.moto_7.Rx.angle=((uint16_t)RX_MOTO_DATA2[0]<<8|(uint16_t)RX_MOTO_DATA2[1]);
		MotoData.moto_7.Rx.speed=((uint16_t)RX_MOTO_DATA2[2]<<8|(uint16_t)RX_MOTO_DATA2[3]);
		MotoData.moto_7.Rx.current=((uint16_t)RX_MOTO_DATA2[4]<<8|(uint16_t)RX_MOTO_DATA2[5]);
		MotoData.moto_7.Rx.temperature=(uint16_t)RX_MOTO_DATA2[6];
		Protect_Number7=1;
		}break;
		case 0x208:
		{
		MotoData.moto_8.Rx.angle=((uint16_t)RX_MOTO_DATA2[0]<<8|(uint16_t)RX_MOTO_DATA2[1]);
		MotoData.moto_8.Rx.speed=((uint16_t)RX_MOTO_DATA2[2]<<8|(uint16_t)RX_MOTO_DATA2[3]);
		MotoData.moto_8.Rx.current=((uint16_t)RX_MOTO_DATA2[4]<<8|(uint16_t)RX_MOTO_DATA2[5]);
		MotoData.moto_8.Rx.temperature=(uint16_t)RX_MOTO_DATA2[6];
		}break;
	}
	  Angle_Turn(&MotoData.moto_6.Rx,&Angle.No6,8192);
  	Angle_Turn(&MotoData.moto_7.Rx,&Angle.No7,8192);
	  No8_Angle_Turn(&MotoData.moto_8.Rx,&Angle.No8,8192);

  }
	if(HAL_CAN_ActivateNotification(&hcan2,CAN_IT_RX_FIFO0_MSG_PENDING)!=HAL_OK)///����жϹ����Ƿ�����������Ļ�����������
	  {
		  __HAL_CAN_ENABLE_IT(&hcan2,CAN_IT_RX_FIFO0_MSG_PENDING);
   	}

}

