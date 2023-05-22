#include "Uart.h"

//#include "main.h"

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
	// Initialize the ID
	this->txBuffer.id = 4;

	// Initialize events
	for (int i = 0; i < NumberOfUartEvents; i++) {
		this->event[i] = xSemaphoreCreateBinaryStatic(&this->eventBuffer[i]);
	}

	// Initialize tx lock
	this->txLock = xSemaphoreCreateBinaryStatic(&this->txLockBuffer);
	xSemaphoreGive(this->txLock);

	// Start the reception
	Uart_startRx(this);
}

void Uart_deinit(Uart * const this)
{
	HAL_UART_Abort(this->handler);

	// Deinitialize events
	for (int i = 0; i < NumberOfUartEvents; i++) {
		vSemaphoreDelete(this->event[i]);
	}

	vSemaphoreDelete(this->txLock);
}

void Uart_startTx(Uart * const this, Telegram * const msg)
{
	xSemaphoreTake(this->txLock, 20);	//Wait at most 20ms

	// Salva a mensagem no próprio buffer
	this->txBuffer.id = msg->id;
	this->txBuffer.data.temperature = msg->data.temperature;
	this->txBuffer.data.dontCare1 = msg->data.dontCare1;
	this->txBuffer.data.dontCare2 = msg->data.dontCare2;

	// Envia os dados
	HAL_UART_Transmit_DMA(this->handler, (uint8_t*)&(this->txBuffer), sizeof(Telegram));

	// Desabilita half transfer interrupt, é inútil pra gente
	__HAL_DMA_DISABLE_IT(this->handler->hdmarx, DMA_IT_HT);
}

void Uart_startRx(Uart * this)
{
	HAL_UARTEx_ReceiveToIdle_DMA(this->handler, (uint8_t*)&(this->rxBuffer), sizeof(Telegram));
	__HAL_DMA_DISABLE_IT(this->handler->hdmarx, DMA_IT_HT);
}

void Uart_setEvent(Uart * const this, UartEvents event)
{
	// give a semaphore
	xSemaphoreGive(this->event[event]);
}

void Uart_setEventFromISR(Uart * const this, UartEvents event)
{
	// give a semaphore
	xSemaphoreGiveFromISR(this->event[event], NULL);
}

/*
 * Return 	0 if ok
 * 			-1 if timeout or error
 */
int Uart_waitEvent(Uart * const this, UartEvents event, uint32_t timeout)
{
	// wait for semaphore
	if (xSemaphoreTake(this->event[event], timeout) == pdFALSE) {
		return -1;
	}

	return 0;
}

// Essas funções serão chamadas sempre pelos interrupt handlers
static void Uart_txCompleteCallback(Uart * const this)
{
	// Libera uart para que outra task possa fazer a transmissão
	xSemaphoreGiveFromISR(this->txLock, NULL);

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
