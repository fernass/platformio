#include<stddef.h>
#include"driver/gpio.h"
#include"freertos/FreeRTOS.h"
#include"freertos/task.h"

#define GPIO_LED 2
#define BITMASK_LED (1ULL<<GPIO_LED)
#define GPIO_BTN 5
#define BITMASK_BTN (1ULL<<GPIO_BTN)
#define ESP_INTERRUPT_FLAG 0


void app_main() {}