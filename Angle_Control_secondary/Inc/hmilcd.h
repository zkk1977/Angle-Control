#ifndef  _HMILCD_H
#define  _HMILCD_H

#include "usart.h"


#define Usart_Port1  1
#define Usart_Port2  2
#define Usart_Port3  3


char *Reverse(char *S);
char *ConvertInt_Str(char *S,int Num);
char *ConvertFloat_Str(char *S,float Num);
void Hmi_Send_Float(char *Index,float Data,u8 Port);
void Hmi_Send_Int(char *Index,int Data,u8 Port);
#endif

