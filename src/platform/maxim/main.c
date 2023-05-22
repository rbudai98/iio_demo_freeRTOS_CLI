/***************************************************************************/ 
/**
 *   @file   main.c
 *   @brief  Main file for Maxim platform of iio_demo project.
 *   @author Robert Budai (robert.budai@analog.com)
 ********************************************************************************
* Copyright 2022(c) Analog Devices, Inc.
*
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*  - Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*  - Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in
*    the documentation and/or other materials provided with the
*    distribution.
*  - Neither the name of Analog Devices, Inc. nor the names of its
*    contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*  - The use of this software may or may not infringe the patent rights
*    of one or more patent holders.  This license does not release you
*    from the requirement that you obtain separate licenses from these
*    patent holders to use this software.
*  - Use of the software either in source or binary form, must be run
*    on or directly connected to an Analog Devices Inc. component.
*
* THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES "AS IS" AND ANY EXPRESS OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, NON-INFRINGEMENT,
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL ANALOG DEVICES BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, INTELLECTUAL PROPERTY RIGHTS, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/
/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/
#include "platform_includes.h"
#include "common_data.h"

#ifdef IIO_EXAMPLE
#include "iio_example.h"
#endif

#ifdef IIO_TRIGGER_EXAMPLE
#include "iio_trigger_example.h"
#endif

// FreeRTOS
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "portmacro.h"
#include "task.h"
#include "semphr.h"
#include "wut.h"
#include "uart.h"
#include "lp.h"
#include "no_os_delay.h"

/* Mutual exclusion (mutex) semaphores */
SemaphoreHandle_t xUARTmutex;
SemaphoreHandle_t xGPIOmutex;

/* Enables/disables tick-less mode */
unsigned int disable_tickless = 1;

/* Stringification macros */
#define STRING(x) STRING_(x)
#define STRING_(x) #x

/* Console ISR selection */
#if (CONSOLE_UART == 0)
#define UARTx_IRQHandler UART0_IRQHandler
#define UARTx_IRQn UART0_IRQn
mxc_gpio_cfg_t uart_cts = {MXC_GPIO0, MXC_GPIO_PIN_2, MXC_GPIO_FUNC_IN, MXC_GPIO_PAD_WEAK_PULL_UP,
                           MXC_GPIO_VSSEL_VDDIOH};
mxc_gpio_cfg_t uart_rts = {MXC_GPIO0, MXC_GPIO_PIN_3, MXC_GPIO_FUNC_OUT, MXC_GPIO_PAD_NONE,
                           MXC_GPIO_VSSEL_VDDIOH};
#else
#error "Please update ISR macro for UART CONSOLE_UART"
#endif

#define MXC_GPIO_PORT_OUT MXC_GPIO2
#define MXC_GPIO_PIN_OUT MXC_GPIO_PIN_0

/**
 * @brief iiod example task
*/

void iiodTask(void *pvParameters)
{
    // int ret = iio_example_main();
}

/**
 * @brief LED blinking task for multithreading example
*/

void blinkingTask(void *pvParameters)
{
    /* Setup output pin. */
    mxc_gpio_cfg_t gpio_out;
    gpio_out.port = MXC_GPIO2;
    gpio_out.mask = MXC_GPIO_PIN_OUT;
    gpio_out.pad = MXC_GPIO_PAD_NONE;
    gpio_out.func = MXC_GPIO_FUNC_OUT;
    MXC_GPIO_Config(&gpio_out);

    bool LED_ON = true;
    while (1)
    {
        if (!LED_ON && (xSemaphoreTake(xGPIOmutex, portMAX_DELAY) == pdTRUE))        
            {
                MXC_GPIO_OutSet(gpio_out.port, ((uint32_t)(1UL << 0)));
                xSemaphoreGive(xGPIOmutex);    
                LED_ON=true;
                vTaskDelay(0.2 * configTICK_RATE_HZ);
            }
        if (LED_ON && (xSemaphoreTake(xGPIOmutex, portMAX_DELAY) == pdTRUE))        
            {
                MXC_GPIO_OutClr(gpio_out.port, ((uint32_t)(1UL << 0)));
                xSemaphoreGive(xGPIOmutex);
                LED_ON=false;
                vTaskDelay(0.2 * configTICK_RATE_HZ);
            }
    }
}

/**
 * @brief Creating iio example with blinking led task
 * 
*/

int create_tasks(void)
{
    //Initial wait time
    // for (int i = 0; i < 0x00FFFF; i++){}



    xUARTmutex = xSemaphoreCreateMutex();
    xGPIOmutex = xSemaphoreCreateMutex();

    // xSemaphoreGive(xUARTmutex);
    // xSemaphoreGive(xGPIOmutex);

    if (xGPIOmutex == NULL)
    {
        printf("Mutex failed to create a mutex.\n");
    }
    else
    {
        /* Configure task */
        if ((xTaskCreate(iiodTask, (const char *)"iiodTask", configIIO_APP_STACK_SIZE, NULL,
                         tskIDLE_PRIORITY + 1, NULL) != pdPASS)) {
            printf("xTaskCreate() failed to create a task.\n");
        }
        else if ((xTaskCreate(blinkingTask, (const char *)"blinkingTask", configMINIMAL_STACK_SIZE, NULL,
                              tskIDLE_PRIORITY + 2, NULL) != pdPASS))
        {
            printf("xTaskCreate() failed to create a task.\n");
        }
        else
        {
            /* Start scheduler */
            printf("Starting scheduler.\n");
            vTaskStartScheduler();
        }
    }
    while (1)
    {
        __NOP();
    }
    return -1;
}

/***************************************************************************/ 
/**
 * @brief Main function execution for Maxim platform.
 *
 * @return ret - Result of the enabled examples execution.
 *******************************************************************************/
int main()
{
    int ret = -1;

#if TARGET_NUM == 32660
#error TARGET MAX32660 not supported
#endif

#ifdef IIO_EXAMPLE
    create_tasks();
#endif

#ifdef IIO_TRIGGER_EXAMPLE
#error Software trigger is not supported over UART.
#endif

#ifdef IIO_TIMER_TRIGGER_EXAMPLE
#error No rtos implementation for timer trigger.
#endif

#if (IIO_EXAMPLE + IIO_TRIGGER_EXAMPLE + IIO_TIMER_TRIGGER_EXAMPLE == 0)
#error At least one example has to be selected using y value in Makefile.
#elif (IIO_EXAMPLE + IIO_TRIGGER_EXAMPLE + IIO_TIMER_TRIGGER_EXAMPLE > 1)
#error Selected example projects cannot be enabled at the same time. \
Please enable only one example and re-build the project.
#endif

    return ret;
}
