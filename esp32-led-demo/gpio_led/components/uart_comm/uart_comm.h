#pragma once

#include <stdio.h>

#include "driver/uart.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

typedef void (*uart_rx_cb_t)(const char *data, int len);

typedef struct
{
    uart_port_t uart_num;
    int baud_rate;
    int tx_pin;
    int rx_pin;

    uart_rx_cb_t rx_callback; // Callback for received data
}uart_comm_t;

void uart_comm_init(uart_comm_t *uart_comm);
void uart_comm_start_task(uart_comm_t *uart);