#include <stdio.h>
#include "freertos/FreeRTOS.h"
// #include "driver/ledc.h"
#include "iot_servo.h"


/*
using ledc driver in 3 steps:
1) timer config
2) channel config
3) change pwm signal
*/

void init_hw(){
    ledc_timer_config_t timer_config = {
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .timer_num = LEDC_TIMER_0,
        .duty_resolution = 
    };
}

void app_main() {}