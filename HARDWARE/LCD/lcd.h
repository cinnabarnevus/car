//////////////////////////////////////////////////////////////////////////////////	 
//锟斤拷锟斤拷锟斤拷只锟斤拷学习使锟矫ｏ拷未锟斤拷锟斤拷锟斤拷锟斤拷锟缴ｏ拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷业锟斤拷途
//锟斤拷锟斤拷硬锟斤拷锟斤拷锟斤拷片锟斤拷CH32F103C8T6,F103C8T6锟斤拷锟侥匡拷锟斤拷锟斤拷,锟斤拷频72MHZ锟斤拷锟斤拷锟斤拷8MHZ
//QDtech-TFT液锟斤拷锟斤拷锟斤拷 for CH32 IO模锟斤拷
//Chan@ShenZhen QDtech co.,LTD
//锟斤拷司锟斤拷站:www.qdtft.com
//wiki锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷站锟斤拷http://www.lcdwiki.com
//锟斤拷司锟结供锟斤拷锟斤拷支锟街ｏ拷锟轿何硷拷锟斤拷锟斤拷锟解欢迎锟斤拷时锟斤拷锟斤拷学习
//锟教伙拷(锟斤拷锟斤拷) :+86 0755-21077707 
//锟街伙拷: (锟斤拷锟斤拷)18823372746 锟斤拷锟斤拷锟斤拷)15989313508
//锟斤拷锟斤拷:(锟斤拷锟斤拷/锟斤拷锟斤拷) sales@qdtft.com  (锟桔猴拷/锟斤拷锟斤拷锟斤拷锟斤拷)service@qdtft.com
//QQ:(锟斤拷前锟斤拷询)3002706772 (锟斤拷锟斤拷支锟斤拷)3002778157
//锟斤拷锟斤拷锟斤拷锟斤拷QQ群:778679828
//锟斤拷锟斤拷锟斤拷锟斤拷:2020/05/07
//锟芥本锟斤拷V1.0
//锟斤拷权锟斤拷锟叫ｏ拷锟斤拷锟斤拷鼐锟斤拷锟�
//Copyright(C) 锟斤拷锟斤拷锟斤拷全锟斤拷锟斤拷锟接硷拷锟斤拷锟斤拷锟睫癸拷司 2018-2028
//All rights reserved
/****************************************************************************************************
//=========================================锟斤拷源锟斤拷锟斤拷================================================//
//     LCD模锟斤拷                CH32锟斤拷片锟斤拷
//      VCC          锟斤拷        DC5V/3.3V      //锟斤拷源
//      GND          锟斤拷          GND          //锟斤拷源锟斤拷
//=======================================液锟斤拷锟斤拷锟斤拷锟斤拷锟竭斤拷锟斤拷==========================================//
//锟斤拷模锟斤拷默锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷为SPI锟斤拷锟斤拷
//     LCD模锟斤拷                CH32锟斤拷片锟斤拷    
//       SDA         锟斤拷          PA7         //液锟斤拷锟斤拷SPI锟斤拷锟斤拷锟斤拷锟斤拷写锟脚猴拷
//=======================================液锟斤拷锟斤拷锟斤拷锟斤拷锟竭斤拷锟斤拷==========================================//
//     LCD模锟斤拷 					      CH32锟斤拷片锟斤拷 
//       LED         锟斤拷          PB6         //液锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷藕牛锟斤拷锟斤拷锟斤拷锟斤拷要锟斤拷锟狡ｏ拷锟斤拷5V锟斤拷3.3V
//       SCK         锟斤拷          PA5         //液锟斤拷锟斤拷SPI锟斤拷锟斤拷时锟斤拷锟脚猴拷
//       A0          锟斤拷          PB7         //液锟斤拷锟斤拷锟斤拷锟斤拷/锟斤拷锟斤拷锟斤拷锟斤拷藕锟�
//       RESET       锟斤拷          PB8         //液锟斤拷锟斤拷锟斤拷位锟斤拷锟斤拷锟脚猴拷
//       CS          锟斤拷          PB9         //液锟斤拷锟斤拷片选锟斤拷锟斤拷锟脚猴拷
//=========================================锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷=========================================//
//模锟介不锟斤拷锟斤拷锟斤拷锟斤拷锟杰ｏ拷锟斤拷锟斤拷要锟斤拷锟叫达拷锟斤拷锟斤拷锟斤拷锟斤拷
**************************************************************************************************/	
 /* @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, QD electronic SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
**************************************************************************************************/		
#ifndef __LCD_H
#define __LCD_H		
#include "sys.h"	 
#include "stdlib.h"

