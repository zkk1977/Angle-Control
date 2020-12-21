#ifndef _pid_
#define _pid_
#include "sys.h"

typedef struct
{
  float curr;  //当前角度
	float set;   //设定角度
	

  float pid_P;       //P
  float pid_I;       //I
  float pid_D;       //D

	float Ek;
	float Ek_1;
	float Ek_2;
	
	
	float Dout;//增量PID计算本次应该输出的增量值--本次计算的结果
	
	u16 calc_cycle;
	short currpwm;  //当前的pwm宽度
	u16 pwm_cycle;//pwm的周期
}PID;

//extern u8 STATUS;
extern PID pid;
void PIDParament_Init(void);  //
void pid_calc(void);  //pid??
extern u16 pidcalc_10ms;

//extern int F3,F4;
//extern int St1,Num0,Num1;
//#define OD PAout(0)// PE5	
#endif

