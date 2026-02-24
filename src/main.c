#include <stdio.h>
#include "pico/stdlib.h"

int main() {
    stdio_init_all();  // Enables serial over debugger UART
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    while (true) {
        printf("Hello from Proton RP2350! Ready for Auto Green test.\n");
        gpio_put(PICO_DEFAULT_LED_PIN, 1);
        sleep_ms(500);
        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        sleep_ms(500);
    }
}