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

	/* ���ô���EEPROM�漴��ȡָ�����У�������ȡ�����ֽ� */
	
	/* ��1��������I2C���������ź� */
	i2c_Start();

	/* ��2������������ֽڣ���7bit�ǵ�ַ��bit0�Ƕ�д����λ��0��ʾд��1��ʾ�� */
	i2c_SendByte((MLX90615_I2C_ADDR << 1) | EEPROM_I2C_WR);	/* �˴���дָ�� */
	
	/* ��3�����ȴ�ACK */
	if (i2c_WaitAck() != 0)
	{
		goto cmd_fail;	/* EEPROM������Ӧ�� */
	}

	/* ��4���������ֽڵ�ַ��24C02ֻ��256�ֽڣ����1���ֽھ͹��ˣ������24C04���ϣ���ô�˴���Ҫ���������ַ */
	i2c_SendByte(reg);

	/* ��5�����ȴ�ACK */
	if (i2c_WaitAck() != 0)
	{
		goto cmd_fail;	/* EEPROM������Ӧ�� */
	}

	/* ��6������������I2C���ߡ�ǰ��Ĵ����Ŀ����EEPROM���͵�ַ�����濪ʼ��ȡ���� */
	i2c_Start();
	
	/* ��7������������ֽڣ���7bit�ǵ�ַ��bit0�Ƕ�д����λ��0��ʾд��1��ʾ�� */
	i2c_SendByte((MLX90615_I2C_ADDR << 1) | EEPROM_I2C_RD);	/* �˴��Ƕ�ָ�� */
	
	/* ��8�����ȴ�ACK */
	if (i2c_WaitAck() != 0)
	{
		goto cmd_fail;	/* EEPROM������Ӧ�� */
	}

	/* ��9������ȡ���� */
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
	/* ����I2C����ֹͣ�ź� */
	i2c_Stop();
	printf("i2c slave ���ݶ�ȡ�ɹ�\n");

	return data;

cmd_fail: /* ����ִ��ʧ�ܺ��мǷ���ֹͣ�źţ�����Ӱ��I2C�����������豸 */
	/* ����I2C����ֹͣ�ź� */
	i2c_Stop();
	printf("ERROR!! i2c����ִ��ʧ�ܣ���\n");

	return data;
}


/********************************** END OF FILE *******************************/
