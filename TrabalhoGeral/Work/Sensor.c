#include <Sensor.h>

// inicializa adc_values
uint16_t adc_reads[2] = {0, 0};

float get_temperature (uint16_t adc_temp, uint16_t adc_vin) {
    float temp = 0;
    float vref_in = (TEMP_ADC_FULL_RANGE * 1.21) / adc_vin;
    temp = adc_temp * vref_in / TEMP_ADC_FULL_RANGE;
    // Conversão para °C
    temp = ((temp - TEMP_V_AT_25) * 1000.0) / TEMP_AVG_SLOPE + 25.0;
    return temp;
}
