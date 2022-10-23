#ifndef __JOINT_H_
#define __JOINT_H_


#include "gpio.h"


void JointData_processing(void);
void synchronization(void);
void Joint_Init(void);
void Joint_Down(int PWM);
void Joint_Up(int PWM);
void Joint_Stop(void);
void Joint_Control(void);
void Joint_Direction(int PWM);

#endif

