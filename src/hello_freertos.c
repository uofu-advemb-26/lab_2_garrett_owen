/**
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/cyw43_arch.h"

#include "functions.h"


#define MAIN_TASK_PRIORITY      ( tskIDLE_PRIORITY + 1UL ) // Set main task to highest priorety
#define BLINK_TASK_PRIORITY     ( tskIDLE_PRIORITY + 2UL ) // Set blink task to have less priorety
#define MAIN_TASK_STACK_SIZE configMINIMAL_STACK_SIZE
#define BLINK_TASK_STACK_SIZE configMINIMAL_STACK_SIZE

int count = 0;
bool on = false;

/**
 * Blinks the LED 10 times at 1 Hz, then delay for 500 ms
 * 
 * @param unused
 */
void blink_task(__unused void *params) {

    // Halt code execution if the cyw43 initialization fails
    hard_assert(cyw43_arch_init() == PICO_OK);

    while (true) {
        

        toggle_led(&count, &on);

        // Set LED value
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, on);


        // 500 ms delay
        vTaskDelay(500);
    
    }
}

void main_task(__unused void *params) {

    xTaskCreate(blink_task, "BlinkThread",
                BLINK_TASK_STACK_SIZE, NULL, BLINK_TASK_PRIORITY, NULL);
    char c;

    // Read a character
    while(c = getchar()) {

        putchar(switch_capitalization(c));

    }
}

int main( void )
{
    stdio_init_all();
    const char *rtos_name;
    rtos_name = "FreeRTOS";
    TaskHandle_t task;

    // Create main task
    xTaskCreate(main_task, "MainThread",
                MAIN_TASK_STACK_SIZE, NULL, MAIN_TASK_PRIORITY, &task);
    
    // Start the scheduler
    vTaskStartScheduler();
    return 0;
}
