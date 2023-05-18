#include "Uart.h"
#include "cmsis_os2.h"

#define UART_RXBUFFERSIZE 26

Uart uartLeft = {.handler = &huart4}; // Uart connected to the last EM
Uart uartRight = {.handler = &huart5}; // Uart Connected to EV side

// Private methods
static void Uart_txCompleteCallback(Uart * const this);
static void Uart_rxCompleteCallback(Uart * const this);
static void Uart_rxErrorCallback(Uart * const this);

// Class methods definitions

void Uart_init(Uart * const this)
{
	this->txBuffer.id = 4;
	// Initialize events

	// Start the reception
	Uart_startRx(this);
}

void Uart_deinit(Uart * const this)
{
	HAL_UART_Abort(this->handler);
}


void Uart_startTx(Uart * this, float temperature)
{
	this->txBuffer.data.temperature = temperature;

	HAL_UART_Transmit_DMA(this->handler, this->txBuffer, sizeof(Telegram));
	__HAL_DMA_DISABLE_IT(this->handler->hdmarx, DMA_IT_HT);	//Disable useless half transfer here
}

void Uart_startRx(Uart * this)
{
	HAL_UARTEx_ReceiveToIdle_DMA(this->handler, this->rxBuffer, sizeof(Telegram));
	__HAL_DMA_DISABLE_IT(this->handler->hdmarx, DMA_IT_HT); //Disable useless half transfer here
}

void Uart_setEvent(Uart * const this, UartEvents event)
{
	// Release the semaphore
}

void Uart_setEventFromISR(Uart * const this, UartEvents event)
{
	// Release the semaphore
}

/*
 * Return 	0 if ok
 * 			-1 if timeout or error
 */
int Uart_waitEvent(Uart * const this, UartEvents event, uint32_t timeout)
{
	// wait for semaphore
}


// Essas funções serão chamadas sempre pelos interrupt handlers
static void Uart_txCompleteCallback(Uart * const this)
{
	// Seta flag the dados transmitidos.
	Uart_setEventFromISR(this, UartEvent_txComplete);
}

static void Uart_rxCompleteCallback(Uart * const this)
{
	// Seta flag the dados recebido.
	Uart_setEventFromISR(this, UartEvent_rxComplete);

	// Reinicia recepção.
	Uart_startRx(this);
}

static void Uart_rxErrorCallback(Uart * const this)
{
	// Cancela qualquer operação
	HAL_UART_Abort(this->handler);

	// Reinicia recepção.
	Uart_startRx(this);
}


// Callbacks


// Funções chamadas de acordo com alguns eventos da UART
// Faça o que precisar aqui, mas cuidado, aqui ainda estamos dentro
// da interrupção da uart, seja breve.
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
	Uart *uart;

	if (huart == uartRight.handler) {
		uart = &uartRight;
	} else if (huart == uartLeft.handler) {
		uart = &uartLeft;
	} else {
		return;
	}

	Uart_rxErrorCallback(uart);
	return;
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	Uart *uart;

	if (huart == uartRight.handler) {
		uart = &uartRight;
	} else if (huart == uartLeft.handler) {
		uart = &uartLeft;
	} else {
		return;
	}

	// Checa se a quantidade de dados recebidos está certa
	if (Size != sizeof(Telegram)) {
		Uart_rxErrorCallback(uart);
		return;
	}

	Uart_rxCompleteCallback(uart);
	return;

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	Uart *uart;

	if (huart == uartRight.handler) {
		uart = &uartRight;
	} else if (huart == uartLeft.handler) {
		uart = &uartLeft;
	} else {
		return;
	}

	Uart_rxCompleteCallback(uart);
	return;
}

void HAL_UART_TxHalfCpltCallback(UART_HandleTypeDef *huart)
{
	Uart *uart;

	if (huart == uartRight.handler) {
		uart = &uartRight;
	} else if (huart == uartLeft.handler) {
		uart = &uartLeft;
	} else {
		return;
	}

	Uart_txCompleteCallback(uart);
	return;
}
