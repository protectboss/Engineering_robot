#ifndef __QUICK_CLAMPING_H_
#define __QUICK_CLAMPING_H_

#include "usart.h"


#define Pi 3.1416f

#define L1  33.8f
#define L1f 1142.44f
#define L2  33.1f
#define L2f 1095.61f
#define L3  31.7f

#define initial_x 36.8f


int16_t Arm_Out1(int16_t x,int16_t y,float angle,float p);
int16_t Arm_Out2(int16_t x,int16_t y,float angle,float p);
void Quick_Joint_Move(float x,float y,float P1, float P2);
void Quick_Joint_Remote_control(void);


#endif 
