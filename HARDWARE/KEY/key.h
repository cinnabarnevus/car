#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
/***********************
��Ŀ������������
���ߣ������ĵ�����--����
����ţ�tb43915564
�޸����ڣ�2025/3/20
�������ã�
************************/    


//#define KEY0 PEin(4)  //PE4
//#define KEY1 PEin(3)	//PE3 
//#define KEY2 PEin(2)	//PE2
//#define WK_UP PAin(0)	//PA0  WK_UP

/*�������õ���������PB1/PB12��������Ϊ��չ�����û�ʹ��*/
#define KEY0  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)//��ȡ����0
#define KEY1  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)//��ȡ����1
#define KEY2  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_14)//��ȡ����2 pc14
#define WK_UP   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//��ȡ����3(WK_UP) 

 

#define KEY0_PRES 	1	//KEY0����
#define KEY1_PRES	2	//KEY1����
#define KEY2_PRES	3	//KEY2����
#define WKUP_PRES   4	//KEY_UP����(��WK_UP/KEY_UP)


void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(u8);  	//����ɨ�躯��					    
#endif
