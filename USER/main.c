/*
 * @Author: cinnabarnevus cinnabar.nevus@gmail.com
 * @Date: 2025-06-19 19:47:35
 * @LastEditors: zjw cinnabar.nevus@gmail.com
 * @LastEditTime: 2025-07-18 19:32:12
 * @FilePath: \USER\main.c
 * @Description: ����Ĭ������,������`customMade`, ��koroFileHeader�鿴���� ��������: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
/*
 * @Author: cinnabarnevus cinnabar.nevus@gmail.com
 * @Date: 2025-05-15 15:24:19
 * @LastEditors: cinnabarnevus cinnabar.nevus@gmail.com
 * @LastEditTime: 2025-06-25 23:40:37
 * @FilePath: \USER\main.c
 * @Description: ����Ĭ������,������`customMade`, ��koroFileHeader�鿴���� ��������: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
/*
 * @Author: cinnabarnevus cinnabar.nevus@gmail.com
 * @Date: 2025-05-15 15:24:19
 * @LastEditors: cinnabarnevus cinnabar.nevus@gmail.com
 * @LastEditTime: 2025-05-27 10:54:39
 * @FilePath: \USER\main.c
 * @Description: ����Ĭ������,������`customMade`, ��koroFileHeader�鿴���� ��������: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "FreeRTOS.h"
#include "adc.h"
#include "exti.h"
#include "lcd.h"
#include "gui.h"
#include "beep.h"
#include "us105.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "dma.h"
#include "stmflash.h"
#include "iap.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"


/*************************************************************************
��Ŀ��������FreeRTOS�ĳ��ص�ص�Ԫ(bootloader)
ʵ�ֹ��ܣ��뿴�û��ֲ�
���ߣ������ĵ�����--����
����ţ�tb43915564
�޸����ڣ�2025/3/20
�������ã�
ע���ù��̴�����֮ǰ��Keil5_Project_updated_V1.2ʵ�ֹ���һ����
ֻ�����ù���ΪFreeRTOS�汾��
**************************************************************************/



/////////////////////////FreeRTOS��������////////////////////////////////////////////////////////////////////////////////////////
//START ����
//�����������ȼ�
#define START_TASK_PRIO      			1 /*��ʼ��������ȼ�����Ϊ���,��ucosֻ���෴���˴�0Ϊ������ȼ�������IDLE����*/
//���������ջ��С
#define START_STK_SIZE  				64 /*��λ���֣�һ������4���ֽڣ�������2���ֽڣ��ʴ˴��Ĵ�СΪ64x4�ֽ�*/
//������
TaskHandle_t StartTask_Handler;
//������
static void start_task(void *pvParameters);	


//�������ת������
//�����������ȼ�
#define PWM_TASK_PRIO       			4
//���������ջ��С
#define PWM_STK_SIZE  					64
//������
TaskHandle_t  PWMTask_Handler;
//������
static void pwm_task(void *pvParameters);


//�������ת��
#define Re_TASK_PRIO					5
#define	Re_STK_SIZE						64
TaskHandle_t  ReTask_Handler;
static void 	reverse_task(void *pvParameters);


//���ת����ʾ����
#define Motoshow_task_prio   			7
#define Motoshow_task_size				64
TaskHandle_t	MotoshowTask_Handler;
static void Motoshow_task(void *pvParameters);


//us105������������
#define us105_task_prio       		  	6    
#define us105_task_size					128
TaskHandle_t	Us015Task_Handler;
static void us105_task(void *pvParameters);

//us_015��������
#define st_task_prio                 	3
#define st_task_size					32
TaskHandle_t	StTask_Handler;
static void st_task(void *pvParameters);

//MPU6050������б�Ƕ�����						
#define mpu6050_task_prio				2
#define	mpu6050_task_size				256
TaskHandle_t	Mpu6050Task_Handler;
static void mpu6050_task(void *pvParameters);

#if ifopen
//IAP����
#define  iap_task_prio               	8
#define  iap_task_size            		512
TaskHandle_t	IapTask_Handler;
static void  iap_task(void *pvParameters);

