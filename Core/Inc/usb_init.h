#ifndef __USB_INIT_H
#define __USB_INIT_H

#include "stm32l4xx_hal.h"

#define USB_VBUS_Pin	GPIO_PIN_9
#define USB_VBUS_Port GPIOA
#define USB_VBUS_EXTI_IRQn EXTI9_5_IRQn

void MU_board_USB_detect_Init(void);
void EXTI9_5_IRQHandler(void);
void Init_after_stop(void);

#endif /* __STM32L4XX_MU_H */
