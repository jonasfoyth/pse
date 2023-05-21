/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Uart.h"
#include "Sensor.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
float temperature = 0;

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for periodic100hz */
osThreadId_t periodic100hzHandle;
const osThreadAttr_t periodic100hz_attributes = {
  .name = "periodic100hz",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for buttonHandler */
osThreadId_t buttonHandlerHandle;
const osThreadAttr_t buttonHandler_attributes = {
  .name = "buttonHandler",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for asynchronousR */
osThreadId_t asynchronousRHandle;
const osThreadAttr_t asynchronousR_attributes = {
  .name = "asynchronousR",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for asynchronousL */
osThreadId_t asynchronousLHandle;
const osThreadAttr_t asynchronousL_attributes = {
  .name = "asynchronousL",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void periodic_task(void *argument);
void button_task(void *argument);
void asynchronousR_task(void *argument);
void asynchronousL_task(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName);
void vApplicationMallocFailedHook(void);

/* USER CODE BEGIN 4 */
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName)
{
   /* Run time stack overflow checking is performed if
   configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2. This hook function is
   called if a stack overflow is detected. */
	__disable_irq();
	while(1);
}
/* USER CODE END 4 */

/* USER CODE BEGIN 5 */
void vApplicationMallocFailedHook(void)
{
   /* vApplicationMallocFailedHook() will only be called if
   configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h. It is a hook
   function that will get called if a call to pvPortMalloc() fails.
   pvPortMalloc() is called internally by the kernel whenever a task, queue,
   timer or semaphore is created. It is also called by various parts of the
   demo application. If heap_1.c or heap_2.c are used, then the size of the
   heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
   FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
   to query the size of free heap space that remains (although it does not
   provide information on how the remaining heap might be fragmented). */
	__disable_irq();
	while(1);
}
/* USER CODE END 5 */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of periodic100hz */
  periodic100hzHandle = osThreadNew(periodic_task, NULL, &periodic100hz_attributes);

  /* creation of buttonHandler */
  buttonHandlerHandle = osThreadNew(button_task, NULL, &buttonHandler_attributes);

  /* creation of asynchronousR */
  asynchronousRHandle = osThreadNew(asynchronousR_task, NULL, &asynchronousR_attributes);

  /* creation of asynchronousL */
  asynchronousLHandle = osThreadNew(asynchronousL_task, NULL, &asynchronousL_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */

	while (1) {
		vTaskDelay(10000);
	}
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_periodic_task */
/**
* @brief Function implementing the periodic100hz thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_periodic_task */
void periodic_task(void *argument)
{
  /* USER CODE BEGIN periodic_task */
  float temperature = 0;

	Telegram tmpTelegram = {0};
	TickType_t xLastWakeTime;
	const TickType_t xPeriod = 10; // In ticks

	xLastWakeTime = xTaskGetTickCount();
	
		
	while(1) {
		//Espera os 10ms (100hz)
		vTaskDelayUntil( &xLastWakeTime, xPeriod );

    // Leitura do valor de temperatura
		Sensor_Read(&temperature);

    // Preenche o telegrama
    tmpTelegram.id = 4;
    tmpTelegram.data.temperature = temperature;	// TODO KELVIN
    //		tmpTelegram.data.dontCare1 = 0;	// Não precisa perder tempo com esse
    //		tmpTelegram.data.dontCare2 = 0; // Nem com esse

		// Envia o valor pra direita somente, pois é o sentido do display.
		Uart_startTx(&uartRight, &tmpTelegram);
	}
  /* USER CODE END periodic_task */
}

/* USER CODE BEGIN Header_button_task */
/**
* @brief Function implementing the buttonHandler thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_button_task */
void button_task(void *argument)
{
  /* USER CODE BEGIN button_task */
	Telegram tmpTelegram = {0};

  float temperature = 0;

	while(1) {
		//Espera até o botão ser apertado


		// Lê o adc
    Sensor_Read(&temperature);

		// Preenche o telegrama
		tmpTelegram.id = 4;
		tmpTelegram.data.temperature = temperature;
    //tmpTelegram.data.dontCare1 = 0;	// Não precisa perder tempo com esse
    //tmpTelegram.data.dontCare2 = 0; // Nem com esse

		// Envia o valor pra direita somente, pois é o sentido do display.
		Uart_startTx(&uartRight, &tmpTelegram);
	}
  /* USER CODE END button_task */
}

/* USER CODE BEGIN Header_asynchronousR_task */
/**
* @brief Function implementing the asynchronousR thread.
* 			Responsável por tratar todos os telegramas recebidos da uart da direita,
* 			que está ligada ao EV (display)
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_asynchronousR_task */
void asynchronousR_task(void *argument)
{
  /* USER CODE BEGIN asynchronousR_task */
	float temperature = 0;

  Telegram tmpTelegram = {0};
	Uart_init(&uartRight);

  
	while(1) {
		//Espera até receber um telegrama válido na uart
		Uart_waitEvent(&uartRight, UartEvent_rxComplete, portMAX_DELAY);

		// Assim que o evento for recebido, verifica se é um broadcast
		// (tem que ser broadcast, se não alguém está fazendo coisa errada, mas é bom verificar)

		if (uartLeft.rxBuffer.id != 255) {
			// Alguém fez algo errado, apenas ignora a mensagem
			continue;
		}

		// Se o ID é de requisição do EV (display), então: (da pra mudar a ordem, deixei assim pq é melhor pra nós)
		// 1º Faz a leitura dos dados e retorna para o valor para o EV (que está em alguma posição na direita).
		// 2º Rapassa a requisição para os dispositivos à esquerda

		// Lê o adc
    Sensor_Read(&temperature);

		// Preenche o telegrama
		tmpTelegram.id = 4;
		tmpTelegram.data.temperature = temperature;
    //tmpTelegram.data.dontCare1 = 0;	// Não precisa perder tempo com esse
    //tmpTelegram.data.dontCare2 = 0; // Nem com esse

		// Devolve o valor conforme requisição
		Uart_startTx(&uartRight, &tmpTelegram);

		// Repassa o telegram para a esquerda
		tmpTelegram.id = 255;	// Só precisa atualizar o id, o resto é dont care
		Uart_startTx(&uartLeft, &tmpTelegram);
	}
  /* USER CODE END asynchronousR_task */
}

/* USER CODE BEGIN Header_asynchronousL_task */
/**
* @brief Function implementing the asynchronousL thread.
* 			Responsável por tratar todos os telegramas recebidos da uart da esquerda,
* 			que não está ligada ao EV (display)
*
* 			Essa task poderia estar totalmente implementada n
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_asynchronousL_task */
void asynchronousL_task(void *argument)
{
  /* USER CODE BEGIN asynchronousL_task */
	Uart_init(&uartLeft);

	while(1) {
		//Espera até receber um telegrama válido na uart
		Uart_waitEvent(&uartLeft, UartEvent_rxComplete, portMAX_DELAY);

		// Assim que o evento for recebido, repassa o que foi recebido na uart da esquerda para
		// a uart da direita.
		// Só precisamos repassar, pois nunca vai ter uma requisição vindo da esquerda.
		Uart_startTx(&uartRight, &uartLeft.rxBuffer);
    }
  /* USER CODE END asynchronousL_task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

