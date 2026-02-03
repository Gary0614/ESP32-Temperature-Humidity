#ifndef __LED_H
#define __LED_H

#include <stdio.h>

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

typedef struct 
{
    gpio_num_t pin;
    uint8_t active_level;  // 1 for HIGH active, 0 for LOW active
    uint8_t state;
}led_t;


void led_init(led_t *led);
void led_on(led_t *led);
void led_off(led_t *led);
void led_toggle(led_t *led);
void led_toggle_task(void *param);

void led_start_task(led_t *led);

#endif
