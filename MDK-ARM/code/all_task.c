#include "all_task.h"



/*��ʼ��*/
void base_Init(void)
{
	CAN1_FILTER_CONFIG(&hcan1);								//����������CAN1
	CAN2_FILTER_CONFIG(&hcan2);								//����������CAN2
	HAL_CAN_ActivateNotification(&hcan1,CAN_IT_RX_FIFO0_MSG_PENDING);   //can1�ж�
	HAL_CAN_ActivateNotification(&hcan2,CAN_IT_RX_FIFO0_MSG_PENDING);   //can2�ж�
	
	//��������  ��ʱ�ж�  ռλ
	HAL_UART_Receive_IT_IDLE(&huart3, remote_control_lever_buff, 100);	//ң����	
}

/*�����ʼ��*/
void task_Init(void)
{
	Led_Init();

}











