#ifndef __TRHEADS_H
#define __THREADS_H

#include "cmsis_os.h"

typedef enum
{
	BLNK_GRN = 2,
  TURN_ON_USB = 16,
	TURN_OFF_USB = 32
} Flag_TypeDef;

struct thrd_t {
	osThreadId_t *thrd;
	const osThreadAttr_t *attr;
};

extern struct thrd_t blinkGrnLed;
extern struct thrd_t turnOnOffUSB;

void Conf_USB(void);
void onUSBPlugOnOff(Flag_TypeDef flg);
//void onUSBPlugOff(Flag_TypeDef flg);

//void blink_green_led(void *argument);
void turnOn_USB(void *argument);
void turnOff_USB(void *argument);

#endif /* __THREADS_H */
