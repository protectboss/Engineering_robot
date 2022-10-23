#include "pid.h"


#define LIMIT(x,min,max) x=(x<(min)?min:((x>=max)?max:x))


/*λ��pid*/
void WZPid(WZPID_TypeDef *WZpid,float target,float real)
{
 WZpid->error_last=WZpid->error;
 WZpid->error=target-real;
 WZpid->output=(WZpid->error-WZpid->error_last)*WZpid->Kd;//΢�ֲ���
 WZpid->output+=(WZpid->error*WZpid->Kp);//����
 WZpid->integral+=(WZpid->error*WZpid->Ki);//���ֲ��� 
 LIMIT(WZpid->integral,-WZpid->integral_max,WZpid->integral_max);
 WZpid->output+=WZpid->integral;
 LIMIT(WZpid->output,-WZpid->output_max,WZpid->output_max);
 if(WZpid->error<0)
 {
 if((-WZpid->error)<WZpid->limit)WZpid->output=0;
 }
 else
{
if((WZpid->error)<WZpid->limit)WZpid->output=0;
}
}


/*����pid*/
void ZLPid(ZLPID_TypeDef *ZLpid,float target,float real)
{
 ZLpid->error_last=ZLpid->error;
 ZLpid->error_last_last=ZLpid->error_last;
 ZLpid->error=target-real;
 ZLpid->outputI=(ZLpid->error-ZLpid->error_last)*ZLpid->Kp;
 ZLpid->outputI+=ZLpid->error*ZLpid->Ki;
 ZLpid->outputI+=(ZLpid->error+ZLpid->error_last_last-2*ZLpid->error_last)*ZLpid->Kd;
 LIMIT(ZLpid->outputI,-ZLpid->outputI_max,ZLpid->outputI_max);
 ZLpid->output+=ZLpid->outputI;
 LIMIT(ZLpid->output,-ZLpid->output_max,ZLpid->output_max);
}


/*λ��pid��ֵ*/
void WZPid_Init(WZPID_TypeDef *WZpid,float p,float i,float d,float Integral_max,float Out_max,float limit)
{
 WZpid->Kp=p;
 WZpid->Ki=i;
 WZpid->Kd=d;
 WZpid->integral_max=Integral_max;
 WZpid->output_max=Out_max;
 WZpid->limit=limit;
}


/*����pid��ֵ*/
void ZLPid_Init(ZLPID_TypeDef *ZLpid,float p,float i,float d,float Intergral_max,float Out_max)
{
ZLpid->Kp=p;
ZLpid->Ki=i;
ZLpid->Kd=d;
ZLpid->outputI_max=Intergral_max;
ZLpid->output_max=Out_max;
}


/*����pid��ʼ��*/
PID_TypeDef Pid;
void All_Pid_Init(void)
{
 ZLPid_Init(&Pid.ZL.No1,15,0.5,0.5,16000,16000);
 ZLPid_Init(&Pid.ZL.No2,15,0.5,0.5,16000,16000);
 ZLPid_Init(&Pid.ZL.No3,15,0.5,0.5,16000,16000);
 ZLPid_Init(&Pid.ZL.No4,15,0.5,0.5,16000,16000);
 ZLPid_Init(&Pid.ZL.No5,15,0.5,0.5,16000,16000);
 ZLPid_Init(&Pid.ZL.No6,15,0.5,0.5,10000,10000);
 ZLPid_Init(&Pid.ZL.No7,15,0.5,0.5,10000,10000);
 ZLPid_Init(&Pid.ZL.No8,15,0.5,0.5,10000,10000);
 WZPid_Init(&Pid.WZ.No6,10,0,8,7000,7000,8);//�ǶȻ����ֲ���ȡ�㣬����û����ָ��ʱ�����˶���
 WZPid_Init(&Pid.WZ.No7,10,0,8,7000,7000,8);
 WZPid_Init(&Pid.WZ.No8,0.4,0,6,7000,7000,100);
}