//LCD锟斤拷要锟斤拷锟斤拷锟斤拷
typedef struct  
{										    
	u16 width;			//LCD 锟斤拷锟斤拷
	u16 height;			//LCD 锟竭讹拷
	u16 id;				  //LCD ID
	u8  dir;			  //锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟狡ｏ拷0锟斤拷锟斤拷锟斤拷锟斤拷1锟斤拷锟斤拷锟斤拷锟斤拷	
	u16	 wramcmd;		//锟斤拷始写gram指锟斤拷
	u16  setxcmd;		//锟斤拷锟斤拷x锟斤拷锟斤拷指锟斤拷
	u16  setycmd;		//锟斤拷锟斤拷y锟斤拷锟斤拷指锟斤拷	 
}_lcd_dev; 	

//LCD锟斤拷锟斤拷
extern _lcd_dev lcddev;	//锟斤拷锟斤拷LCD锟斤拷要锟斤拷锟斤拷
/////////////////////////////////////锟矫伙拷锟斤拷锟斤拷锟斤拷///////////////////////////////////	 
#define USE_HORIZONTAL  	 0 //锟斤拷锟斤拷液锟斤拷锟斤拷顺时锟斤拷锟斤拷转锟斤拷锟斤拷 	0-0锟斤拷锟斤拷转锟斤拷1-90锟斤拷锟斤拷转锟斤拷2-180锟斤拷锟斤拷转锟斤拷3-270锟斤拷锟斤拷转

//////////////////////////////////////////////////////////////////////////////////	  
//锟斤拷锟斤拷LCD锟侥尺达拷
#define LCD_W 128
#define LCD_H 160

//TFTLCD锟斤拷锟斤拷锟斤拷要锟斤拷锟矫的猴拷锟斤拷		   
extern u16  POINT_COLOR;//默锟较猴拷色    
extern u16  BACK_COLOR; //锟斤拷锟斤拷锟斤拷色.默锟斤拷为锟斤拷色

////////////////////////////////////////////////////////////////////
//-----------------LCD锟剿口讹拷锟斤拷---------------- 
#define GPIO_TYPE  GPIOB  //GPIO锟斤拷锟斤拷锟斤拷
#define LED      6        //锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟�        PB6
#define LCD_CS   9       //片选锟斤拷锟斤拷            PB9
#define LCD_RS   7       //锟侥达拷锟斤拷/锟斤拷锟斤拷选锟斤拷锟斤拷锟斤拷 PB7 
#define LCD_RST  8       //锟斤拷位锟斤拷锟斤拷            PB8


//QDtech全系锟斤拷模锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷芸锟斤拷票锟斤拷锟斤拷锟斤拷锟斤拷没锟揭诧拷锟斤拷越锟絇WM锟斤拷锟节憋拷锟斤拷锟斤拷锟斤拷
#define	LCD_LED PBout(LED) //LCD锟斤拷锟斤拷    		 PB6
//锟斤拷锟绞癸拷霉俜锟斤拷夂�锟斤拷锟斤拷锟斤拷锟斤拷锟叫底层，锟劫度斤拷锟斤拷锟铰斤拷锟斤拷14帧每锟诫，锟斤拷锟斤拷锟斤拷锟斤拷锟剿撅拷萍锟斤拷锟斤拷锟�
//锟斤拷锟斤拷IO锟斤拷锟斤拷直锟接诧拷锟斤拷锟侥达拷锟斤拷锟斤拷锟斤拷锟斤拷IO锟斤拷锟斤拷锟斤拷刷锟斤拷锟斤拷锟绞匡拷锟皆达到28帧每锟诫！ 

// LCD 控制引脚操作宏定义：
// LCD_CS_SET  ：将 LCD 片选信号（CS）拉高，取消选中 LCD（PB9）
// LCD_RS_SET  ：将 LCD 数据/命令选择信号（RS/A0）拉高，表示写数据（PB7）
// LCD_RST_SET ：将 LCD 复位信号（RST）拉高，结束复位状态（PB8）

// 这些宏通过直接操作 GPIOB 的 BSHR 寄存器实现对 LCD 控制引脚的高电平输出。
#define	LCD_CS_SET  GPIO_TYPE->BSHR=1<<LCD_CS    //片选拉高，取消选中LCD  	
#define	LCD_RS_SET	GPIO_TYPE->BSHR=1<<LCD_RS    //数据/命令选择拉高，写数据  	  	
#define	LCD_RST_SET	GPIO_TYPE->BSHR=1<<LCD_RST   //复位拉高，LCD结束复位

