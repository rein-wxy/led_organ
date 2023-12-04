#include "led.h"
#include <stdbool.h>
#include "main.h"
#include "all_task.h"
#include "stdlib.h"
#include "Remote_Control.h"
#include "pid.h"

bool R_led[4] = {0};
bool B_led[4] = {0};
bool victory = 0;// 1-�ɹ��󼤻��������� 0-δ����

uint8_t length[2];

float flag[14];//�ƶ�����  8
uint8_t mode_led; //0-��������  1-�������� 2-������  
uint8_t mode_move; //0-δ����   1- ������   2-һ����
uint32_t led_time,length_tim[3],rgb_tim,tim_win;



uint32_t tool_length;//�������г�
float speed;


void Led_Init(void)
{
	pid_init(&pid_led_motor,
								0,	0,	0, 0,	0,0, 0, 0,0, //�⻷λ�û�kp,ki,kd
								0,	150,	5000,		0xFFFFFF,   25,        0, 5.0f, 0, 0);//�ڻ��ٶȻ�kp,ki,kd
}







void mode_set()
{
	if(RC_DR16.switch_left == 2)
		mode_led = 0;
	else if(RC_DR16.switch_left == 3)
		mode_led = 1;
	else if(RC_DR16.switch_left == 1 )
	{
		mode_led = 2;
		if(flag[9] == 0)
		{
			led_time = HAL_GetTick();
			flag[9] = 1;
		}
		
	}

	if(mode_led == 0)//����
	{
		if(RC_DR16.switch_right == 2)
			mode_move = 0;
		else if(RC_DR16.switch_right == 3)
			mode_move = 1;
		else if(RC_DR16.switch_right == 1 )
			mode_move = 2;
		flag[9] = 0;
	}
	if(mode_led == 1)
	{
		flag[9] = 0;//��ʱ��־  
	}
	if(mode_led == 2)//������ʼ��ʱ
	{
		if(HAL_GetTick()-led_time >= 240000 && HAL_GetTick()-led_time <= 300000)
			mode_move = 1;
		else if(HAL_GetTick()-led_time >= 360000&& HAL_GetTick()-led_time <= 420000)
			mode_move = 2;
		else
			mode_move = 0;	
	}
	
}
/*
	���̿���ledװ�װ�
*/
void Led_on_off(void)
{
	switch (RC_DR16.keyBoard.key_code)
        {
        	case KEY_SHIFT_Q : B_led[0] = 1;
        		break;
			case KEY_SHIFT_W : B_led[1] = 1;
        		break;
			case KEY_SHIFT_E : B_led[2] = 1;
        		break;
			case KEY_SHIFT_R : B_led[3] = 1;
        		break;
			case KEY_SHIFT_A : R_led[0] = 1;
        		break;
			case KEY_SHIFT_S : R_led[1] = 1;
        		break;
			case KEY_SHIFT_D : R_led[2] = 1;
        		break;
        	case KEY_SHIFT_F : R_led[3] = 1;
        		break;
        	default:
        		break;
        }
		switch (RC_DR16.keyBoard.key_code)
        {
        	case KEY_CTRL_Q : B_led[0] = 0;
        		break;
			case KEY_CTRL_W : B_led[1] = 0;
        		break;
			case KEY_CTRL_E : B_led[2] = 0;
        		break;
			case KEY_CTRL_R : B_led[3] = 0;
        		break;
			case KEY_CTRL_A : R_led[0] = 0;
        		break;
			case KEY_CTRL_S : R_led[1] = 0;
        		break;
			case KEY_CTRL_D : R_led[2] = 0;
        		break;
        	case KEY_CTRL_F : R_led[3] = 0;
        		break;
        	default:
        		break;
        }
	if(mode_led == 2)
	{
		
		if(flag[7] == 1)//������ʼ��ȫ��
		{
			for(int i = 0;i < 4;i++)
			{
				R_led[i] = 0;
				B_led[i] = 0;
			}
			flag[7] = 0;
		}
		
		
		if((B_led[1]+ B_led[2] +B_led[3]) >= 3  && flag[4] == 0)//����С��
		{
			R_led[1] = 0;
			R_led[2] = 0;
			R_led[3] = 0;
			flag[4] = 1;
		}
		else if((R_led[1]+ R_led[2] +R_led[3]) >= 3  && flag[4] == 0)
		{
			B_led[1] = 0;
			B_led[2] = 0;
			B_led[3] = 0;
			flag[4] = 1;
		}
		
		if(mode_move == 1)	//����ʱ��������
		{
			if(R_led[0] == 1 && flag[5] == 1)
			{
				B_led[0] = 0;
				victory = 1; 
				flag[5] = 0;//ֹͣ��־
			}
			else if(B_led[0] == 1  &&flag[5] == 1 )
			{
				R_led[0] = 0;
				victory = 1; 
				flag[5] = 0;
			}
			else ;
		}
		else if(mode_move == 2)
		{
			if(flag[13] == 1)
			{
				flag[13] = 0;
				R_led[0] = 0;
				B_led[0] = 0;
				victory = 0;
			}
			
			if(R_led[0] == 1 &&  flag[6] == 1 && flag[13] == 0)
			{
				B_led[0] = 0;
				victory = 1; 
				flag[6] = 0;				
			}
			else if(B_led[0] == 1 && flag[6] == 1 && flag[13] == 0)
			{
				R_led[0] = 0;
				victory = 1; 
				flag[6] = 0;
			}
			else ;
		}
		else if(mode_move == 0)
		{
			flag[5] = 1;
			flag[6] = 1;
			flag[13] = 1;
			victory = 0; 
		}
		
	}
	else if(mode_led == 1)//����������ȫ��
	{
		for(int i = 0;i < 4;i++)
		{
			R_led[i] = 1;
			B_led[i] = 1;
		}
		flag[7] = 1;
		flag[4] = 0; //С���ж�
	}
	else if(mode_led == 0)//���Ի����
	{
//		for(int i = 0;i < 4;i++)
//		{
//			R_led[i] = 1;
//			B_led[i] = 1;
//		}
		flag[7] = 1;
		
	}
	
	HAL_GPIO_WritePin(GPIOI,B1_Pin,B_led[0]);
	HAL_GPIO_WritePin(GPIOB,B2_Pin,B_led[1]);
	HAL_GPIO_WritePin(GPIOB,B3_Pin,B_led[2]);
	HAL_GPIO_WritePin(GPIOB,B4_Pin,B_led[3]);
	
	
	HAL_GPIO_WritePin(GPIOI,R1_Pin,R_led[0]);
	HAL_GPIO_WritePin(GPIOF,R2_Pin,R_led[1]);
	HAL_GPIO_WritePin(GPIOF,R3_Pin,R_led[2]);
	HAL_GPIO_WritePin(GPIOB,R4_Pin,R_led[3]);

}

