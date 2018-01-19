#include "mgos.h"

int pinSensor;
int pinLed;
int pullFrequenceMs;

void updateMotionStatus(bool);


static void timer_cb(void *arg) {
    //LOG(LL_INFO, ("XXXXX"));
    printf("Lese auf Pin: %d\n", pinSensor);

    bool result = mgos_gpio_read(pinSensor);
    updateMotionStatus(result);

  (void) arg;
}


/* method handling movement changes */
void updateMotionStatus(bool motionDetected) {

    int currentTime = time(NULL);

    printf("Uhrzeit: %d\n", currentTime);

    if (motionDetected == true) {
        mgos_gpio_write(pinLed, 1);
    } else {
        mgos_gpio_write(pinLed, 0);
    }

       printf("Ergebnis: %d\n", motionDetected);
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




