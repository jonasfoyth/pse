#include "tests.h"
#include "unity.h"
#include "Uart.h"

// Classe de equivalência: Valor float positivo
void setUp (void) {} /* Is run before every test, put unit init calls here. */
void tearDown (void) {} /* Is run after every test, put unit clean-up calls here.*/

void uart_tx_1(void) {
	Telegram tmpTelegram = {0};
	tmpTelegram.id = 4;
	tmpTelegram.data.temperature = 25.0;
//	TEST_ASSERT_EQUAL_INT(0, Uart_startTx(&uartRight, &tmpTelegram));
}

//// Classe de equivalência: Valor float zero
//int uart_tx_2(void) {
//	Telegram tmpTelegram = {0};
//	tmpTelegram.id = 4;
//	tmpTelegram.data.temperature = 0;
//}
//
//// Classe de equivalência: Valor float negativo
//int uart_tx_3(void) {
//	Telegram tmpTelegram = {0};
//	tmpTelegram.id = 4;
//	tmpTelegram.data.temperature = -2.3;
//}
//
//// Classe de equivalência: Valor NaN
//int uart_tx_4(void) {
//	Telegram tmpTelegram = {0};
//	tmpTelegram.id = 4;
//    float value = sqrt(-1.0);
//	tmpTelegram.data.temperature = value;
//}
//
//
//// Classe de equivalência: Valor float invalido
void uart_tx_5(void) {
	Telegram tmpTelegram = {0};
	tmpTelegram.id = 4;
    float value = 1.0 / 0.0;
	tmpTelegram.data.temperature = value;
//	TEST_ASSERT_EQUAL_INT(0, Uart_startTx(&uartRight, &tmpTelegram));
}