#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////����ȫ�ֱ���///////////////////////////////////////////////////////////
/*˼��һ��ΪʲôҪ��static�ؼ���?*/
/*static�ؼ��ֱ�֤ȫ�ֱ���ֻ�ڱ��ļ��ڲ���Ч��static�����ڳ��������ڼ�һֱ���ڣ����ᱻ���٣���������Ҫ�ڶ����������Ҫ�������Դ*/
//������Ҫ�õ���ȫ�ֱ���
static SemaphoreHandle_t 	sig1;
static SemaphoreHandle_t 	sig2;
static SemaphoreHandle_t 	sig3;
static QueueHandle_t 		sig4;	/*us015����������о��*/
#if ifopen
static SemaphoreHandle_t 	sig5;
#endif
static led_d led1;	/*led�ṹ����--�����ĵ�����ע*/
static led_d bep;
static led_d us;
static volatile u8 flag=8;
static volatile u8 mark=8;
static volatile u32 rate=0;
static volatile u32 buff;
static volatile u8  STA=0;
/********************************************************************************************/


/******************************����APP���򻺳�����С*************************************************************/
/**��ʹ��Ϊ1����ʱ���MAP�ļ��ᷢ��RAM��СΪ19.56KB��������Ϊbootƫ����16K���ټ���APP��3.56K����������RAM��boot��APP�ĺϼ�***/
//������յ�APP�����С
#if ifopen		/*��Ҫʹ�ù̼����¹��ܣ���ʹ��Ϊ1*/

	/*��Ҫע�ⲻ����bootloader�����RAM������APP�����RAM�����ص���������bootloader��RAM���Ϊ12K�����ƫ����16K��Ϊ0x4000,ʣ�µ�4Kram��APP*/
	
	u8 receive_buff[buff_size]  __attribute__ ((at(0X20004000)));/*��������䵽�̶����ڴ��ַ���������Ҫ�޸ģ�,������жϹ̼�����ʧ��*/
	
#endif

/********************************************************************************************************************/



/*�����������ڳ�ʼ��Ӳ���Լ�������ʼ����*/
 int main(void)
 {	
	/************************************************************************************************************/
	/*���ڹ���6���жϣ������жϷ���Ϊ4��4λ��ռ���ȼ���0λ�����ȼ�����ΪFree��֧�������ȼ�����
	 ����Free�д����������ȼ���ֵ�ĸ���ù��̱�������Ϊ3�����������Ҫ����API�������ж����ȼ����ܳ���3��
	 ����DMA�ж����ȼ�Ϊ4�����벶���ж����ȼ�Ϊ5
	 ��ʱ��2�ж����ȼ�Ϊ6��PB12/PC14�ⲿ�ж����ȼ�7��PB1�ⲿ�ж����ȼ�8�������ȼ�������Ϊ0--�����ĵ�����ע*/
	/*************************************************************************************************************/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//�����ж����ȼ�����Ϊ��4��4λ��ռ���ȼ���0λ��Ӧ���ȼ� 	
	delay_init();	    //��ʱ������ʼ��
	uart_init(115200);
	MPU_Init();        /*ͨ��iicЭ����ͨѶ*/
	mpu_dmp_init();		/*mpu6050�����˶��������ĳ�ʼ��*/
	LED_Init(&led1,GPIOC,GPIO_Pin_13);			 //��ʼ����LED���ӵ�Ӳ���ӿ�
	Beep_Init(&bep,GPIOB,GPIO_Pin_15);			/*��ʼ��beep*/
	us105Init(&us,GPIOA,GPIO_Pin_12);			/*��ʼ��US-015�����������*/
	TIM3_PWM_Init(99,14399);					/*��ʼ��pwm*/
	EXTIX_Init();								/*��ʼ�������ж�*/
	LCD_Init();									/*LCD��ʼ����ͨ��spiЭ����ͨѶ*/
	
#if ifopen
	MYDMA_Config(DMA1_Channel5,(u32)&USART1->DR,(u32)receive_buff,buff_size);//��ʼ��DMA
#endif  
	xTaskCreate(start_task,"start_task",START_STK_SIZE,NULL,START_TASK_PRIO,&StartTask_Handler);/*������ʼ����*/
	vTaskStartScheduler(); 	/*�������������*/  	 
}
 

