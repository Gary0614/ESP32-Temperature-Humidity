#include "uart_comm.h"
#include "string.h"
#include <stdio.h>

#define UART_BUF_SIZE 1024

void uart_comm_init(uart_comm_t *uart_comm)
{
    uart_config_t uart_config = {
        .baud_rate = uart_comm->baud_rate,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    uart_param_config(uart_comm->uart_num, &uart_config);
    uart_set_pin(uart_comm->uart_num, uart_comm->tx_pin, uart_comm->rx_pin, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(uart_comm->uart_num, UART_BUF_SIZE * 2, 0, 0, NULL, 0);
}

static void uart_task(void *param)
{
    uart_comm_t *uart =(uart_comm_t *)param;
    uint8_t rx_buf[128];


    // const char *msg  = "Hello from ESP32 UART!\n";    //test message
    // printf("UART task started on UART %d with baud rate %d\n", uart->uart_num, uart->baud_rate);
    while(1)
    {
        int len =uart_read_bytes(uart->uart_num, rx_buf, sizeof(rx_buf)-1, pdMS_TO_TICKS(100));
        if(len > 0)
        {
            rx_buf[len] = '\0'; // Null-terminate the received data

            // If a callback is registered, call it
            if(uart->rx_callback != NULL)
            {
                uart->rx_callback((const char *)rx_buf, len);
            }
        }
        
    }
}

void uart_comm_start_task(uart_comm_t *uart)
{
    xTaskCreate(uart_task, "uart_task", 3072, uart, 6, NULL);
}