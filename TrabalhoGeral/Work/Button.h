/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BUTTON_CLASS_H__
#define __BUTTON_CLASS_H__

#include <stdint.h>
#include "FreeRTOS.h"
#include "event_groups.h"

#define BUTTON_BIT	( 1 << 0 )

void Button_Init();
int Button_Wait();
void Button_Pressed();

#endif /* __BUTTON_CLASS_H__ */