/*******************************************����Ϊ���񲿷֣�����14��������rtos������ʼ����******************************************************************/	  

/*��ʼ����*/
static void start_task(void *pvParameters)
{
	/**Ϊ��ֹ��ʱ�жϳ�ʼ���Ժ�����жϺ���������ʱ�ź�����û�д���
	,���½���HardFault����,�������ʼ�����вų�ʼ����ʱ���жϺ���*/
	
	taskENTER_CRITICAL();			//�����ٽ���(�޷����жϴ��) 
	
	/**********��������*******************/
	sig4=xQueueCreate(1,sizeof(u16));
	/*************************************/
	
	/*****������ֵ�ź���--FreeRTOS********/
	sig1=xSemaphoreCreateBinary();
	sig2=xSemaphoreCreateBinary();
	sig3=xSemaphoreCreateBinary();
#if ifopen
	sig5=xSemaphoreCreateBinary();
#endif
	/**************************************/
	
	/********��ʼ����ʱ���ж�******************/
	TIM2_Int_Init(4999,14399);	//����1s�ж����ڵĶ�ʱ�������ж�
	/****************************************/
	
	/*****��ʱ�����벶���ʼ��*****************/
	TIM1_Cap_Init(84,71999);  //����Ƶ��Ҳ����̫�ߣ��������Ҳ���ܷɣ���Ϊ��Ƶ�������ж�ռ��cpu��Դ
	/*****************************************/
	
	/********��������**************************************************************************************/    				   
	xTaskCreate(pwm_task,"pwm_task",PWM_STK_SIZE,NULL,PWM_TASK_PRIO,&PWMTask_Handler);
	xTaskCreate(reverse_task,"reverse_task",Re_STK_SIZE,NULL,Re_TASK_PRIO,&ReTask_Handler);
	xTaskCreate(Motoshow_task,"motoshow_task",Motoshow_task_size,NULL,Motoshow_task_prio,&MotoshowTask_Handler);
	xTaskCreate(us105_task,"us015_task",us105_task_size,NULL,us105_task_prio,&Us015Task_Handler);
	xTaskCreate(st_task,"st_task",st_task_size,NULL,st_task_prio,&StTask_Handler);
	xTaskCreate(mpu6050_task,"mpu6050_task",mpu6050_task_size,NULL,mpu6050_task_prio,&Mpu6050Task_Handler);
#if ifopen
	xTaskCreate(iap_task,"iap_task",iap_task_size,NULL,iap_task_prio,&IapTask_Handler);
#endif
	vTaskDelete(StartTask_Handler); 	//ɾ����ʼ����
	/****************************************************************************************************/
	
	taskEXIT_CRITICAL();				//�˳��ٽ���(���Ա��жϴ��)
}



/*�������ת������*/
static void pwm_task(void *pvParameters)
{
	while(1)	/*����ϰ���ô���������ѭ�����û�Ҳ����ѡ����for(;;)*/
	{
		xSemaphoreTake(sig1,portMAX_DELAY);	/*�ȴ��ź�����portMAX_DELAY�������޵�*/
		TIM_SetCompare3(TIM3,flag);	/*�����ת*/
	}
}


/*�����ת����*/
static void reverse_task(void *pvParameters)
{
	while(1)
	{
		xSemaphoreTake(sig2,portMAX_DELAY);	/*�ȴ��ź�����portMAX_DELAY�������޵�*/
		TIM_SetCompare3(TIM3,mark);	/*�����ת*/
	}
}


