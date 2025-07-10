#ifndef __IAP_H__
#define __IAP_H__
#include "sys.h"  

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


typedef  void (*iapfun)(void);				//����һ���������͵Ĳ���.

#define 	ifopen   0/*�̼���������ʹ��*/
#define FLASH_APP1_ADDR		0x0800F000  	//��һ��Ӧ�ó�����ʼ��ַ(�����FLASH)//ƫ�Ƴ�0x400�պ���16K��С�����ڴ��bootloader
											//����0X08000000~0X0800FFFF�Ŀռ�ΪIAPʹ��

void iap_load_app(u32 appxaddr);			//ִ��flash�����app����
void iap_load_appsram(u32 appxaddr);		//ִ��sram�����app����
void iap_write_appbin(u32 appxaddr,u8 *appbuf,u32 applen);	//��ָ����ַ��ʼ,д��bin
#endif







































