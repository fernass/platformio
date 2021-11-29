#include<stddef.h>
#include"driver/gpio.h"
#include"freertos/FreeRTOS.h"
#include"freertos/task.h"

#define GPIO_LED 2
#define BITMASK_LED (1ULL<<GPIO_LED)
#define GPIO_BTN 5
#define BITMASK_BTN (1ULL<<GPIO_BTN)
#define ESP_INTR_FLAG_DEFAULT 0

static void btn_handler(void* args);
static void init_hw(void);


void app_main() {
//    printf("Main\n");
    init_hw();

    vTaskSuspend(NULL);
}

//################################################
void init_hw(void){
//    printf("enter hw_init\n");
    // configure the LED (output) gpio
    gpio_config_t io_conf;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pin_bit_mask = BITMASK_LED;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;

    gpio_config(&io_conf);

    // configure the button (input) gpio
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = BITMASK_BTN;
    io_conf.intr_type = GPIO_PIN_INTR_ANYEDGE;
    //io_conf.intr_type = GPIO_INTR_NEGEDGE;
    io_conf.pull_up_en = 1;

    gpio_config(&io_conf);

    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
    gpio_isr_handler_add(GPIO_BTN, btn_handler, NULL);

//    printf("exit hw_init\n");

}

//###########################
static bool led_state = false;
static TickType_t next = 0;

static void IRAM_ATTR btn_handler(void* arg){
    TickType_t now = xTaskGetTickCountFromISR();

    if(now > next){
        led_state = !led_state;
        gpio_set_level(GPIO_LED, led_state);
        next = now + 500 / portTICK_PERIOD_MS;
    }
}
