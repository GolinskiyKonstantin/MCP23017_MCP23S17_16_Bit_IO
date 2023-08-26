/*

  ******************************************************************************
  * @file 			( фаил ):   MCP23x17.c
  * @brief 		( описание ):  	
  ******************************************************************************
  * @attention 	( внимание ):	author: Golinskiy Konstantin	e-mail: golinskiy.konstantin@gmail.com
  ******************************************************************************
  
*/

/* Includes ----------------------------------------------------------*/
#include "MCP23x17.h"

#ifdef MCP23x17_SPI_HAL	
	extern SPI_HandleTypeDef MCP23x17_SPI_HAL;
#endif
#ifdef MCP23x17_I2C_HAL
	extern I2C_HandleTypeDef MCP23x17_I2C_HAL;
#endif
	
	
/*
	******************************************************************************
	* @brief	 ( описание ):  
	* @param	( параметры ):	
	* @return  ( возвращает ):	

	******************************************************************************
*/
void MCP23x17_write(uint8_t addr, uint8_t data)
{
	#ifdef MCP23x17_SPI_HAL	
	
		#ifdef CS_PORT
			// enable CS
			HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);
		#endif
	
		// передаем адрес устройства и команду что будем пасать
		uint8_t value = MCP23x17_ADDR | MCP23x17_WRITE;
		HAL_SPI_Transmit( &MCP23x17_SPI_HAL, &value, 1, 200 );
		
		// передаем адрес регистра с которым хотим работать
		HAL_SPI_Transmit( &MCP23x17_SPI_HAL, &addr, 1, 200 );
		
		// отправляем 1 байт данных в указаный ранее регистр
		HAL_SPI_Transmit( &MCP23x17_SPI_HAL, &data, 1, 200 );
	
		#ifdef CS_PORT		
			// disable CS
			HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);
		#endif
	
	#endif
	
	#ifdef MCP23x17_I2C_HAL	

		HAL_I2C_Mem_Write( &MCP23x17_I2C_HAL, MCP23x17_ADDR, addr, I2C_MEMADD_SIZE_8BIT, &data, 1, 200 );
		
	#endif
}
//----------------------------------------------------------------------------------
/*
	******************************************************************************
	* @brief	 ( описание ):  
	* @param	( параметры ):	
	* @return  ( возвращает ):	

	******************************************************************************
*/
uint8_t MCP23x17_read(uint8_t addr)
{
	uint8_t data = 0;
	
	#ifdef MCP23x17_SPI_HAL	
	
		#ifdef CS_PORT
			// enable CS
			HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);
		#endif
	
		// передаем адрес устройства и команду что будем пасать
		uint8_t value = MCP23x17_ADDR | MCP23x17_READ;
		HAL_SPI_Transmit( &MCP23x17_SPI_HAL, &value, 1, 200 );
		
		// передаем адрес регистра с которым хотим работать
		HAL_SPI_Transmit( &MCP23x17_SPI_HAL, &addr, 1, 200 );
		
		// отправляем 1 байт данных в указаный ранее регистр
		HAL_SPI_Receive( &MCP23x17_SPI_HAL, &data, 1, 200 );
		
		#ifdef CS_PORT
			// disable CS
			HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);
		#endif
			
	#endif
	
	#ifdef MCP23x17_I2C_HAL	
	
		HAL_I2C_Mem_Read( &MCP23x17_I2C_HAL, MCP23x17_ADDR, addr, I2C_MEMADD_SIZE_8BIT, &data, 1, 200 );
		
	#endif
	
	return data;
}
//----------------------------------------------------------------------------------


//----------------------------------------------------------------------------------

/************************ (C) COPYRIGHT GKP *****END OF FILE****/
