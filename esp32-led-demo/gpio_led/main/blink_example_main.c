/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
// #include "driver/gpio.h"
// #include "esp_log.h"
// #include "led_strip.h"
// #include "sdkconfig.h"
// #include "driver/uart.h"
// #include "nvs_flash.h"

#include "wifi_mgr.h"
#include "mqtt_client.h"
#include "led.h"
#include "uart_comm.h"

static led_t led ={
    .pin = 4,
    .active_level = 1,
    .state = 0
};

static void uart_rx_handler(const char *data, int len);

static uart_comm_t uart1 = {
    .uart_num = UART_NUM_1,
    .baud_rate = 115200,
    .tx_pin = GPIO_NUM_17,
    .rx_pin = GPIO_NUM_16,
    .rx_callback = uart_rx_handler
};

static void uart_rx_handler(const char *data, int len)
{
    //处理字符串
    int temp, humi;
    if(sscanf(data, "$TEMP:%d,HUM:%d#", &temp, &humi) == 2)
    {
        mqtt_publish_sht31(temp, humi);   //上传数据到云端 
        printf("{\"Temp\": %d.%2d \"Humi\": %d.%2d\r\n", temp / 100, temp % 100, humi / 100, humi % 100);
        uart_write_bytes(uart1.uart_num, (char*)"$DATA:ACK#", strlen("$DATA:ACK#"));
    }
 
    // TODO：上传云端

}

void app_main(void)
{
    // Initialize and start LED task
    led_init(&led);
    led_start_task(&led);
    // led_start_task(&led);

    wifi_init_sta();
    mqtt_start();
    // mqtt_publish_sht31(3000, 5000);

    // Initialize and start UART communication task
    uart_comm_init(&uart1);
    uart_comm_start_task(&uart1);
        
}

