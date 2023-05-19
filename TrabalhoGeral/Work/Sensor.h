/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SENSOR_CLASS_H__
#define __SENSOR_CLASS_H__

#include <stdint.h>

#define TEMP_V_AT_25 	0.76 	// Tensão em 25°C
#define TEMP_AVG_SLOPE 	2.5 	// mV/°C
#define TEMP_ADC_FULL_RANGE 	4096	// Fundo de escala
#define TEMP_ADC_REF_V	3.3		// Tensão de referência

// Armazena as medições raw vindas do ADC1
extern uint16_t adc_reads[2];

float get_temperature (uint16_t adc_temp, uint16_t adc_vin);

#endif /* __SENSOR_CLASS_H__ */
