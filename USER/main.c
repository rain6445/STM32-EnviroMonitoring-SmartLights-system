#include "led.h"
#include "usart.h"
#include "delay.h"
#include "dht11.h"
#include "oled.h"
#include "key.h"
#include "remote.h"

u8 temp;
u8 humi;

int key = 0;
int key_state = 0;
int main(void)
{ 
	u8 key;
	
  SystemInit();//配置系统时钟为72M	
	delay_init();
	LED_Init();
	LED0_On();
	uart_init(115200);//串口初始化
	OLED_Init();
	KEY_Init();
	Remote_Init();
	printf("Start \n");
	delay_ms(1000);
	
	OLED_Clear();
	//显示“温度：”
	OLED_ShowChinese(0,0, 7,16,1);
	OLED_ShowChinese(16,0,8,16,1);
	OLED_ShowChar(32, 0, ':',16,1);//26
	OLED_ShowChar(66, 0, 'C',16,1);	
	//显示“湿度：”
	OLED_ShowChinese(0,16,1,16,1);
	OLED_ShowChinese(16,16,8,16,1);
	OLED_ShowChar(32, 16, ':',16,1);	
	OLED_ShowChar(66, 16, '%',16,1);	


	while(DHT11_Init())
	{
		printf("DHT11 Error \r\n");
		delay_ms(1000);
	}

  while (1)
  {
				key=Remote_Scan();	
		if(key)
		{	 
						switch(key)
			{
				case 0:printf("ERROR\r\n");break;
			  case 2:printf("ON\r\n");LED1_Off();break;
				case 34:printf("OFF\r\n");LED1_On();break;		  
			}
		}
		DHT11_Read_Data(&temp,&humi);//
		printf("temp %d ,humi %d\r\n",temp,humi);
		LED0_Toggle();
		delay_ms(1000);
		//显示温度数据
		OLED_ShowNum(48,0,temp,2,16,1);
		//显示湿度数据
		OLED_ShowNum(48,16,humi,2,16,1);
  }
}
