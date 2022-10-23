#ifndef __GYROSCOPE_H_
#define __GYROSCOPE_H_


#include "stm32f4xx_hal.h"


void Gyro1_handler(void);
void Gyro2_handler(void);
void Gyro1_Init(void);
void Gyro2_Init(void);
void IDLE_Gyro1_Handler(void);
void IDLE_Gyro2_Handler(void);


extern float gyro[3],angle1[3],angle2[3],temperate;


extern UART_HandleTypeDef huart6;
extern DMA_HandleTypeDef hdma_usart6_rx;

extern UART_HandleTypeDef huart8;
extern DMA_HandleTypeDef hdma_uart8_rx;


#endif 