/*���ת����ʾ����*/
static void Motoshow_task(void *pvParameters)
{
	while(1)
	{
		xSemaphoreTake(sig3,portMAX_DELAY);	/*�ȴ��ź�����portMAX_DELAY�������޵�*/
		buff=rate;
		/*��ʾ����*/
		Show_Str(0,80,BLUE,WHITE,"Speed:00r/min",16,0);
		LCD_ShowNum(0+6*8,80,60*buff/2,2,16);
		rate=0;/*����ֵ����*/
	}
}


/*us105������������*/
static void us105_task(void *pvParameters)
{
	BaseType_t xResult;
	u16 PluseWidth,num;
	while(1)
	{
		/* �Ӷ����л�ȡ���ݣ��ȴ�ʱ��ΪportMAX_DELAY��һֱ�ȴ� */
        xResult = xQueueReceive(sig4, &PluseWidth, portMAX_DELAY);
        if(xResult == pdPASS){ 	/* ���յ���Ϣ */
		/*printf("%d",PluseWidth);*/	/*������*/
		if(STA&0x80)
		{
			num=0.005*340*PluseWidth;
			Show_Str(0,60,BLUE,WHITE,"juli:00cm",16,0);
			LCD_ShowNum(0+5*8,60,num,2,16);
			/*����С��5cmʱ�İ�ȫ����*/
			if(num<=5)
			{
				Beep_on(&bep);
				led_on(&led1);
				TIM_SetCompare3(TIM3,8);
			}	
			else
			{
				led_off(&led1);
				Beep_off(&bep);
			}
			STA=0;
		}
	  }
	}
}


/*us-015��������*/
static void st_task(void *pvParameters)
{
	while(1)
	{
		us105_Start(&us);/*us-015������������trigger�����ṩ������ƽ*/
		/*����ʱ�����Ƕ�vTaskDelay�����ķ�װ����ΪvTaskDelay,Ϊ�����ʱ*/
		delay_ms(1000);	//�����ʱһ��Ҫ�ӣ���Ϊ����us015�Ĵ����źţ����Ǵ����źŵ�Ƶ��Խ�ߣ����������Ƶ��ҲԽ�ߣ�
		//���½����жϵ�Ƶ��Ҳ��Խ�ߣ������жϹ���Ƶ������cpu��Դ�ľ�.
	}
}
	

/*mpu6050������б�Ƕ�����*/
static void mpu6050_task(void *pvParameters)
{
	float pitch,roll,yaw; 
	int tmp;
	while(1)
	{
		/*��ȡDMP����������*/
		if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)/*����ֵΪ0����ʾdmp������������*/
		/*ʹ��&��Ŀ����ʹ�ú������Ը��µ��õı���ֵ��ʵ�ֶ������ֵ;dmp����ɹ���pitch,roll,yawΪ���º��ֵ*/
		{
			/*����roll�Ƕ�����*/
			tmp = roll * 100;/*���Ƕ�ת��Ϊ�������������ڼ�����������/С�����֣�*/
			/*��roll=12.30,��ʱtmp��1230���������tmp/100�õ���������*/
			/*��ʾ�Ƕ�ֵ*/
			if (tmp < 0)
			{
				/*��ʾ���Ƕ�*/
				tmp = -tmp;
				Show_Str(0,40,BLUE,WHITE,"angle:-00.00d",16,0);
				LCD_ShowNum(0+7*8,40,tmp/100,2,16);
				LCD_ShowNum(0+10*8,40,tmp%100,2,16);
			}
			else
			{
				/*��ʾ���Ƕ�*/
				Show_Str(0,40,BLUE,WHITE,"angle:00.00d",16,0);
				LCD_ShowNum(0+6*8,40,tmp/100,2,16);//��������
				LCD_ShowNum(0+9*8,40,tmp%100,2,16);//С������
			}
			/*��ȫ�����ж�*/
			if(tmp>4500)/*����tmp��*100���������ôroll>45��ʱ����ʱtmpֵӦ��Ϊ4500*/
			{
				TIM_SetCompare3(TIM3,8);//��ʾ�Ĵ�ʱ�������
				Show_Str(0,20,BLUE,WHITE,"Caution!",16,0);
			}
			else 
				LCD_Fill(0,0,128,35,WHITE);//����
			delay_ms(100);//��ʱ�����̣���֤��ȡ���ݵ�Ƶ���㹻�ߣ�����ʱ�䳤�˻ῴ�������ݱ仯��FIFO���,�����ʱ���ܳ���300ms
		}
	}
}


