#include "remote_control.h"


uint8_t controller_data[36];
uint32_t Remote_Control_Normal;


/*遥控器灵敏度*/
#define Rc_Sent_X 3
#define Rc_Sent_Y 3
#define Rc_Sent_yaw 3
#define Rc_sent_roller 1


/*遥控器通讯正常判断位*/
#define Signal_Normal 1


void Remote_Control_Init(void)
{
 __HAL_UART_CLEAR_IDLEFLAG(&huart1);
 __HAL_UART_ENABLE_IT(&huart1,UART_IT_IDLE);
 HAL_UART_Receive_DMA(&huart1,controller_data,36);
}


Controller_TypeDef Remote_Control;
void Controller_handler(void)
{
	/*数据位移*/
 unsigned short direction[4];
 direction[0]=((int16_t)controller_data[0]|((int16_t)controller_data[1]<<8)) & 0x07FF;
 direction[1]=(((int16_t)controller_data[1]>> 3)|((int16_t)controller_data[2]<< 5))&0x07FF;
 direction[2]=(((int16_t)controller_data[2]>> 6)|((int16_t)controller_data[3]<< 2)|((int16_t)controller_data[4]<<10))&0x07FF;
 direction[3]=(((int16_t)controller_data[4]>> 1)|((int16_t)controller_data[5]<<7))&0x07FF;
 
	/*遥控器数据*/
 Remote_Control.Rc.yaw=((direction[0]-1024)*Rc_Sent_yaw);
 //Remote_Control.Rc.pitch=(direction[1]-1024);
 Remote_Control.Rc.x=((direction[2]-1024)*Rc_Sent_X);
 Remote_Control.Rc.y=((direction[3]-1024)*Rc_Sent_Y);
 Remote_Control.Rc.s1=((controller_data[5]>>4)&0x00C)>>2;
 Remote_Control.Rc.s2=((controller_data[5]>>4)&0x003);
 Remote_Control.Rc.roller=(((((int16_t)controller_data[16])|(int16_t)controller_data[17]<<8)&0x07FF)-1024)*Rc_sent_roller;


	/*键盘数据*/
	Remote_Control.Key.Board =  ((int16_t)controller_data[14]) | ((int16_t)controller_data[15]<<8);
	Remote_Control.Key.W=((Remote_Control.Key.Board>>0)&0x01);
	Remote_Control.Key.S=((Remote_Control.Key.Board>>1)&0x01);
	Remote_Control.Key.A=((Remote_Control.Key.Board>>2)&0x01);
	Remote_Control.Key.D=((Remote_Control.Key.Board>>3)&0x01);
	Remote_Control.Key.Shift=((Remote_Control.Key.Board>>4)&0x01);
	Remote_Control.Key.Ctrl=((Remote_Control.Key.Board>>5)&0x01);
	Remote_Control.Key.Q=((Remote_Control.Key.Board>>6)&0x01);
	Remote_Control.Key.E=((Remote_Control.Key.Board>>7)&0x01);
	Remote_Control.Key.R=((Remote_Control.Key.Board>>8)&0x01);
	Remote_Control.Key.F=((Remote_Control.Key.Board>>9)&0x01);
	Remote_Control.Key.G=((Remote_Control.Key.Board>>10)&0x01);
	Remote_Control.Key.Z=((Remote_Control.Key.Board>>11)&0x01);
	Remote_Control.Key.X=((Remote_Control.Key.Board>>12)&0x01);
	Remote_Control.Key.C=((Remote_Control.Key.Board>>13)&0x01);
	Remote_Control.Key.V=((Remote_Control.Key.Board>>14)&0x01);
	Remote_Control.Key.B=((Remote_Control.Key.Board>>15)&0x01);
	
	/*鼠标数据*/
	Remote_Control.Mouse.X=((int16_t)controller_data[6])|((int16_t)controller_data[7]<<8);
	Remote_Control.Mouse.Y=((int16_t)controller_data[8])|((int16_t)controller_data[9]<<8);
	Remote_Control.Mouse.Z=((int16_t)controller_data[10])|((int16_t)controller_data[11]<<8);
	Remote_Control.Mouse.L=controller_data[12];
	Remote_Control.Mouse.R=controller_data[13];
}


/*DMA空闲中断校验位数据函数*/
void IDLE_Handler(void)
{
 uint32_t Data_lave,Data_exist;
 if((__HAL_UART_GET_FLAG(&huart1,UART_FLAG_IDLE)!=RESET))//判断是否进入空闲中断
	{
   __HAL_UART_CLEAR_IDLEFLAG(&huart1);//清除UART空闲中断标志位
	 HAL_UART_DMAStop(&huart1);//关闭DMA避免受到干扰
	 Data_lave =__HAL_DMA_GET_COUNTER(&hdma_usart1_rx);//获取进入空闲中断时，DMA所剩的空间字节数，总的空间是36字节
	 Data_exist=36-Data_lave;//总的空间字数-剩余的空间字节数	= 已经接受的字节数
	 if(Data_exist == 18)     //如果本次DMA传输接受到18个字节的数据，则该数据是正确的，进入数据处理函数
	  {
	   Remote_Control_Normal=Signal_Normal;
		 Controller_handler();//遥控数据拼接处理
	  }
	 HAL_UART_Receive_DMA(&huart1,controller_data,36);//重新打开DMA的接收功能
  }	 
}

