/**
	******************************************************************************
	* @file    main.c
	* @author  fire
	* @version V1.0
	* @date    2013-xx-xx
	* @brief   AT24C02���ԣ����ģ��I2C��
	******************************************************************************
	* @attention
	*
	* ʵ��ƽ̨:Ұ�� F103-ָ���� STM32 ������ 
	* ��̳    :http://www.firebbs.cn
	* �Ա�    :https://fire-stm32.taobao.com
	*
	******************************************************************************
	*/
	
#include "stm32f10x.h"
#include "./usart/bsp_usart.h"
#include "./i2c/bsp_i2c_ee.h"
#include "temp_mlx90615.h"

 /**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	/* ���ڳ�ʼ�� */
	USART_Config();
	printf("MLX90615 ����ǹ������ �¶ȶ�ȡ���� \r\n");		

	printf("MLX90615 ID: %d \n", Temp_GetId());
	printf("MLX90615 Ambient Temp: %.2f \n", Temp_GetAmbientTemp());
	printf("MLX90615 Obejct Temp: %.2f \n", Temp_GetObjectTemp());

	while(1);
}
/*********************************************END OF FILE**********************/
