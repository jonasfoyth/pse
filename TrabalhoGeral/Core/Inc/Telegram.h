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
	broadcast,
	EM,
	EV,
} Telegram_cmd;

typedef enum {
	Request,
	Answers,
} Telegram_direction;

typedef struct {
	Telegram_cmd command,
	Telegram_direction direction,

} Telegram;



#endif /* INC_TELEGRAM_H_ */
