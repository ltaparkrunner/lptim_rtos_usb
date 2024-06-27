#ifndef __STM32L4XX_MU_H
#define __STM32L4XX_MU_H

#include "stm32l4xx_hal.h"

typedef enum
{
	GREEN,
  RED
} Led_TypeDef;

#define G_PIN GPIO_PIN_14   				// Светодиоды 2 шт. на маленькой плате
#define G_GPIO_PORT GPIOE
#define R_PIN GPIO_PIN_15
#define R_GPIO_PORT GPIOE

#define SoundSign_Pin GPIO_PIN_7      // ?инамик на плате пульта
#define SoundSign_GPIO_Port GPIOE
#define HL3Sign_Pin GPIO_PIN_4				// —ветодиоды 3 шт. на плате пульта
#define HL3Sign_GPIO_Port GPIOE
#define HL2Sign_Pin GPIO_PIN_5
#define HL2Sign_GPIO_Port GPIOE
#define HL1Sign_Pin GPIO_PIN_6
#define HL1Sign_GPIO_Port GPIOE

#define LEDx_GPIO_CLK_ENABLE(__LED__)      __HAL_RCC_GPIOE_CLK_ENABLE()
#define LEDx_GPIO_CLK_DISABLE(__LED__)     __HAL_RCC_GPIOE_CLK_DISABLE()

void MU_LED_Init(Led_TypeDef Led);
void MU_LED_DeInit(Led_TypeDef Led);
void MU_LED_On(Led_TypeDef Led);
void MU_LED_Off(Led_TypeDef Led);
void MU_LED_Toggle(Led_TypeDef Led);

void MU_Sound_Init(void);

void MU_board_LEDs_Init(void);
void MU_board_LEDs_DeInit(void);
void MU_LED_Toggle(Led_TypeDef Led);

void GPIO_ConfigAN(void);

#endif /* __STM32L4XX_MU_H */
