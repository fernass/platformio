#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "dht.h"

#define GPIO_DH11 17
#define GPIO_BUZ 18
#define BITMASK_BUZ (1ULL << GPIO_BUZ)

static int16_t temperature;
static int16_t humidity;

void init_hw(void);

void app_main() {
    init_hw();

    while(1){
        if(dht_read_data(DHT_TYPE_DHT11, (gpio_num_t) GPIO_DH11, &humidity, &temperature)==ESP_OK){
            printf("Humidity: %d%% Temperature: %dC\n", humidity/10, temperature/10);
            
        }
    }

}



void init_hw(void){
    gpio_config_t io_config ={
        .mode = GPIO_MODE_INPUT,
        .intr_type = GPIO_INTR_DISABLE,
        .pin_bit_mask = BITMASK_BUZ,
        .pull_down_en = 0,
        .pull_up_en = 0
    };

    gpio_config(&io_config);

}