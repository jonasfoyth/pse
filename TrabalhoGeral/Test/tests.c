#include "tests.h"
#include "Telegram.h"
#include "string.h"
#include "stdio.h"
#include "math.h"
#include "unity.h"
#include "Sensor.h"


//char test_results[1024];
//int results_index = 0;

void setUp (void) {} /* Is run before every test, put unit init calls here. */
void tearDown (void) {} /* Is run after every test, put unit clean-up calls here.*/

// begin: assert functions
void TEST_ASSERT_ENUM_EQUAL(const char* testName, Erro opcao1, Erro opcao2) {
    if (opcao1 == opcao2) {
        printf("%s: OK", testName);
    } else {
        printf("%s: FAILED", testName);
    }
}

void TEST_ASSERT_ENUM_NOT_EQUAL(const char* testName, Erro opcao1, Erro opcao2) {
    if (opcao1 != opcao2) {
        printf("%s: OK", testName);
    } else {
        printf("%s: FAILED", testName);
    }
}

void TEST_ASSERT_TMP_EQUAL(const char* testName, float opcao1, float opcao2) {
    if (opcao1 == opcao2) {
        printf("%s: OK", testName);
    } else {
        printf("%s: FAILED", testName);
    }
}

void TEST_ASSERT_TMP_NOT_EQUAL(const char* testName, float opcao1, float opcao2) {
    if (opcao1 == opcao2) {
        printf("%s: OK", testName);
    } else {
        printf("%s: FAILED", testName);
    }
}

// end: assert functions
// begin: uart test functions

// Classe de equivalência: Valor float positivo
void uart_tx_1(void) {
	Telegram tmpTelegram = {0};
	Erro erro = criarStruct(&tmpTelegram, 4, 25.3);
	TEST_ASSERT_EQUAL(ERRO_OK, erro);
}

// Classe de equivalência: Valor float zero
void uart_tx_2(void) {
	Telegram tmpTelegram = {0};
	Erro erro = criarStruct(&tmpTelegram, 4, 0);
	TEST_ASSERT_EQUAL(ERRO_OK, erro);
}

// Classe de equivalência: Valor float negativo
void uart_tx_3(void) {
	Telegram tmpTelegram = {0};
	Erro erro = criarStruct(&tmpTelegram, 4, -3.3);
	TEST_ASSERT_EQUAL(ERRO_OK, erro);
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

// end: test functions
// begin: adc test functions

// Classe de equivalência: Valor float positivo
void adc_1(void) {
    int ADC_VALUE = 1054;
    int ADC_VIN = 1675;
    float temperature = Sensor_Convert(ADC_VALUE, ADC_VIN);
    TEST_ASSERT_NOT_EQUAL(25.55, temperature);
}

// Classe de equivalência: Valor float pŕoximo de 0
void adc_2(void) {
    int ADC_VALUE = 966;
    int ADC_VIN = 1675;
    float temperature = Sensor_Convert(ADC_VALUE, ADC_VIN);
    TEST_ASSERT_NOT_EQUAL(0.13, temperature);
}

// Classe de equivalência: Valor float negativo
void adc_3(void) {
    int ADC_VALUE = 900;
    int ADC_VIN = 1675;
    float temperature = Sensor_Convert(ADC_VALUE, ADC_VIN);
    TEST_ASSERT_NOT_EQUAL(-18.49, temperature);
}

// Classe de equivalência: Valor adc zero
void adc_4(void) {
    int ADC_VALUE = 0;
    int ADC_VIN = 0;
    float temperature = Sensor_Convert(ADC_VALUE, ADC_VIN);
    TEST_ASSERT_NOT_EQUAL(NAN, temperature);
}

// Classe de equivalência: Valor adc muito alto
void adc_5(void) {
    int ADC_VALUE = 70000;
    int ADC_VIN = 70000;
    float temperature = Sensor_Convert(ADC_VALUE, ADC_VIN);
    TEST_ASSERT_NOT_EQUAL(205.05, temperature);
}

// ebd: adc test functions
void begin_tests(void) {
	TEST_MESSAGE("BEGIN OF TESTS EXECUTION");

	UNITY_BEGIN();
    // adc
    adc_1();
    adc_2();
    adc_3();
    adc_4();
    adc_5();
	// uart
    uart_tx_1();
    uart_tx_2();
    uart_tx_3();
    uart_tx_4();
    uart_tx_5();
    UNITY_END();
    TEST_MESSAGE("END OF TESTS EXECUTION");
}


// others

//
//// Função de configuração de impressão personalizada
//void custom_print_char(char c)
//{
//    test_results[results_index] = c;
//    results_index++;
//}

