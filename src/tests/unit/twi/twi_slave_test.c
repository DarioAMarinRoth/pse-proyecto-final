#include "twi.h"
#include "gpio.h"

int main(void) {
    gpio_input(13);
    slave_init(0);
    twi_slave_transmit(1);
    twi_slave_transmit(0);
    while (1) {
        if (gpio_pin(13,GET))
            twi_slave_transmit(1);
        else
            twi_slave_transmit(0);
    }
}
