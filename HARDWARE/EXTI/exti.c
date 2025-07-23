#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"

/***********************
��Ŀ�����ж���������
���ߣ������ĵ�����--����
����ţ�tb43915564
�޸����ڣ�2025/3/20
�������ã�
************************/   

//�ⲿ�ж�PC14��PB1/PB12���жϷ�������ʼ��
void EXTIX_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		EXTI_InitTypeDef EXTI_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;

		/*����ʱ��*/
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
		/*���ж�io������Ϊ���뷽ʽ���˴�ֻ������PC14�����뷽ʽ��
		��ΪPB1��PB12�ⲿ�����������裬��stm32�У���û��ָ�����뷽ʽ��Ĭ��Ϊ�������룬
		��˿��ⲿ��·����--�����ĵ�����ע*/
		GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_14;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��

	   //PB1���½��ش�����key0
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);
		EXTI_InitStructure.EXTI_Line=EXTI_Line1;	
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

		//PB12���½��ش���,key1
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource12); 
		EXTI_InitStructure.EXTI_Line=EXTI_Line12;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
		//PC14���½��ش���
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource14); 
		EXTI_InitStructure.EXTI_Line=EXTI_Line14;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���


		NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//ʹ��PB12/PC14���ڵ��ⲿ�ж�ͨ��
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 7;	//��ռ���ȼ�����ֵԽС�����ȼ�Խ��
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;					//�����ȼ�0
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
		NVIC_Init(&NVIC_InitStructure); 

		NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//ʹ�ܰ���KEY0���ڵ��ⲿ�ж�ͨ��
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 8;	//��ռ���ȼ�
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;					//�����ȼ� 
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
		NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
}

//�ⲿ�ж�0������� 
//void EXTI0_IRQHandler(void)
//{
//	delay_ms(50);//����
//	if(WK_UP==1)	 	 //WK_UP����
//	{				 
//		LED1=!LED1;	
//	}
//	EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ  
//}
 
//�ⲿ�ж�4�������
//void EXTI1_IRQHandler(void)
//{
//	delay_ms(50);//����
//	LED0=!LED0;
//	EXTI_ClearITPendingBit(EXTI_Line9);
//	if(KEY0==1)	 //����KEY0
//	{
//		LED0=!LED0;
//	}		 
//	EXTI_ClearITPendingBit(EXTI_Line4);  //���LINE4�ϵ��жϱ�־λ  
//}

//void EXTI1_IRQHandler(void)//�ⲿ�ж�1
//{
//		delay_ms(50);
//		if(KEY0==0)
//			{
//				flag=1;
//			}
//		EXTI_ClearITPendingBit(EXTI_Line1);
//}


//void EXTI15_10_IRQHandler(void)//�ⲿ�ж�PB12
//{
//		delay_ms(50);
//	  if(KEY1==0)
//	    {
//				mark=1;
//			}
//				
//		EXTI_ClearITPendingBit(EXTI_Line12);
//}

 
