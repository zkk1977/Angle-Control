#include "pid.h"
#include "tim.h"
PID pid;
u16 pidcalc_10ms,I3;
int St1,Num0,Num1;
void PIDParament_Init()  
{
  pid.set =30;
	pid.currpwm=0;
	pid.pwm_cycle=20;    //
	pid.calc_cycle=20; 
  pid.pid_P=205;//210 160
  pid.pid_I=2;//2
  pid.pid_D=-0.1;//-0.1
}

void pid_calc()  //pid??
{
  //int dk;

	
  short PID_out;

	if(pidcalc_10ms<pid.calc_cycle) return ;

  pid.Ek=pid.set-pid.curr;//????(????-????)
  PID_out=((pid.pid_P)*((pid.Ek)-(pid.Ek_1)))+ \
          ((pid.pid_I)*(pid.Ek))+ \
          ((pid.pid_D)*((pid.Ek)-(2*(pid.Ek_1))+(pid.Ek_2)));   //??????
  pid.currpwm+=PID_out;
  pid.Ek_2=pid.Ek_1;  //???????
  pid.Ek_1=pid.Ek;    //??????
  if(pid.Ek<=0.3&&pid.currpwm>10)
	{
		pid.currpwm=13;
	}
  if(pid.currpwm>pid.pwm_cycle)  //1000    //1s??PWM??
  {
     pid.currpwm=pid.pwm_cycle;   //????????1000???????
  }
  if(pid.currpwm<=0||pid.Ek<=-0.2)  //??????0??0??(????)
  {
      pid.currpwm=0;//   
  }  //PID????
 pidcalc_10ms=0;
// St1++;
// Num0+=pid.currpwm;
//	if(St1>=5)
//	{
//		St1=0;
//		Num1=Num0*5;
//		Num0=0;
//	}
	Tim_PwmOutPut(htim3,pid.currpwm);
} 



