/**
	******************************************************************************
	* @file    main.c
	* @author  fire
	* @version V1.0
	* @date    2013-xx-xx
	* @brief   AT24C02测试（软件模拟I2C）
	******************************************************************************
	* @attention
	*
	* 实验平台:野火 F103-指南者 STM32 开发板 
	* 论坛    :http://www.firebbs.cn
	* 淘宝    :https://fire-stm32.taobao.com
	*
	******************************************************************************
	*/
	
#include "stm32f10x.h"
#include "./usart/bsp_usart.h"
#include "./i2c/bsp_i2c_ee.h"
#include "temp_mlx90615.h"

 /**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
	/* 串口初始化 */
	USART_Config();
	printf("MLX90615 额温枪传感器 温度读取测试 \r\n");		

	printf("MLX90615 ID: %d \n", Temp_GetId());
	printf("MLX90615 Ambient Temp: %.2f \n", Temp_GetAmbientTemp());
	printf("MLX90615 Obejct Temp: %.2f \n", Temp_GetObjectTemp());

	while(1);
}
/*********************************************END OF FILE**********************/
