#include <stdio.h>
#include "pico/stdlib.h"

#include "FreeRTOS.h"

#include "task.h"

void vBlinkTask()
{
    vTaskDelay(1000);
    while (true)
    {
        gpio_put(PICO_DEFAULT_LED_PIN, 1);
        vTaskDelay(250);
        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        vTaskDelay(250);
        printf("Current TASK1 custom count %d\n", getTaskCustomCount());
    }
}

void vBlinkTask2()
{
    while (true)
    {
        printf("Current TASK2 custom count %d\n", getTaskCustomCount());
        // busy wait for 100 ms
        absolute_time_t timediff = make_timeout_time_ms(100);
        while (!time_reached(timediff))
            ;
    }
}
void vBlinkTask3()
{
    while (true)
    {
        printf("Current TASK3 custom count %d\n ", getTaskCustomCount());
        // busy wait for 250 ms
        absolute_time_t timediff = make_timeout_time_ms(250);
        while (!time_reached(timediff))
            ;
    }
}
void main()
{
    stdio_init_all();
    gpio_init(PICO_DEFAULT_LED_PIN);

    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    // task with higher priority, this will pre-empt the other two tasks even though they do not yield
    xTaskCreate(vBlinkTask, "Blink Task", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    // blocking tasks with lower priority
    xTaskCreate(vBlinkTask2, "Blink Task 2", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(vBlinkTask3, "Blink Task 3", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    vTaskStartScheduler();
}
