#include "quick_rotate.h"
#include "pid.h"
#include "remote_control.h"


void Quick_rotate(void)
{
 if(Remote_Control.Key.Z|Remote_Control.Key.X|Remote_Control.Key.C)
 {
  if(Remote_Control.Key.C|Remote_Control.Key.X)
  {	
	 if(Remote_Control.Key.X)
   {
	  WZPid(&Pid.WZ.No8,0,MotoData.moto_8.Rx.angle_change);
 	  Pid.ZL.No8.output=Pid.WZ.No8.output;
   }
   else
   {
	  WZPid(&Pid.WZ.No8,30310,MotoData.moto_8.Rx.angle_change);
	  Pid.ZL.No8.output=Pid.WZ.No8.output;
   }
  }
  else
  {
  	 WZPid(&Pid.WZ.No8,-30310,MotoData.moto_8.Rx.angle_change);
	  Pid.ZL.No8.output=Pid.WZ.No8.output;
  }
 }
}
