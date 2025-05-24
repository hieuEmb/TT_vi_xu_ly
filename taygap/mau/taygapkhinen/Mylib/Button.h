#ifndef __BUTTON_H__ //(if not def):kiem tra dax co __BUTTON_H__ chua neu ch thi thuc thi lenh tiep theo
										//neu co thi ko thuc thi lenh nua(thoat ra ngoai) 
#define __BUTTON_H__//tao __BUTTON_H__
										//(ifndef vs define goi la tien su ly)
#include "main.h"
typedef struct//ko gan gia tri trong "struc" // bien chua du lieu button
																						// button phai co chan cang :  " GPIO_TypeDef *port; "
																						//												     " uint16_t pin; "
{
	GPIO_TypeDef *port;//HAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
	uint16_t pin;

	uint8_t btn_current;//Bien trang thai hien tai
	uint8_t btn_last ;//Bien trang thai truoc day
	uint8_t btn_filter ;//check trang thai tu 1-0 va 0-1
	uint32_t t_debounce;//bien thoi gian
	uint32_t time_start_press;//thoi gian nhan
	uint8_t is_press ;//da dong hay chua
}Button_t;//du lieu cho 1 nut nhan
//dat thu vien theo cu phap"_t"
void button_handle(Button_t *btn);
void button_init (Button_t *btn, GPIO_TypeDef *port, uint16_t pin);

#endif
//luu y: ko de bien vao file.h
//"file.h" dinh nghia ham de cho file ben ngoai goi