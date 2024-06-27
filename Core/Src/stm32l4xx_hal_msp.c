/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file         stm32l4xx_hal_msp.c
  * @brief        This file provides code for the MSP Initialization
  *               and de-Initialization codes.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN Define */

/* USER CODE END Define */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN Macro */

/* USER CODE END Macro */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* External functions --------------------------------------------------------*/
/* USER CODE BEGIN ExternalFunctions */

/* USER CODE END ExternalFunctions */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
/**
  * Initializes the Global MSP.
  */
void HAL_MspInit(void)
{
  /* USER CODE BEGIN MspInit 0 */

  /* USER CODE END MspInit 0 */

  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();

  /* System interrupt init*/
  /* PendSV_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(PendSV_IRQn, 15, 0);

  /* USER CODE BEGIN MspInit 1 */

  /* USER CODE END MspInit 1 */
}

/**
* @brief LPTIM MSP Initialization
* This function configures the hardware resources used in this example
* @param hlptim: LPTIM handle pointer
* @retval None
*/
//void HAL_LPTIM_MspInit(LPTIM_HandleTypeDef* hlptim)
//{
//  if(hlptim->Instance==LPTIM1)
//  {
//  /* USER CODE BEGIN LPTIM1_MspInit 0 */

//  /* USER CODE END LPTIM1_MspInit 0 */
//    /* Peripheral clock enable */
//    __HAL_RCC_LPTIM1_CLK_ENABLE();
//    /* LPTIM1 interrupt Init */
//    HAL_NVIC_SetPriority(LPTIM1_IRQn, 5, 0);
//    HAL_NVIC_EnableIRQ(LPTIM1_IRQn);
//  /* USER CODE BEGIN LPTIM1_MspInit 1 */

//  /* USER CODE END LPTIM1_MspInit 1 */
//  }

//}

///**
//* @brief LPTIM MSP De-Initialization
//* This function freeze the hardware resources used in this example
//* @param hlptim: LPTIM handle pointer
//* @retval None
//*/
//void HAL_LPTIM_MspDeInit(LPTIM_HandleTypeDef* hlptim)
//{
//  if(hlptim->Instance==LPTIM1)
//  {
//  /* USER CODE BEGIN LPTIM1_MspDeInit 0 */

//  /* USER CODE END LPTIM1_MspDeInit 0 */
//    /* Peripheral clock disable */
//    __HAL_RCC_LPTIM1_CLK_DISABLE();

//    /* LPTIM1 interrupt DeInit */
//    HAL_NVIC_DisableIRQ(LPTIM1_IRQn);
//  /* USER CODE BEGIN LPTIM1_MspDeInit 1 */

//  /* USER CODE END LPTIM1_MspDeInit 1 */
//  }

//}

/**
* @brief RTC MSP Initialization
* This function configures the hardware resources used in this example
* @param hrtc: RTC handle pointer
* @retval None
*/
void HAL_RTC_MspInit(RTC_HandleTypeDef* hrtc)
{
  if(hrtc->Instance==RTC)
  {
  /* USER CODE BEGIN RTC_MspInit 0 */

  /* USER CODE END RTC_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_RTC_ENABLE();
  /* USER CODE BEGIN RTC_MspInit 1 */

  /* USER CODE END RTC_MspInit 1 */
  }

}

/**
* @brief RTC MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hrtc: RTC handle pointer
* @retval None
*/
void HAL_RTC_MspDeInit(RTC_HandleTypeDef* hrtc)
{
  if(hrtc->Instance==RTC)
  {
  /* USER CODE BEGIN RTC_MspDeInit 0 */

  /* USER CODE END RTC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_RTC_DISABLE();
  /* USER CODE BEGIN RTC_MspDeInit 1 */

  /* USER CODE END RTC_MspDeInit 1 */
  }

}

/* USER CODE BEGIN 1 */

