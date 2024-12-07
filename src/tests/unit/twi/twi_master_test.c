#include <stdint.h>

#include "gpio.h"
#include "twi.h"

int main(void) {
    master_init();
    uint8_t data = 0;
    gpio_output(13);
    int status;

    while (1) {
        status = twi_master_receive_byte(DEFAULT_SLA);
        data = get_received_data();
        if (data == 1) {
            gpio_pin(13, ON);
        } else {
            gpio_pin(13, OFF);
        }
    }
}
