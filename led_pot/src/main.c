#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "driver/ledc.h"

#define GPIO_LEDC 2
#define SAMPLING 32
static const adc1_channel_t adc_channel = ADC_CHANNEL_6;
static ledc_channel_config_t ledc_channel;

static void init_hw(void);

void app_main() {
    init_hw();

    while (1){
        uint32_t adc_val = 0;
        for(int i=0; i<SAMPLING; i++){
            adc_val += adc1_get_raw(adc_channel);
        }
        adc_val /= SAMPLING;
        ledc_set_duty(ledc_channel.speed_mode, ledc_channel.channel, adc_val);
        ledc_update_duty(ledc_channel.speed_mode, ledc_channel.channel);

        vTaskDelay(500/portTICK_RATE_MS);

    }
}


static void init_hw(void){
    /* in order to read a pwm signal: use one of the two adcs (adc1 has 8 channels 32-39)
        - here use adc1, channel_6 = GPIO34
        - define approximation accuracy, here 10bit
        - define attenuation, here ADC_ATTEN_DB_11 => maximum voltage
    */
    adc1_config_width(ADC_WIDTH_BIT_10);
    adc1_config_channel_atten(adc_channel, ADC_ATTEN_DB_11);

    /* in order to write a pwm signal, here to control the led brightness
        - use ledc api (can be used also for servos and other dc motors)
        - in order to use the ledc api
        -- configure a timer (using a ledc_config_t object)
        -- configure a channel = timer + gpio
        -- change (write) the pwm signal
    */
   ledc_timer_config_t ledc_timer = {
       .duty_resolution = LEDC_TIMER_10_BIT, 
       .freq_hz = 1000,
       .speed_mode = LEDC_HIGH_SPEED_MODE,
       .timer_num = LEDC_TIMER_0,
       .clk_cfg = LEDC_AUTO_CLK,
   };
   ledc_timer_config(&ledc_timer);
   
   ledc_channel.channel = LEDC_CHANNEL_0;
   ledc_channel.duty = 0;
   ledc_channel.gpio_num = GPIO_LEDC;
   ledc_channel.speed_mode = LEDC_HIGH_SPEED_MODE;
   ledc_channel.hpoint = 0;
   ledc_channel.timer_sel = LEDC_TIMER_0;
   
   ledc_channel_config(&ledc_channel);



}