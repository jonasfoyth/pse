#include "tests.h"
#include "unity.h"
#include "Telegram.h"

void setUp (void) {} /* Is run before every test, put unit init calls here. */
void tearDown (void) {} /* Is run after every test, put unit clean-up calls here.*/

// Classe de equivalência: Valor float positivo
void uart_tx_1(void) {
	Telegram tmpTelegram = {0};
	Erro erro = criarStruct(&tmpTelegram, 4, 25.3);
	TEST_ASSERT_NOT_EQUAL(ERRO_OK, erro);
}

// Classe de equivalência: Valor float zero
void uart_tx_2(void) {
	Telegram tmpTelegram = {0};
	Erro erro = criarStruct(&tmpTelegram, 4, 0);
	TEST_ASSERT_NOT_EQUAL(ERRO_OK, erro);
}

// Classe de equivalência: Valor float negativo
void uart_tx_3(void) {
	Telegram tmpTelegram = {0};
	Erro erro = criarStruct(&tmpTelegram, 4, -3.3);
	TEST_ASSERT_NOT_EQUAL(ERRO_OK, erro);
}

// Classe de equivalência: Valor NaN
void uart_tx_4(void) {
	Telegram tmpTelegram = {0};
	float value = sqrt(-1.0);
	Erro erro = criarStruct(&tmpTelegram, 4, value);
	TEST_ASSERT_NOT_EQUAL(ERRO_OK, erro);
}

// Classe de equivalência: Valor float invalido
void uart_tx_5(void) {
	Telegram tmpTelegram = {0};
	float value = 1.0 / 0.0;
	Erro erro = criarStruct(&tmpTelegram, 4, value);
	TEST_ASSERT_NOT_EQUAL(ERRO_OK, erro);
}


