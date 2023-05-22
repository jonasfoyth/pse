/*
 * Telegram.h
 *
 *  Created on: May 3, 2023
 *      Author: bruno
 */

#ifndef INC_TELEGRAM_H_
#define INC_TELEGRAM_H_

#include "stdint.h"

typedef enum {
	Display = 1,
	Accel,
	Gyro,
	Temp,
	Potenciometer,
	Requisition = 255,
} Telegram_id;

typedef struct {
	float temperature;
	float dontCare1;
	float dontCare2;
} Telegram_data;

typedef struct __attribute__((packed)){
	Telegram_id id;
	Telegram_data data;
} Telegram;

#endif /* INC_TELEGRAM_H_ */
