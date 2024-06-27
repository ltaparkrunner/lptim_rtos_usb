#include "stm32l4xx_mu.h"

uint16_t LED_GPIO_PIN[2] = {G_PIN, R_PIN };
GPIO_TypeDef * LED_GPIO_PORT[2] = {G_GPIO_PORT, R_GPIO_PORT};


/**
  * @brief  Configure LED GPIO.
  * @param  Led: LED to be configured.
  *         This parameter can be one of the following values:
  *            @arg  LED2 or LED4 on Nucleo-64 with external SMPS
  * @retval None
  */
void MU_LED_Init(Led_TypeDef Led)
{
  GPIO_InitTypeDef  GPIO_InitStruct = {0};

  /* Enable the GPIO_LED Clock */
  LEDx_GPIO_CLK_ENABLE(Led);
	if(Led == GREEN || Led == RED){
  /* Configure the GPIO_LED pin */
		GPIO_InitStruct.Pin   = LED_GPIO_PIN[Led];
		GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull  = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(LED_GPIO_PORT[Led], &GPIO_InitStruct);
	}
}

/**
  * @brief  DeInitialize LED GPIO.
  * @param  Led: LED to be deinitialized.
  *         This parameter can be one of the following values:
  *            @arg  LED2 or LED4 on Nucleo-64 with external SMPS
  * @note BSP_LED_DeInit() does not disable the GPIO clock
  * @retval None
  */
void MU_LED_DeInit(Led_TypeDef Led)
{
  GPIO_InitTypeDef  GPIO_InitStruct;

  /* Turn off LED */
  HAL_GPIO_WritePin(LED_GPIO_PORT[Led], LED_GPIO_PIN[Led], GPIO_PIN_RESET);
  /* DeInit the GPIO_LED pin */
  GPIO_InitStruct.Pin = LED_GPIO_PIN[Led];
  HAL_GPIO_DeInit(LED_GPIO_PORT[Led], GPIO_InitStruct.Pin);
}

/**
  * @brief  Turn selected LED On.
  * @param  Led: Specifies the Led to be set on.
  *   This parameter can be one of following parameters:
  *            @arg  LED2 or LED4 on Nucleo-64 with external SMPS
  * @retval None
  */
void MU_LED_On(Led_TypeDef Led)
{
  HAL_GPIO_WritePin(LED_GPIO_PORT[Led], LED_GPIO_PIN[Led], GPIO_PIN_RESET);
}

/**
  * @brief  Turn selected LED Off.
  * @param  Led: Specifies the Led to be set off.
  *   This parameter can be one of following parameters:
  *            @arg  LED2 or LED4 on Nucleo-64 with external SMPS
  * @retval None
  */
void MU_LED_Off(Led_TypeDef Led)
{
  HAL_GPIO_WritePin(LED_GPIO_PORT[Led], LED_GPIO_PIN[Led], GPIO_PIN_SET);
}

/**
  * @brief  Toggle the selected LED.
  * @param  Led: Specifies the Led to be toggled.
  *   This parameter can be one of following parameters:
  *            @arg  LED2 or LED4 on Nucleo-64 with external SMPS
  * @retval None
  */
void MU_LED_Toggle(Led_TypeDef Led)
{
  HAL_GPIO_TogglePin(LED_GPIO_PORT[Led], LED_GPIO_PIN[Led]);
}

void MU_Sound_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin   = SoundSign_Pin;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	// TODO: delete one of two WritePin below
	HAL_GPIO_WritePin(SoundSign_GPIO_Port, SoundSign_Pin, GPIO_PIN_RESET);
	HAL_GPIO_Init(SoundSign_GPIO_Port, &GPIO_InitStruct);
	HAL_GPIO_WritePin(SoundSign_GPIO_Port, SoundSign_Pin, GPIO_PIN_RESET);
}

void MU_board_LEDs_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStruct = {0};

  /* Enable the GPIOLED Clock */
  __HAL_RCC_GPIOE_CLK_ENABLE();
	{
  /* Configure the GPIO_LED pin */
		GPIO_InitStruct.Pin   = HL3Sign_Pin | HL2Sign_Pin | HL1Sign_Pin;
		GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull  = GPIO_PULLDOWN;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_WritePin(HL1Sign_GPIO_Port, HL3Sign_Pin | HL2Sign_Pin | HL1Sign_Pin, GPIO_PIN_RESET);
		HAL_GPIO_Init(HL1Sign_GPIO_Port, &GPIO_InitStruct);
	}
}


void MU_board_LEDs_DeInit(void)
{
	{
  /* Disable the GPIO_LED pin */
		HAL_GPIO_WritePin(HL1Sign_GPIO_Port, HL3Sign_Pin | HL2Sign_Pin | HL1Sign_Pin, GPIO_PIN_RESET);
		HAL_GPIO_DeInit(GPIOE, HL3Sign_Pin | HL2Sign_Pin | HL1Sign_Pin);
	}
	/* Disable the GPIOLED Clock */
	//__HAL_RCC_GPIOE_CLK_DISABLE();
}

void GPIO_ConfigAN(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* Configure all GPIO as analog to reduce current consumption on non used IOs */
  /* Enable GPIOs clock */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
	//__HAL_RCC_GPIOH_CLK_ENABLE();


  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;	//GPIO_MODE_INPUT;		//GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Pin = GPIO_PIN_All/*;*/		 & ~GPIO_PIN_13 & ~GPIO_PIN_14;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct); 
	GPIO_InitStruct.Pin = GPIO_PIN_All;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = GPIO_PIN_All;		// & ~GPIO_PIN_14 & ~GPIO_PIN_15; 
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = GPIO_PIN_All;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = GPIO_PIN_All; // & ~GPIO_PIN_14 & ~GPIO_PIN_15; 
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
	//GPIO_InitStruct.Pin = GPIO_PIN_All; // & ~GPIO_PIN_14 & ~GPIO_PIN_15; 
  //HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);


  /* Disable GPIOs clock */
  //__HAL_RCC_GPIOA_CLK_DISABLE();
  __HAL_RCC_GPIOB_CLK_DISABLE();
  __HAL_RCC_GPIOC_CLK_DISABLE();
  __HAL_RCC_GPIOD_CLK_DISABLE();
  __HAL_RCC_GPIOE_CLK_DISABLE(); // * is used for leds
	//__HAL_RCC_GPIOH_CLK_DISABLE();
}
