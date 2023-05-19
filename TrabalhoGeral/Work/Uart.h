/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UART_CLASS_H__
#define __UART_CLASS_H__

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#include "Telegram.h"

// Enum for uart event
typedef enum {
	UartEvent_rxComplete,
	UartEvent_txComplete,
	NumberOfUartEvents,
} UartEvents;

// Uart Class

typedef struct {
	UART_HandleTypeDef *const handler;
	int event[NumberOfUartEvents];
	Telegram rxBuffer;
	Telegram txBuffer;
} Uart;

// Class methods

void Uart_init(Uart * const this);		// Constructor
void Uart_deinit(Uart * const this);	// Destructor

void Uart_startTx(Uart * const this, float temperature);
void Uart_startRx(Uart * const this);

void Uart_setEvent(Uart * const this, UartEvents event);
void Uart_setEventFromISR(Uart * const this, UartEvents event);
int Uart_waitEvent(Uart * const this, UartEvents event, uint32_t timeout);

// Exported objects

extern Uart uartLeft;
extern Uart uartRight;

#endif /* __UART_CLASS_H__ */
