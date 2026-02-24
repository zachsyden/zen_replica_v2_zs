#include <stdio.h>
#include "pico/stdlib.h"
#include "tusb.h"

#define LED_PIN 25

void hid_gamepad_task(void) {
    static uint32_t last = 0;
    uint32_t now = time_us_32();

    if (tud_mounted() && tud_hid_ready()) {  // correct, no _n
        if (now - last >= 3000000UL) {
            uint8_t report[4] = {0x01, 0x00, 0x00, 0x00};
            tud_hid_report(1, report, sizeof(report));  // correct, no _n
            sleep_ms(80);
            report[0] = 0x00;
            tud_hid_report(1, report, sizeof(report));
            last = now;
            printf("A pressed test\n");
        }
    }
}

int main() {
    stdio_init_all();
    tusb_init();

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    for (int i = 0; i < 4; i++) {
        gpio_put(LED_PIN, 1); sleep_ms(200);
        gpio_put(LED_PIN, 0); sleep_ms(200);
    }

    printf("Started\n");

    while (true) {
        tud_task();
        hid_gamepad_task();

        static uint32_t blink = 0;
        if (time_us_32() - blink > 1000000) {
            gpio_put(LED_PIN, !gpio_get(LED_PIN));
            blink = time_us_32();
        }
    }
}