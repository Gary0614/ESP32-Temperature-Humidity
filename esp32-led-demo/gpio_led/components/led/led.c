#include "led.h"



void led_init(led_t *led)
{
    gpio_config_t io_conf = {
        .pin_bit_mask   = (1ULL << led->pin),
        .mode           = GPIO_MODE_OUTPUT,
        .pull_up_en     = GPIO_PULLUP_DISABLE,
        .pull_down_en   = GPIO_PULLDOWN_DISABLE,
        .intr_type      = GPIO_INTR_DISABLE
    };

    gpio_config(&io_conf);
    led->state = 0;
    led_off(led);
}

void led_on(led_t *led)
{
    led->state = 1;
    gpio_set_level(led->pin, led->active_level);
}


void led_off(led_t *led)
{
    led->state = 0;
    gpio_set_level(led->pin, !led->active_level);
}

void led_toggle(led_t *led)
{
    if(led->state)
    {
        led_off(led);
        led->state = 0;
    }
    else
    {
        led_on(led);
        led->state = 1;
    }
}

void led_toggle_task(void *param)
{
    led_t *led = (led_t *)param;

    while(1)
    {
        led_toggle(led);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void led_start_task(led_t *led)
{
    xTaskCreate(
        led_toggle_task,
        "led_toggle_task",
        2048,
        led,
        5,
        NULL
    );
}