// LCD 控制引脚操作宏定义：
// LCD_CS_CLR  ：将 LCD 片选信号（CS）拉低，选中 LCD（PB9）
// LCD_RS_CLR  ：将 LCD 数据/命令选择信号（RS/A0）拉低，表示写命令（PB7）
// LCD_RST_CLR ：将 LCD 复位信号（RST）拉低，进行硬件复位（PB8）
// 这些宏通过直接操作 GPIOB 的 BCR 寄存器实现对 LCD 控制引脚的低电平输出。
#define	LCD_CS_CLR  GPIO_TYPE->BCR=1<<LCD_CS     //片选拉低，选中LCD 	
#define	LCD_RS_CLR	GPIO_TYPE->BCR=1<<LCD_RS     //数据/命令选择拉低，写命令	 
#define	LCD_RST_CLR	GPIO_TYPE->BCR=1<<LCD_RST    //复位拉低，LCD复位

//锟斤拷锟斤拷锟斤拷色
#define WHITE       0xFFFF
#define BLACK      	0x0000	  
#define BLUE       	0x001F  
#define BRED        0XF81F
#define GRED 			 	0XFFE0
#define GBLUE			 	0X07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define GREEN       0x07E0
#define CYAN        0x7FFF
#define YELLOW      0xFFE0
#define BROWN 			0XBC40 //锟斤拷色
#define BRRED 			0XFC07 //锟截猴拷色
#define GRAY  			0X8430 //锟斤拷色
//GUI锟斤拷色

#define DARKBLUE      	 0X01CF	//锟斤拷锟斤拷色
#define LIGHTBLUE      	 0X7D7C	//浅锟斤拷色  
#define GRAYBLUE       	 0X5458 //锟斤拷锟斤拷色
//锟斤拷锟斤拷锟斤拷色为PANEL锟斤拷锟斤拷色 
 
#define LIGHTGREEN     	0X841F //浅锟斤拷色
#define LIGHTGRAY     0XEF5B //浅锟斤拷色(PANNEL)
#define LGRAY 			 		0XC618 //浅锟斤拷色(PANNEL),锟斤拷锟藉背锟斤拷色

#define LGRAYBLUE      	0XA651 //浅锟斤拷锟斤拷色(锟叫硷拷锟斤拷锟缴�)
#define LBBLUE          0X2B12 //浅锟斤拷锟斤拷色(选锟斤拷锟斤拷目锟侥凤拷色)
	    															  
void LCD_Init(void);
void LCD_DisplayOn(void);
void LCD_DisplayOff(void);
void LCD_Clear(u16 Color);	 
void LCD_SetCursor(u16 Xpos, u16 Ypos);
void LCD_DrawPoint(u16 x,u16 y);//锟斤拷锟斤拷
u16  LCD_ReadPoint(u16 x,u16 y); //锟斤拷锟斤拷
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);		   
void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd);

u16 LCD_RD_DATA(void);//锟斤拷取LCD锟斤拷锟斤拷									    
void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue);
void LCD_WR_DATA(u8 data);
u16 LCD_ReadReg(u8 LCD_Reg);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(u16 RGB_Code);
u16 LCD_ReadRAM(void);		   
u16 LCD_BGR2RGB(u16 c);
void LCD_SetParam(void);
void Lcd_WriteData_16Bit(u16 Data);
void LCD_direction(u8 direction );

//锟斤拷锟斤拷锟饺伙拷锟斤拷锟斤拷俣炔锟斤拷锟斤拷欤�锟斤拷锟斤拷使锟斤拷锟斤拷锟斤拷暮甓�锟斤拷,锟斤拷锟斤拷俣锟�.
//注锟斤拷要去锟斤拷lcd.c锟斤拷void LCD_WR_DATA(u16 data)锟斤拷锟斤拷锟斤拷锟斤拷哦
/*
#if LCD_USE8BIT_MODEL==1//使锟斤拷8位锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷模式
	#define LCD_WR_DATA(data){\
	LCD_RS_SET;\
	LCD_CS_CLR;\
	DATAOUT(data);\
	LCD_WR_CLR;\
	LCD_WR_SET;\
	DATAOUT(data<<8);\
	LCD_WR_CLR;\
	LCD_WR_SET;\
	LCD_CS_SET;\
	}
	#else//使锟斤拷16位锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷模式
	#define LCD_WR_DATA(data){\
	LCD_RS_SET;\
	LCD_CS_CLR;\
	DATAOUT(data);\
	LCD_WR_CLR;\
	LCD_WR_SET;\
	LCD_CS_SET;\
	} 	
#endif
*/
				  		 
#endif  
	 
	 



