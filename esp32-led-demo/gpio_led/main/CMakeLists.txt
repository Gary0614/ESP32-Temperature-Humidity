idf_component_register(SRCS "blink_example_main.c"
                       INCLUDE_DIRS "."
                       REQUIRES led uart_comm mqtt_client wifi_mgr mqtt nvs_flash esp_wifi esp_event 
                       )