#define MU_SPI2_SCK_GPIO_PIN            GPIO_PIN_10
#define MU_SPI2_MISO_GPIO_PIN           GPIO_PIN_2
#define MU_SPI2_MOSI_GPIO_PIN           GPIO_PIN_3
#define MU_SPI2_SCK_GPIO_PORT           GPIOB
#define MU_SPI2_MISO_GPIO_PORT          GPIOC
#define MU_SPI2_MOSI_GPIO_PORT          GPIOC
#define MU_SPI2_SCK_GPIO_AF             GPIO_AF5_SPI2
#define MU_SPI2_MOSI_GPIO_AF            GPIO_AF5_SPI2
#define MU_SPI2_MISO_GPIO_AF            GPIO_AF5_SPI2
#define MU_SPI2_NSS_GPIO_PIN						GPIO_PIN_9
#define MU_SPI2_NSS_GPIO_PORT						GPIOB

void HAL_SPI_MspInit(SPI_HandleTypeDef *spiHandle)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  /* USER CODE BEGIN SPI2_MspInit 0 */

  /* USER CODE END SPI2_MspInit 0 */
  /* Enable Peripheral clock */
  __HAL_RCC_SPI2_CLK_ENABLE();

  /**SPI2 GPIO Configuration
  PB10     ------> SPI2_SCK
  PC2      ------> SPI2_MISO
  PC3      ------> SPI2_MOSI
	PB9			 ------> SPI2_NSS
    */
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = MU_SPI2_MOSI_GPIO_AF;
  GPIO_InitStruct.Pin = MU_SPI2_MOSI_GPIO_PIN;
  HAL_GPIO_Init(MU_SPI2_MOSI_GPIO_PORT, &GPIO_InitStruct);
	
  GPIO_InitStruct.Alternate = MU_SPI2_MISO_GPIO_AF;
  GPIO_InitStruct.Pin = MU_SPI2_MISO_GPIO_PIN;
  HAL_GPIO_Init(MU_SPI2_MISO_GPIO_PORT, &GPIO_InitStruct);
	
  GPIO_InitStruct.Alternate = MU_SPI2_SCK_GPIO_AF;
  GPIO_InitStruct.Pin = MU_SPI2_SCK_GPIO_PIN;
  HAL_GPIO_Init(MU_SPI2_SCK_GPIO_PORT, &GPIO_InitStruct);

  /* USER CODE BEGIN SPI2_MspInit 1 */
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Pin = MU_SPI2_NSS_GPIO_PIN;
	HAL_GPIO_Init(MU_SPI2_NSS_GPIO_PORT, &GPIO_InitStruct);
  /* USER CODE END SPI2_MspInit 1 */
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef *spiHandle)
{
  /* USER CODE BEGIN SPI2_MspDeInit 0 */

  /* USER CODE END SPI2_MspDeInit 0 */
  /* Peripheral clock disable */
  __HAL_RCC_SPI2_CLK_DISABLE();

  /**SPI2 GPIO Configuration
  PB10     ------> SPI2_SCK
  PC2      ------> SPI2_MISO
  PC3      ------> SPI2_MOSI
    */
  HAL_GPIO_DeInit(MU_SPI2_MOSI_GPIO_PORT, MU_SPI2_MOSI_GPIO_PIN);
  HAL_GPIO_DeInit(MU_SPI2_MISO_GPIO_PORT, MU_SPI2_MISO_GPIO_PIN);
  HAL_GPIO_DeInit(MU_SPI2_SCK_GPIO_PORT, MU_SPI2_SCK_GPIO_PIN);

  /* USER CODE BEGIN SPI2_MspDeInit 1 */
	GPIO_InitTypeDef GPIO_InitStruct;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = GPIO_PIN_All;// & ~GPIO_PIN_14 & ~GPIO_PIN_15; 
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = GPIO_PIN_All;
	__HAL_RCC_GPIOB_CLK_DISABLE();
  __HAL_RCC_GPIOC_CLK_DISABLE();
  /* USER CODE END SPI2_MspDeInit 1 */
}

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
