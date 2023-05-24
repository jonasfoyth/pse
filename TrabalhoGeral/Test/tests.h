#include "Telegram.h"
//Uart tests
void uart_tx_1(void);
void uart_tx_2(void);
void uart_tx_3(void);
void uart_tx_4(void);
void uart_tx_5(void);

//adc tests
void adc_1(void);
void adc_2(void);
void adc_3(void);
void adc_4(void);
void adc_5(void);

void begin_tests(void);

void TEST_ASSERT_ENUM_EQUAL(const char* testName, Erro opcao1, Erro opcao2);
void TEST_ASSERT_ENUM_NOT_EQUAL(const char* testName, Erro opcao1, Erro opcao2);
void TEST_ASSERT_TMP_EQUAL(const char* testName, float opcao1, float opcao2);
void TEST_ASSERT_TMP_NOT_EQUAL(const char* testName, float opcao1, float opcao2);
