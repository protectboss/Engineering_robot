#ifndef __REMOTE_CONTROL_
#define __REMOTE_CONTROL_


#include "moto.h"
#include "usart.h"
#include "dma.h"
#include "usart.h"


typedef struct
{
 int16_t x;
 int16_t y;
 int16_t yaw;
 int16_t pitch;
 int16_t roller;
 char s1;
 char s2;
}RC_TypeDef;


typedef struct
{
 short X;
 short Y;
 short Z;
 char L;
 char R;
}Mouse_ControlTypeDef;


typedef struct
{
unsigned short Board;
unsigned short W;
unsigned short S;
unsigned short A;
unsigned short D;
unsigned short Shift;
unsigned short Ctrl;
unsigned short Q;
unsigned short E;
unsigned short R;
unsigned short F;
unsigned short G;
unsigned short Z;
unsigned short X;
unsigned short C;
unsigned short V;
unsigned short B;
}Key_ControlTypeDef;


typedef struct
{
RC_TypeDef Rc;
Mouse_ControlTypeDef Mouse;
Key_ControlTypeDef Key;
}Controller_TypeDef;


void Remote_Control_Init(void);
void Controller_handler(void);
void IDLE_Handler(void);


extern Controller_TypeDef Remote_Control;


#endif

