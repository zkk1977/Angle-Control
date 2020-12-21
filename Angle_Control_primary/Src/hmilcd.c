#include "hmilcd.h"
#include "string.h"
#include "stdlib.h"
const char *Str1 = ".txt=\"";
const char *Str2 = "\"";
char Text[50];

/*******************************************************************************
* ������  : Hmi_Send_Int
* ����    : ��HMI������������
* ����    : *Index�ؼ�ID,Data�����͵�����ֵ,Port��Ҫʹ�õĴ���
* ���    : ��
* ����    : �� 
* ˵��    : ��
*******************************************************************************/
void Hmi_Send_Int(char *Index,int Data,u8 Port)
{
	int i;
  char Temp[50];

	for(i=0;Text[i]!='\0';i++) Text[i]='\0';
  ConvertInt_Str((char *)Temp,Data);//����ֵתΪ�ַ���
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
* ������  : Hmi_Send_Float
* ����    : ��HMI�������͸�����
* ����    : *Index�ؼ�ID,Data�����͵ĸ�����ֵ,Port��Ҫʹ�õĴ���
* ���    : ��
* ����    : �� 
* ˵��    : ��
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
* ������  : Reverse_Str
* ����    : ��ת�ַ���
* ����    : *Arr����ת���ַ���
* ���    : ��
* ����    : ��ת��ɵ��ַ���ָ��
* ˵��    : ��
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
* ������  : ConvertInt_Str
* ����    : ������ֵת��Ϊ�ַ���
* ����    : *S��ŷ�ת��ɵ��ַ���,Num��ת��������ֵ
* ���    : ��
* ����    : ת����ɵ��ַ���ָ��
* ˵��    : ��
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
* ������  : ConvertFloat_Str
* ����    : ��������ֵת��Ϊ�ַ���
* ����    : *S��ŷ�ת��ɵ��ַ���,Num��ת���ĸ�����ֵ
* ���    : ��
* ����    : ת����ɵ��ַ���ָ��
* ˵��    : ��
*******************************************************************************/
char *ConvertFloat_Str(char *S,float Num)
{
  sprintf(S,"%.2f",Num);
	return S;
}