uint32_t speed_tim[2];
float aco = 1,ftr,factor[8] = {-2,-1.5,-1 -0.7, 0.7, 1, 1.5, 2};//�ٶȱ仯ϵ��
float factor2[8] =	{-1, -0.9, 0.7, 0.8, 1, 1.3, 1.4, 1.5};
void Led_length(void)
{
	length[0]= HAL_GPIO_ReadPin(GPIOE,L1_Pin);
	length[1]= HAL_GPIO_ReadPin(GPIOC,L2_Pin);
	
	if(length[0] == 0)
	{
		length_tim[0]++;
		if(length_tim[0] > 40 && speed  < -1 )
		{
			length_tim[0] = 0;
			aco = aco * (-1);
			
		}
	}
	 if(length[1] == 0 )
	{
		length_tim[1]++;
		if(length_tim[1] > 40 && speed >1)
		{
			length_tim[1] = 0;
			aco = aco * (-1);
			
		}
	}

}

float Led_length_speed(float flag,float speed)//������λȡ����
{
	if(flag == 1)
	{
		speed = fabs(speed);
	}
	else if(flag == 2)
	{
		speed = -fabs(speed);
	}
	else
		speed = speed;
	
	
	return speed;
	
}

void speed_change()
{
	if(HAL_GetTick() - speed_tim[0] >= 400)
	{
		flag[0] = 1; 
		ftr = factor2[rand() %(8)];
		speed_tim[0] = HAL_GetTick();
	}
	
}



void motor_move(void)
{
	if(mode_led == 2|| mode_led == 0)
	{
		if(mode_move == 1)
		{
			if(victory == 1 && mode_led == 2)
				speed = 0;
			else
				speed = 4000 * aco;
		}
		else if(mode_move == 2)
		{
			if(victory == 1 && mode_led == 2)
				speed = 0;
			else
				speed = 4000 * aco *ftr;
		}
		else  
			speed = 0;
	}
	else if(mode_led == 1)
	{
		mode_move = 0;
		speed = 0;
	}

	pid_calculate(&pid_led_motor,1,motor_led.speed,speed);
	SET_MOTOR_CURRENT_CAN1_1234(&hcan1,pid_led_motor.pid_out_speed,0,0,0);
	
}


void led_task()
{
	Led_length();
	mode_set();//ģʽ
	motor_move();
	speed_change();
	Led_on_off();
	
	
}