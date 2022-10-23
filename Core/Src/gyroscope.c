#include "gyroscope.h"
#include "usart.h"


uint8_t Gyro1_Data[22],Gyro2_Data[22];
float gyro[3],angle1[3],angle2[3],temperate;
int16_t yaw_gyro1_angle,pitch_gyro1_angle;
int16_t yaw_gyro2_angle,pitch_gyro2_angle;


/**
* @brief  ���������ݴ�����
* @param  None
* @return None
*/
void Gyro1_handler(void)
{
	if(Gyro1_Data[0]== 0x55)
	{
		/*��������200Hz����̬������*/
		angle1[0]=((int16_t)(Gyro1_Data[2] | (int16_t)Gyro1_Data[3] << 8))/32768.0*180;
		angle1[1]=((int16_t)(Gyro1_Data[4] | (int16_t)Gyro1_Data[5] << 8))/32768.0*180;
		angle1[2]=((int16_t)(Gyro1_Data[6] | (int16_t)Gyro1_Data[7] << 8))/32768.0*180;
	}
}


void Gyro2_handler(void)
{
	if(Gyro2_Data[0]== 0x55)
	{
		/*��������200Hz����̬������*/
		angle2[0]=((int16_t)(Gyro2_Data[2] | (int16_t)Gyro2_Data[3] << 8))/32768.0*180;
		angle2[1]=((int16_t)(Gyro2_Data[4] | (int16_t)Gyro2_Data[5] << 8))/32768.0*180;
		angle2[2]=((int16_t)(Gyro2_Data[6] | (int16_t)Gyro2_Data[7] << 8))/32768.0*180;
	}
}


/**
* @brief  �����ǽ��ճ�ʼ������
* @param  None
* @return None
*/
void Gyro1_Init(void)
{
	__HAL_UART_CLEAR_IDLEFLAG(&huart8);
	__HAL_UART_ENABLE_IT(&huart8,UART_IT_IDLE);
  HAL_UART_Receive_DMA(&huart8,Gyro1_Data,22);
}
/**
* @brief  ������DMA�����ж�У�����ݺ���
* @param  None
* @return None
*/
void IDLE_Gyro1_Handler(void)
{
	
	uint32_t Data_lave,Data_exist; 
		if((__HAL_UART_GET_FLAG(&huart8,UART_FLAG_IDLE)!= RESET))  
		{
			__HAL_UART_CLEAR_IDLEFLAG(&huart8);
			
			HAL_UART_DMAStop(&huart8); 
			
			Data_lave = __HAL_DMA_GET_COUNTER(&hdma_uart8_rx); 

			Data_exist = 22-Data_lave; 

			if(Data_exist == 11)  
			{
				Gyro1_handler();
			}
			HAL_UART_Receive_DMA(&huart8,Gyro1_Data,22); 
		}
}

/**
* @brief  �����ǽ��ճ�ʼ������
* @param  None
* @return None
*/
void Gyro2_Init(void)
{
	__HAL_UART_CLEAR_IDLEFLAG(&huart6);
	__HAL_UART_ENABLE_IT(&huart6,UART_IT_IDLE);
  HAL_UART_Receive_DMA(&huart6,Gyro2_Data,22);
}
/**
* @brief  ������DMA�����ж�У�����ݺ���
* @param  None
* @return None
*/
void IDLE_Gyro2_Handler(void)
{
	
	uint32_t Data_lave,Data_exist; 
		if((__HAL_UART_GET_FLAG(&huart6,UART_FLAG_IDLE)!= RESET))  
		{
			__HAL_UART_CLEAR_IDLEFLAG(&huart6);
			
			HAL_UART_DMAStop(&huart6); 
			
			Data_lave = __HAL_DMA_GET_COUNTER(&hdma_usart6_rx); 

			Data_exist = 22-Data_lave; 

			if(Data_exist == 11)  
			{
				Gyro2_handler();
			}
			HAL_UART_Receive_DMA(&huart6,Gyro2_Data,22); 
		}
}

