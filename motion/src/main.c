#include "mgos.h"

/* pin layout */
int pinSensor;
int pinLed;

/* the global cycle frequence */
int pullFrequenceMs;

/* the second when the last movement was detected */
int timeOfLastMovement = -10;

void processSensorSignal(bool);


static void timer_cb(void *arg) {
    //LOG(LL_INFO, ("XXXXX"));
    //printf("Lese auf Pin: %d\n", pinSensor);

    bool result = mgos_gpio_read(pinSensor);
    processSensorSignal(result);

  (void) arg;
}


/* method handling movement changes */
void processSensorSignal(bool motionDetected) {

    int currentTime = time(NULL);

    printf("---------------------------------\n");
    printf("Uhrzeit: %d\n", currentTime);
    printf("Last Movement: %d\n", timeOfLastMovement);
    printf("Movement: %d\n", motionDetected);

    if(currentTime >= (timeOfLastMovement + 0)) {

        if (motionDetected == true) {
            timeOfLastMovement = currentTime;
            printf("Result: SWITCH ON\n\n");
            mgos_gpio_write(pinLed, 1);
        } else {
        printf("Result: SWITCH OFF\n\n");
        mgos_gpio_write(pinLed, 0);
        }
    } else {
    printf("Result: NOTHING\n\n");
    }
}


/* initialization method */
enum mgos_app_init_result mgos_app_init(void) {

    pinSensor =  mgos_sys_config_get_app_sensor();
    pinLed = mgos_sys_config_get_app_led();
    pullFrequenceMs = mgos_sys_config_get_app_pullFrequenceMs();

    printf("Sensor Pin: %d\n", pinSensor);
    printf("LED Pin: %d\n", pinLed);
    printf("Pull Frequency: %d\n", pullFrequenceMs);

    /* prepare pins */
    mgos_gpio_set_mode(pinSensor, MGOS_GPIO_MODE_INPUT);
    mgos_gpio_set_mode(pinLed, MGOS_GPIO_MODE_OUTPUT);

    mgos_set_timer(pullFrequenceMs, true, timer_cb, NULL);

     return MGOS_APP_INIT_SUCCESS;
}




