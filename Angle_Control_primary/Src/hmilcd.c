#include "hmilcd.h"
#include "string.h"
#include "stdlib.h"
const char *Str1 = ".txt=\"";
const char *Str2 = "\"";
char Text[50];

/*******************************************************************************
* 函数名  : Hmi_Send_Int
* 描述    : 向HMI彩屏发送整数
* 输入    : *Index控件ID,Data待发送的整数值,Port需要使用的串口
* 输出    : 无
* 返回    : 无 
* 说明    : 无
*******************************************************************************/
void Hmi_Send_Int(char *Index,int Data,u8 Port)
{
	int i;
  char Temp[50];

	for(i=0;Text[i]!='\0';i++) Text[i]='\0';
  ConvertInt_Str((char *)Temp,Data);//将数值转为字符串
	strcpy(Text,Index);
	strcat(Text,Str1);
	strcat(Text,Temp);
	strcat(Text,Str2);
	switch(Port)
	{
	  case 1: 
		Usart.Hal_SendString(Text,huart1);
		for(i=0;i<3;i++)
		 Usart.Hal_SendData(0xff,huart1);
	  break;
	  
		case 2: 
		Usart.Hal_SendString(Text,huart2);
		for(i=0;i<3;i++)
		 Usart.Hal_SendData(0xff,huart2);
	  break;
		
		case 3: 
		Usart.Hal_SendString(Text,huart3);
		for(i=0;i<3;i++)
		 Usart.Hal_SendData(0xff,huart3);
	  break;
		
		default:
			break;
	}
	
}
/*******************************************************************************
* 函数名  : Hmi_Send_Float
* 描述    : 向HMI彩屏发送浮点数
* 输入    : *Index控件ID,Data待发送的浮点数值,Port需要使用的串口
* 输出    : 无
* 返回    : 无 
* 说明    : 无
*******************************************************************************/
void Hmi_Send_Float(char *Index,float Data,u8 Port)
{
	int i;
  char Temp[50];

	for(i=0;Text[i]!='\0';i++) Text[i]='\0';
  ConvertFloat_Str((char *)Temp,Data);
	strcpy(Text,Index);
	strcat(Text,Str1);
	strcat(Text,Temp);
	strcat(Text,Str2);
	switch(Port)
	{
	  case 1: 
		Usart.Hal_SendString(Text,huart1);
		for(i=0;i<3;i++)
		 Usart.Hal_SendData(0xff,huart1);
	  break;
	  
		case 2: 
		Usart.Hal_SendString(Text,huart2);
		for(i=0;i<3;i++)
		 Usart.Hal_SendData(0xff,huart2);
	  break;
		
		case 3: 
		Usart.Hal_SendString(Text,huart3);
		for(i=0;i<3;i++)
		 Usart.Hal_SendData(0xff,huart3);
	  break;
	}
}

/*******************************************************************************
* 函数名  : Reverse_Str
* 描述    : 反转字符串
* 输入    : *Arr待反转的字符串
* 输出    : 无
* 返回    : 反转完成的字符串指针
* 说明    : 无
*******************************************************************************/
char *Reverse_Str(char *Arr)
{
  char *Start = Arr;
	char *End = Arr;
	char Temp = 0;
	while(*Arr++) End++;
  End--;
  while(Start<End)
  {
	   Temp = *Start;
		 *Start++ = *End;
		 *End-- = Temp;
	}
return Arr;
}

/*******************************************************************************
* 函数名  : ConvertInt_Str
* 描述    : 将整数值转换为字符串
* 输入    : *S存放反转完成的字符串,Num待转换的整数值
* 输出    : 无
* 返回    : 转换完成的字符串指针
* 说明    : 无
*******************************************************************************/
char *ConvertInt_Str(char *S,int Num)
{
  int Negative = 0;
	char *P = S;
	Negative = Num;
 if(Negative<0) Num = -Num;
 do
 {
  *P++ = (Num%10)+'0';
  Num/=10;
 }while(Num>0);
if(Negative<0) *P++ = '-';
 *P = '\0';
 Reverse_Str(S);
 return S;
}

/*******************************************************************************
* 函数名  : ConvertFloat_Str
* 描述    : 将浮点数值转换为字符串
* 输入    : *S存放反转完成的字符串,Num待转换的浮点数值
* 输出    : 无
* 返回    : 转换完成的字符串指针
* 说明    : 无
*******************************************************************************/
char *ConvertFloat_Str(char *S,float Num)
{
  sprintf(S,"%.2f",Num);
	return S;
}



