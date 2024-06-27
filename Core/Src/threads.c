#include "threads.h"
#include "stm32l4xx_mu.h"
#include "main.h"
#include "usb_device.h"

osThreadId_t blinkGrnLedHandle;
const osThreadAttr_t blinkGrnLed_attributes = {
  .name = "blinkGreenLed",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};

//struct thrd_t blinkGrnLed = {
//	.thrd = &blinkGrnLedHandle,
//	.attr = &blinkGrnLed_attributes
//};

osThreadId_t turnOnUSBHandle;
const osThreadAttr_t turnOnUSB_attributes = {
  .name = "turnOnUSB",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 128 * 4
};

//struct thrd_t turnOnUSB = {
//	.thrd = &turnOnUSBHandle,
//	.attr = &turnOnUSB_attributes
//};


osThreadId_t turnOffUSBHandle;
const osThreadAttr_t turnOffUSB_attributes = {
  .name = "turnOffUSB",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 128 * 4
};

//struct thrd_t turnOffUSB = {
//	.thrd = &turnOffUSBHandle,
//	.attr = &turnOffUSB_attributes
//};

void Conf_USB(void) 
{
	/*blinkGrnLed.thrd*/ blinkGrnLedHandle = osThreadNew(GLBlink, NULL, &blinkGrnLed_attributes /*blinkGrnLed.attr*/);
	turnOnUSBHandle = osThreadNew(turnOn_USB, NULL, &turnOnUSB_attributes	/*turnOnUSB.attr*/);
	turnOffUSBHandle = osThreadNew(turnOff_USB, NULL, &turnOffUSB_attributes/*turnOffUSB.attr*/);
}

void turnOn_USB(void *argument)
{
	uint32_t flag;
  /* Infinite loop */
  for(;;)
  {
		
    flag = osThreadFlagsWait(TURN_ON_USB, osFlagsWaitAny, osWaitForever);
    if(flag == TURN_ON_USB)
    {
				MX_USB_DEVICE_Init();
		}
  }
}



void turnOff_USB(void *argument)
{
	uint32_t flag;
  /* Infinite loop */
  for(;;)
  {
		flag = osThreadFlagsWait(TURN_OFF_USB, osFlagsWaitAny, osWaitForever);
		if(flag == TURN_OFF_USB) 
			MX_USB_DEVICE_DeInit();
  }
}

void onUSBPlugOnOff(Flag_TypeDef flg)
{
	osThreadFlagsSet(blinkGrnLedHandle, BLNK_GRN);
	if(flg == TURN_OFF_USB)
		osThreadFlagsSet(turnOffUSBHandle, TURN_OFF_USB);
	else 
	if(flg == TURN_ON_USB)
		osThreadFlagsSet(turnOnUSBHandle, TURN_ON_USB);
	
}
