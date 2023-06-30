#ifndef IIO_DEMO_FREE_RTOS_CONFIG
#define IIO_DEMO_FREE_RTOS_CONFIG

#include <stdint.h>

/* CMSIS keeps a global updated with current system clock in Hz */

// #define configCPU_CLOCK_HZ ((uint32_t)IPO_FREQ)
#define configCPU_CLOCK_HZ ((uint32_t)100000000)

// #define configUSE_TICKLESS_IDLE     1

#define configTICK_RATE_HZ ((portTickType)1000)
#define configRTC_TICK_RATE_HZ (32768)
#define configTOTAL_HEAP_SIZE ((size_t)(26 * 1024))
#define configMINIMAL_STACK_SIZE ((uint16_t)448)
#define configIIO_APP_STACK_SIZE ((uint16_t)1024)
// #define configSUPPORT_STATIC_ALLOCATION 1
#define configMAX_PRIORITIES 5
#define configUSE_PREEMPTION 1
#define configUSE_IDLE_HOOK 0
#define configUSE_TICK_HOOK 0
#define configUSE_CO_ROUTINES 0
#define configUSE_16_BIT_TICKS 0
#define configUSE_MUTEXES 1
// #if configUSE_16_BIT_TICKS == 0
// #define freeRTOS_WAIT_TIME 0xffffffff
// #else
// #define freeRTOS_WAIT_TIME 0xffff
// #endif
#define freeRTOS_WAIT_TIME  0
/* Run time and task stats gathering related definitions. */
#define configUSE_TRACE_FACILITY 1
#define configUSE_STATS_FORMATTING_FUNCTIONS 1

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */
#define INCLUDE_vTaskPrioritySet 0
#define INCLUDE_vTaskDelete 0
#define INCLUDE_vTaskSuspend 1
#define INCLUDE_vTaskDelayUntil 1
#define INCLUDE_uxTaskPriorityGet 0
#define INCLUDE_vTaskDelay 1
/* # of priority bits (configured in hardware) is provided by CMSIS */
// #define configPRIO_BITS __NVIC_PRIO_BITS
#define configPRIO_BITS 3
/* Priority 7, or 255 as only the top three bits are implemented.  This is the lowest priority. */
#define configKERNEL_INTERRUPT_PRIORITY ((unsigned char)7 << (8 - configPRIO_BITS))
/* Priority 5, or 160 as only the top three bits are implemented. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY ((unsigned char)5 << (8 - configPRIO_BITS))
/* Alias the default handler names to match CMSIS weak symbols */
#define vPortSVCHandler SVC_Handler
#define xPortPendSVHandler PendSV_Handler
#define xPortSysTickHandler SysTick_Handler
#ifdef configUSE_TICKLESS_IDLE
/* Provide routines for tickless idle pre- and post- processing */
void vPreSleepProcessing(uint32_t *);
void vPostSleepProcessing(uint32_t);
#define configPRE_SLEEP_PROCESSING(idletime) vPreSleepProcessing(&idletime);
#define configPOST_SLEEP_PROCESSING(idletime) vPostSleepProcessing(idletime);
#endif
/* FreeRTOS+CLI requires this size to be defined, but we do not use it */
#define configCOMMAND_INT_MAX_OUTPUT_SIZE 1
#define INCLUDE_xTaskGetIdleTaskHandle                          1
#define INCLUDE_pxTaskGetStackStart                             1

// #include "SEGGER_SYSVIEW_FreeRTOS.h"

#endif // IIO_DEMO_FREE_RTOS_CONFIG
