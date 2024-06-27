#include "lptim.h"
#include "main.h"
#include "stm32l4xx_mu.h"

/**
* @brief LPTIM MSP Initialization
* This function configures the hardware resources used in this example
* @param hlptim: LPTIM handle pointer
* @retval None
*/

extern LPTIM_HandleTypeDef hlptim1;

void HAL_LPTIM_MspInit(LPTIM_HandleTypeDef* hlptim)
{
  if(hlptim->Instance==LPTIM1)
  {
  /* USER CODE BEGIN LPTIM1_MspInit 0 */

  /* USER CODE END LPTIM1_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_LPTIM1_CLK_ENABLE();
    /* LPTIM1 interrupt Init */
    HAL_NVIC_SetPriority(LPTIM1_IRQn, 15/* 0 */, 0);
    HAL_NVIC_EnableIRQ(LPTIM1_IRQn);
  /* USER CODE BEGIN LPTIM1_MspInit 1 */

  /* USER CODE END LPTIM1_MspInit 1 */
  }

}

/**
* @brief LPTIM MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hlptim: LPTIM handle pointer
* @retval None
*/
void HAL_LPTIM_MspDeInit(LPTIM_HandleTypeDef* hlptim)
{
  if(hlptim->Instance==LPTIM1)
  {
  /* USER CODE BEGIN LPTIM1_MspDeInit 0 */

  /* USER CODE END LPTIM1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_LPTIM1_CLK_DISABLE();

    /* LPTIM1 interrupt DeInit */
    HAL_NVIC_DisableIRQ(LPTIM1_IRQn);
  /* USER CODE BEGIN LPTIM1_MspDeInit 1 */

  /* USER CODE END LPTIM1_MspDeInit 1 */
  }

}

void MX_LPTIM1_Init(void)
{

  /* USER CODE BEGIN LPTIM1_Init 0 */

  /* USER CODE END LPTIM1_Init 0 */

  /* USER CODE BEGIN LPTIM1_Init 1 */

  /* USER CODE END LPTIM1_Init 1 */
  hlptim1.Instance = LPTIM1;
  hlptim1.Init.Clock.Source = LPTIM_CLOCKSOURCE_APBCLOCK_LPOSC;
  hlptim1.Init.Clock.Prescaler = LPTIM_PRESCALER_DIV16;			//	LPTIM_PRESCALER_DIV1;	//	
  hlptim1.Init.Trigger.Source = LPTIM_TRIGSOURCE_SOFTWARE;
  hlptim1.Init.OutputPolarity = LPTIM_OUTPUTPOLARITY_HIGH;
  hlptim1.Init.UpdateMode = LPTIM_CFGR_PRELOAD;			//	LPTIM_UPDATE_IMMEDIATE;			//	
  hlptim1.Init.CounterSource = LPTIM_COUNTERSOURCE_INTERNAL;
  hlptim1.Init.Input1Source = LPTIM_INPUT1SOURCE_GPIO;
  hlptim1.Init.Input2Source = LPTIM_INPUT2SOURCE_GPIO;
  if (HAL_LPTIM_Init(&hlptim1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LPTIM1_Init 2 */

  /* USER CODE END LPTIM1_Init 2 */

}

/**
  * @brief LPTIM1 Initialization Function
  * @param None
  * @retval None
  */
//static void MX_LPTIM1_Init(void)
//{

//  /* USER CODE BEGIN LPTIM1_Init 0 */

//  /* USER CODE END LPTIM1_Init 0 */

//  /* USER CODE BEGIN LPTIM1_Init 1 */

//  /* USER CODE END LPTIM1_Init 1 */
//  hlptim1.Instance = LPTIM1;
//  hlptim1.Init.Clock.Source = LPTIM_CLOCKSOURCE_APBCLOCK_LPOSC;
//  hlptim1.Init.Clock.Prescaler = LPTIM_PRESCALER_DIV1;
//  hlptim1.Init.Trigger.Source = LPTIM_TRIGSOURCE_SOFTWARE;
//  hlptim1.Init.OutputPolarity = LPTIM_OUTPUTPOLARITY_HIGH;
//  hlptim1.Init.UpdateMode = LPTIM_UPDATE_IMMEDIATE;
//  hlptim1.Init.CounterSource = LPTIM_COUNTERSOURCE_INTERNAL;
//  hlptim1.Init.Input1Source = LPTIM_INPUT1SOURCE_GPIO;
//  hlptim1.Init.Input2Source = LPTIM_INPUT2SOURCE_GPIO;
//  if (HAL_LPTIM_Init(&hlptim1) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  /* USER CODE BEGIN LPTIM1_Init 2 */

//  /* USER CODE END LPTIM1_Init 2 */

//}

void MX_LPTIM1_DeInit(void)
{
	hlptim1.Instance = LPTIM1;
	if (HAL_LPTIM_DeInit(&hlptim1) != HAL_OK)
  {
    Error_Handler();
  }
}

void LPTIM1_IRQHandler(void)
{
  /* USER CODE BEGIN LPTIM1_IRQn 0 */
	MU_LED_Init(GREEN);
	//__HAL_RCC_GPIOE_CLK_ENABLE();
	MU_LED_Toggle(GREEN);
	__HAL_RCC_GPIOE_CLK_DISABLE();
  /* USER CODE END LPTIM1_IRQn 0 */
  HAL_LPTIM_IRQHandler(&hlptim1);
  /* USER CODE BEGIN LPTIM1_IRQn 1 */

  /* USER CODE END LPTIM1_IRQn 1 */
}
