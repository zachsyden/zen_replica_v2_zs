#include <stdio.h>
#include "pico/stdlib.h"
#include "tusb.h"           // TinyUSB header

int main() {
    stdio_init_all();
    tusb_init();            // Initialize TinyUSB device stack

    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    printf("Proton RP2350 started - TinyUSB init done. LED on GPIO %d\n", PICO_DEFAULT_LED_PIN);

    while (true) {
        tud_task();         // MUST call this regularly for USB to work

        // Your blink
        gpio_put(PICO_DEFAULT_LED_PIN, 1);
        sleep_ms(500);
        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        sleep_ms(500);

        // Optional: print connection status every few seconds
        static uint32_t last_print = 0;
        if (time_us_32() - last_print > 5000000) {  // every 5s
            if (tud_mounted()) {
                printf("USB mounted! Host sees us.\n");
            } else {
                printf("Waiting for USB host...\n");
            }
            last_print = time_us_32();
        }
    }
    return 0;
}