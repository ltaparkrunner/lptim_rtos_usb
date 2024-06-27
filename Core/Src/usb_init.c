#include "usb_init.h"
#include "cmsis_os.h"
#include "threads.h"
#include "main.h"
#include "usb_device.h"

void MU_board_USB_detect_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct = {0};

  /* Enable the USB detect pin */
  __HAL_RCC_GPIOA_CLK_ENABLE();
	{
  /* Configure the GPIO_LED pin 1*/
		GPIO_InitStruct.Pin   = USB_VBUS_Pin;
		GPIO_InitStruct.Mode  = GPIO_MODE_IT_RISING_FALLING;//GPIO_MODE_IT_RISING;
		GPIO_InitStruct.Pull  = GPIO_PULLDOWN;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(USB_VBUS_Port, &GPIO_InitStruct);
		/* Enable and set VBUS_DET EXTI Interrupt to the lowest priority */
    HAL_NVIC_SetPriority(USB_VBUS_EXTI_IRQn, 0x0F /*0*/, 0);
    HAL_NVIC_EnableIRQ(USB_VBUS_EXTI_IRQn);
	}
}

void EXTI9_5_IRQHandler(void)
{
//	osThreadFlagsSet( blink_green_led, 8);
	__HAL_GPIO_EXTI_CLEAR_IT(USB_VBUS_Pin);
	GPIO_PinState res = HAL_GPIO_ReadPin(USB_VBUS_Port, USB_VBUS_Pin);
	if(res == GPIO_PIN_SET) 
		onUSBPlugOnOff(TURN_ON_USB);
	else if(res == GPIO_PIN_RESET) 
		onUSBPlugOnOff(TURN_OFF_USB);
/*
#if (defined(SX1276MB1MAS) | defined(SX1276MB1LAS) | defined(SX1272MB2DAS))
  HAL_EXTI_IRQHandler(&H_EXTI_5);
#endif
*/
}

extern PCD_HandleTypeDef hpcd_USB_OTG_FS;
void Init_after_stop(void) {
	SystemClock_Config();
	//MX_USB_DEVICE_Init();
	HAL_PCD_MspInit(&hpcd_USB_OTG_FS);
}
