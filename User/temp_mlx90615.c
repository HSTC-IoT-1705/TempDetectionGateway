/**
 * ******************************************************************************
 * @file temp_mlx90615.c
 * @author Gump
 * @version V0.1
 * @date 2020-05-02
 * @brief
 *
 * @copyright Copyright (c) <2020> <HANSHAN NORMAL UNIVERSITY(CHAOZHOU)> All rights Reserved.
 *
 * ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "temp_mlx90615.h"
#include "i2c\bsp_i2c_gpio.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

uint32_t Temp_GetId(void) {
	uint32_t id;
	
	id = Temp_ReadWord16(MLX90615_REG_ID_LOW);
	//printf("ID low = %d,", id);
	id |= (uint32_t)Temp_ReadWord16(MLX90615_REG_ID_HIGH) << 16;

	return id;
}

float Temp_GetAmbientTemp(void) {
	float temp;

	temp = Temp_ReadWord16(MLX90615_REG_TEMP_AMBIENT) * 0.02 - 273.15;

	return temp;
}

float Temp_GetObjectTemp(void) {
	float temp;

	 temp = Temp_ReadWord16(MLX90615_REG_TEMP_OBJECT) * 0.02 - 273.15;


	// printf("----> word= %.2f \n", temp);
	// printf("----> word * 0.02 = %.2f \n", temp*0.02);
	// printf("----> word * 0.02 - 273.15 = %.2f \n", temp*0.02-273.15);
	//printf("----> Object Temp is: %.2f \n", temp);

	return temp + 3;
}

uint16_t Temp_ReadWord16(uint8_t reg) {
	uint16_t data;
	uint8_t data_high;

	/* 采用串行EEPROM随即读取指令序列，连续读取若干字节 */
	
	/* 第1步：发起I2C总线启动信号 */
	i2c_Start();

	/* 第2步：发起控制字节，高7bit是地址，bit0是读写控制位，0表示写，1表示读 */
	i2c_SendByte((MLX90615_I2C_ADDR << 1) | EEPROM_I2C_WR);	/* 此处是写指令 */
	
	/* 第3步：等待ACK */
	if (i2c_WaitAck() != 0)
	{
		goto cmd_fail;	/* EEPROM器件无应答 */
	}

	/* 第4步：发送字节地址，24C02只有256字节，因此1个字节就够了，如果是24C04以上，那么此处需要连发多个地址 */
	i2c_SendByte(reg);

	/* 第5步：等待ACK */
	if (i2c_WaitAck() != 0)
	{
		goto cmd_fail;	/* EEPROM器件无应答 */
	}

	/* 第6步：重新启动I2C总线。前面的代码的目的向EEPROM传送地址，下面开始读取数据 */
	i2c_Start();
	
	/* 第7步：发起控制字节，高7bit是地址，bit0是读写控制位，0表示写，1表示读 */
	i2c_SendByte((MLX90615_I2C_ADDR << 1) | EEPROM_I2C_RD);	/* 此处是读指令 */
	
	/* 第8步：等待ACK */
	if (i2c_WaitAck() != 0)
	{
		goto cmd_fail;	/* EEPROM器件无应答 */
	}

	/* 第9步：读取数据 */
	data = i2c_ReadByte();       /* read low byte */
	//printf("data = %02X \n", data);
	i2c_Ack();
	data_high = i2c_ReadByte();
	//printf("data_high = %02X \n", data);
	data |=  data_high << 8; /* read high byte */
	printf("data = %d \n", data);
	i2c_Ack();
	/*data = */i2c_ReadByte();       /* read and discard PEC (packet error code) */
	i2c_Ack();
	/* 发送I2C总线停止信号 */
	i2c_Stop();
	printf("i2c slave 数据读取成功\n");

	return data;

cmd_fail: /* 命令执行失败后，切记发送停止信号，避免影响I2C总线上其他设备 */
	/* 发送I2C总线停止信号 */
	i2c_Stop();
	printf("ERROR!! i2c命令执行失败！！\n");

	return data;
}


/********************************** END OF FILE *******************************/
