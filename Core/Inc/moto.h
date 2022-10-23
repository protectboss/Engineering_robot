#ifndef __MOTO_H
#define __MOTO_H


#include "can.h"


typedef struct
{
int16_t angle;
int16_t speed;
int16_t current;
int16_t temperature;
int32_t angle_change;
}MotoData_RxTypeDef;


typedef struct
{
int16_t target_speed;
float target_angle;
int16_t pid_output_current;
}MotoData_TxTypeDef;


typedef struct
{
MotoData_RxTypeDef Rx;
MotoData_TxTypeDef Tx;
}MotoData_TypeDef;


typedef struct
{
MotoData_TypeDef moto_1;
MotoData_TypeDef moto_2;
MotoData_TypeDef moto_3;
MotoData_TypeDef moto_4;
MotoData_TypeDef moto_5;
MotoData_TypeDef moto_6;
MotoData_TypeDef moto_7;
MotoData_TypeDef moto_8;
}MotoNumber_TypeDef;


void CanFilter_Init(void);
void Tx_Moto_Init(void);
void Rx_Moto_Init(void);
void Moto_Init(void);
void Rx_Moto_Init2(void);



void Moto_Current_Output(int16_t Current1,int16_t Current2,int16_t Current3,int16_t Current4);
void Moto_Current_Output2(int16_t Current1,int16_t Current2,int16_t Current3,int16_t Current4);
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan);


extern MotoNumber_TypeDef MotoData;

#endif


