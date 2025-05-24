//#include <stdint.h>//lay duong dan 
//#include <stmf1xxhal_gpio.h	>//Goi library ma minh lay ham o do ra giong ".h" 
#include "button.h"//lay duong dan tuong doi

//--------------------button---------------------------------

__weak void btn_pressing_callback(Button_t *btn) //create ra cac callback cho user chu ko phai de library use  
{
	
}
__weak void btn_pressed_short_callback(Button_t *btn,uint16_t pressed_ms)//su kien nhan ngan
{
	 
}
__weak void btn_pressed_timeout_callback(Button_t *btn)
{
//"__weak" de trong library read go out
}
__weak void btn_realese_callback(Button_t *btn)
{
	//Luu y: o file.c co ten ham giong nhau thi bao loi nen sai "__weak"
}
void button_handle(Button_t *btn)// su dung cho file main.c
{
	uint8_t sta = HAL_GPIO_ReadPin(btn->port,btn->pin);//bt kho nhan thi den dang o muc 1
//trang thai hien tai khi goi ham sta so vs filter
	if(sta != btn->btn_filter)
	{
		btn->btn_filter = sta;
		btn->t_debounce =HAL_GetTick();
	}
	if( HAL_GetTick() - btn->t_debounce >= 15)
	{
		btn->btn_current = btn->btn_filter;//btn_filter = sta lay thang nao cung dc
		if(btn->btn_current != btn->btn_last)
		{
			if(btn->btn_current==0)//nhan nut
			{
				btn->time_start_press=HAL_GetTick();
				btn_pressing_callback(btn);
				btn->is_press =1;
			}
			else  //nha nut
			{
				uint16_t ms=HAL_GetTick()- btn->time_start_press;
				if( ms<= 1000)
				{
					btn_pressed_short_callback(btn,ms);
				}
				btn_realese_callback(btn);
				btn->is_press = 0;
			}
			btn->btn_last = btn->btn_current;
			
		}
		if(btn->is_press && (HAL_GetTick()-btn->time_start_press >= 3000))
		{
				btn_pressed_timeout_callback(btn);
				btn->is_press=0;
		}
	}
}
void button_init (Button_t *btn, GPIO_TypeDef *port, uint16_t pin)//Luu y: library phai co "init"
{
	btn->port = port;	
	btn->pin = pin;
	btn-> btn_last =1;//Bien trang thai truoc day
	btn-> btn_filter =1;//check trang thai tu 1-0 va 0-1
	btn-> t_debounce =0;//bien thoi gian// "btn->" tro vao va gan gia tri
	btn-> time_start_press =0;//thoi gian nhan 
	btn-> is_press =0;//da dong hay chua
}
