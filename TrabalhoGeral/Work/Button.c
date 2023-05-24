#include "Button.h"

EventGroupHandle_t ButtonEventHandle = NULL;
EventBits_t eventBits;
const TickType_t xTicksToWait = 100 / portTICK_PERIOD_MS;

// Inicialização do grupo de eventos
void Button_Init() {
    ButtonEventHandle = xEventGroupCreate();
}

// Função que agurda por evento de botão pressionado
int Button_Wait() {
    // Aguarda pelo evento de botão pressionado
    eventBits = xEventGroupWaitBits(
            ButtonEventHandle,      // Event group
            BUTTON_BIT,             // Bit que deve ser esperado
            pdTRUE,                 // Reset automático
            pdTRUE,                 // Aguarda por todos os bit set
            portMAX_DELAY );        // Aguarda indefinidamente

    return (eventBits & BUTTON_BIT) != 0;
}

// Função para sinalizar evento de botão pressionado
void Button_Pressed() {
    xEventGroupSetBitsFromISR(ButtonEventHandle, BUTTON_BIT, pdFALSE);
}
