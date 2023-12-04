#include "all_task.h"



/*初始化*/
void base_Init(void)
{
	CAN1_FILTER_CONFIG(&hcan1);								//过滤器配置CAN1
	CAN2_FILTER_CONFIG(&hcan2);								//过滤器配置CAN2
	HAL_CAN_ActivateNotification(&hcan1,CAN_IT_RX_FIFO0_MSG_PENDING);   //can1中断
	HAL_CAN_ActivateNotification(&hcan2,CAN_IT_RX_FIFO0_MSG_PENDING);   //can2中断
	
	//串口配置  闲时中断  占位
	HAL_UART_Receive_IT_IDLE(&huart3, remote_control_lever_buff, 100);	//遥控器	
}

/*任务初始化*/
void task_Init(void)
{
	Led_Init();

}











