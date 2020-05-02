/**
 * ******************************************************************************
 * @file temp_mlx90615.h
 * @author Gump
 * @version V0.1
 * @date 2020-05-02
 * @brief 
 * 
 * @copyright Copyright (c) <2020> <HANSHAN NORMAL UNIVERSITY(CHAOZHOU)> All rights Reserved.
 * 
 * ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TEMP_MLX90615_H__
#define __TEMP_MLX90615_H__ 

/* Includes ------------------------------------------------------------------*/
#include <inttypes.h>

/* Exported typedef -----------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
#define MLX90615_I2C_ADDR		0x5B /*!< default MLX90615 I2C address */

#define MLX90615_REG_ID_LOW			0x1E /*!< ROM - ID number low byte */
#define MLX90615_REG_ID_HIGH		0x1F /*!< ROM - ID number high byte */

#define MLX90615_REG_TEMP_AMBIENT	0x26 /*!< RAM - ambient temperature register */
#define MLX90615_REG_TEMP_OBJECT	0x27 /*!< RAM - object temperature register  */

/* Exported function -----------------------------------------------*/
uint32_t Temp_GetId(void);
float Temp_GetAmbientTemp(void);
float Temp_GetObjectTemp(void);
uint16_t Temp_ReadWord16(uint8_t reg);

#endif /* __TEMP_MLX90615_H__ */ 
/********************************** END OF FILE *******************************/
