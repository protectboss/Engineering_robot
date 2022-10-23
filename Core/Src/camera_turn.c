#include "camera_turn.h"


void Camera_turn(void)
{
 if(Remote_Control.Key.Ctrl|Remote_Control.Key.Shift)
 {
 if(Remote_Control.Key.Ctrl)	__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_4,1500);
 else __HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_4,500);
 }
}