/*����ӵ�������pwm_task()�������ʹ��*/
void EXTI1_IRQHandler(void)//�ⲿ�ж�1,���¼���
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;/*�ͷŶ�ֵ�ź��������������ʼ��ΪpdFalse*/
	delay_xms(10);/*����,����ʱ���������������*/
	if(KEY0==0)
	{
		flag-=1;
		if(flag<3)
		{
			flag=8;
		}
		/*��ʾ���ٵ�λ*/
		Show_Str(0,100,BLUE,WHITE,"Gear:",16,0);
		LCD_ShowNum(0+5*8,100,flag,2,16);
		/* �ͷŶ�ֵ�ź�����������������ڵȴ����ź������������� */
		xSemaphoreGiveFromISR(sig1, &xHigherPriorityTaskWoken);
	}
	EXTI_ClearITPendingBit(EXTI_Line1);/*����жϱ�־λ*/
	/* �����Ҫ�Ļ�����һ�������л� */
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}


/*�����ת�����ת��������reverse_task()�������ʹ��*/
void EXTI15_10_IRQHandler(void)//�ⲿ�ж�PB12,PC14���ڿ��Ƶ����ת/���ת�ټ���
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;/*�ͷŶ�ֵ�ź��������������ʼ��ΪpdFalse*/
	delay_xms(10);	/*����,������������*/
	/*PB12���Ƶ����ת����Ϊ12��14����[15:10]�����жϣ�������Ҫͨ��EXTI_GetITStatus�ж��ж�Դ������һ��*/
	if(EXTI_GetITStatus(EXTI_Line12)!=RESET)
	{
	  if(KEY1==0)
	    {
			mark+=1;
			if(mark>13)
			{
				mark=8;
			}
			Show_Str(0,120,BLUE,WHITE,"Gear:",16,0);
			LCD_ShowNum(0+5*8,120,mark,2,16);
			xSemaphoreGiveFromISR(sig2, &xHigherPriorityTaskWoken);/*�ͷŶ�ֵ�ź���*/
	    }
		EXTI_ClearITPendingBit(EXTI_Line12);
	}
	/*PC14���Ƶ��ת�ټ���*/
	if(EXTI_GetITStatus(EXTI_Line14)!=RESET)
	{
		if(KEY2==0)
			rate++;
		//led_on(&led1);
		EXTI_ClearITPendingBit(EXTI_Line14);
	}
		/* �����Ҫ�Ļ�����һ�������л� */
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}


/*��ȡ1s��ת��������Motoshow_task()�������ʹ��*/
void TIM2_IRQHandler(void)//��ʱ���жϺ�������ʱ1s�����ʱ��ת��,��Ҫע������жϺ�����߲���д̫���ӵĶ�������Ȼ�ͻᱻ��ס
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;/*�ͷŶ�ֵ�ź��������������ʼ��ΪpdFalse*/
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //��� TIM2 �����жϷ������
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update ); //��� TIM2 �����жϱ�־
		led_on(&led1);/*������*/
		xSemaphoreGiveFromISR(sig3, &xHigherPriorityTaskWoken);/*�ͷŶ�ֵ�ź���*/
	}
	/* �����Ҫ�Ļ�����һ�������л� */
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}


