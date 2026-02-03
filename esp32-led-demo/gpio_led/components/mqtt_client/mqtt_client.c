#include "mqtt5_client.h"

#include "esp_log.h"
#include "mqtt_client.h"

static esp_mqtt_client_handle_t client;
static const char *TAG = "mqtt";

void mqtt_start(void)
{
    esp_mqtt_client_config_t cfg = {
        .broker.address.uri = "mqtt://broker.hivemq.com",
    };

    client = esp_mqtt_client_init(&cfg);
    esp_mqtt_client_start(client);
}

void mqtt_publish_sht31(int temp_x100, int humi_x100)
{
    char payload[64];

    snprintf(payload, sizeof(payload),
             "{\"temp\":%d.%d,\"humi\":%d.%d}",
             temp_x100 / 100, temp_x100 % 100, humi_x100 / 100, humi_x100 % 100);

    esp_mqtt_client_publish(
        client,
        "stm32/sht31/data",
        payload,
        0,
        1,
        0
    );

    ESP_LOGI(TAG, "publish: %s", payload);
}
