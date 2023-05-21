#include <Sensor.h>

//SemaphoreHandle_t temperature_semaph;

// inicializa adc_values
uint16_t adc_reads[2] = {0, 0};

void Sensor_Init() {
    //temperature_semaph = xSemaphoreCreateMutex();
}


float Sensor_Convert(uint16_t adc_temp, uint16_t adc_vin) {
    float vref_in = (TEMP_ADC_FULL_RANGE * 1.21) / adc_vin;
    float temp = adc_temp * vref_in / TEMP_ADC_FULL_RANGE;

    // Conversão para °C
    temp = ((temp - TEMP_V_AT_25) * 1000.0) / TEMP_AVG_SLOPE + 25.0;
    return temp;
}


void Sensor_Read(float *temperature) {
	//if (xSemaphoreTake(temperature_semaph, pdMS_TO_TICKS(1)) == pdTRUE) {
	// Realiza a conversão copiando os valores atuais do ADC (temp e V_in)
	float temp = Sensor_Convert(adc_reads[0], adc_reads[1]);
	*temperature = temp;
	//xSemaphoreGive(temperature_semaph);

}