/*���벶���ж�������us105_task()�������ʹ��*/
//������us105���ģ�飬���񴫻����ĸߵ�ƽ����,�����ж�
void TIM1_CC_IRQHandler(void)
{ 
	static u16	PluseWidth;
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
 	if((STA&0X80)==0)//��δ�ɹ�����	
	{	  
		if (TIM_GetITStatus(TIM1, TIM_IT_CC1) != RESET)//����1���������¼�
		{	
			if(STA&0X40)		//����һ���½��� 		
			{	  			
				STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
				PluseWidth=TIM_GetCapture1(TIM1);
				TIM_OC1PolarityConfig(TIM1,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���
			}
			else  			    //��δ��ʼ,��һ�β���������
			{
				STA=0;			//���
				PluseWidth=0;
				TIM_SetCounter(TIM1,0);
				STA|=0X40;		//��˳���ʵ�����ǵȵ��������жϵ�ʱ���ڴ˴�����������ȼĴ�����ֵ��ɲ���0��
				TIM_OC1PolarityConfig(TIM1,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
			}		    
		}			     	    					   
 	}
	TIM_ClearITPendingBit(TIM1, TIM_IT_CC1); //����жϱ�־λ
	/*������з������� */
    xQueueSendFromISR(sig4, &PluseWidth, &xHigherPriorityTaskWoken);
	/*�����Ҫ�Ļ�����һ�������л� */
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}


#if ifopen
/*�̼���������*/
static void iap_task(void *pdata)
{
	uint16_t receivedLength;
	while(1)
	{
		xSemaphoreTake(sig5,portMAX_DELAY);	/*�ȴ��ź�����portMAX_DELAY�������޵�*/
		//printf("ִ�е�����");//������
		receivedLength = GetReceivedDataLength();/*���������յ�����������Ҫ���ñ������ڵȴ��ź�����������ȷ����ʱ����*/
		if(receive_buff[0])//���Ƿ���յ���APP����
		{
			printf("�ѽ��յ�APP����Ϊ%d\n",receivedLength);
			//printf("%s\n",receive_buff);//������
			/*��������ת*/
			if(((*(vu32*)(0X20004000+4))&0xFF000000)==0x08000000)//�ж��Ƿ�Ϊ0X08XXXXXX.
			{	 
				Show_Str(0,120,BLUE,WHITE,"Firmware updating!",16,0);/*��ӡ��Ϣ��LCD��Ļ�ϴ������ڸ���*/
				FLASH_ErasePage(FLASH_APP1_ADDR);/*�Ȳ���APP����flash����ֹ�����ݲ���--�����ĵ�����*/
				iap_write_appbin(FLASH_APP1_ADDR,receive_buff,buff_size);//����FLASH����   				
				printf("�̼��������!\r\n");	
				printf("��ʼִ��flash�û�����\r\n");
				if(((*(vu32*)(FLASH_APP1_ADDR+4))&0xFF000000)==0x08000000)//�ж��Ƿ�Ϊ0X08XXXXXX.
					iap_load_app(FLASH_APP1_ADDR);//ִ��FLASH APP����
				else
					printf("��FLASHӦ�ó���,�޷�ִ��!\r\n");  
			}
				/*����жϹ̼�ʧ�ܣ��Ƚ�����APP�����������ֹ���ݲ��������¿���DMA�������´θ���--�����ĵ�����*/
			else
			{
				memset(receive_buff,0,buff_size);   //�������
				MYDMA_Enable(DMA1_Channel5);//����һ��DMA���䣬�����´θ���
				printf("error!�̼��ж�ʧ��");
			}
		}
	}
}


/*����APP��������*/
void DMA1_Channel5_IRQHandler(void) 
{
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;/*�ͷŶ�ֵ�ź��������������ʼ��ΪpdFalse*/
		// ���DMA��������ж�
		if (DMA_GetITStatus(DMA1_IT_TC5))
		{
        	// ����жϱ�־
        	DMA_ClearITPendingBit(DMA1_IT_TC5);
			//printf("CNDTR: %d\n", DMA_GetCurrDataCounter(DMA1_Channel5)); // ������
			xSemaphoreGiveFromISR(sig5, &xHigherPriorityTaskWoken);/*�ͷŶ�ֵ�ź���*/	
		}
		/* �����Ҫ�Ļ�����һ�������л� */
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
#endif


