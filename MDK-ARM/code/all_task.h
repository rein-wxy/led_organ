#ifndef __ALL_TASK_H
#define __ALL_TASK_H	 

#include "stm32f4xx_hal.h"
#include "bsp_can.h"
#include "bsp_usart.h"
#include "led.h"
#include "main.h"
#include "tim.h"
#define mode_car (1)//1���Ϲ�����---2�ڱ�����̨

void task_Init(void);
/*��ʼ��*/
void base_Init(void);
/*��������*/
void chassis_all_task(void);
/*��������*/
void gimbal_all_task(void);

void key_all_task(void);

/*����������*/
void imu_all_task(void);

void referee_all_task(void);


#endif

