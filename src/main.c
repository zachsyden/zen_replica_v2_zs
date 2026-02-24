#include <stdio.h>
#include "pico/stdlib.h"
#include "tusb.h"               // TinyUSB main header

// Onboard LED is GPIO 25 on Proton / Pico 2
#define LED_PIN 25

// Simple periodic HID test: press/release "A" button every ~3 seconds
void hid_gamepad_task(void)
{
    static uint32_t last_press = 0;

    if (tud_mounted() && tud_hid_ready())   // Correct: no _n
    {
        uint32_t now = time_us_32();

        if (now - last_press >= 3000000)     // 3 seconds
        {
            uint8_t report[4] = {0x01, 0x00, 0x00, 0x00};  // Button 1 (A) pressed

            tud_hid_report(1, report, sizeof(report));      // Correct: no _n

            sleep_ms(80);

            report[0] = 0x00;
            tud_hid_report(1, report, sizeof(report));

            last_press = now;
            printf("Test A button sent\n");
        }
    }
}

int main(void)
{
    stdio_init_all();               // Serial over USB (CDC)
    tusb_init();                    // Initialize TinyUSB stack

    // Initialize LED
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // Initial fast blink to confirm boot
    for (int i = 0; i < 6; i++)
    {
        gpio_put(LED_PIN, 1);
        sleep_ms(100);
        gpio_put(LED_PIN, 0);
        sleep_ms(100);
    }

    printf("Proton RP2350 started - TinyUSB init OK\n");
    printf("Waiting for USB host connection...\n");

    uint32_t last_status_print = 0;
    uint32_t last_blink = 0;

    while (true)
    {
        tud_task();                 // Must call frequently for USB to work
        hid_gamepad_task();         // Send periodic A button press for testing
        // Slow blink while waiting / running
        if (time_us_32() - last_blink > 1000000)   // 1 second toggle
        {
            gpio_put(LED_PIN, !gpio_get(LED_PIN));
            last_blink = time_us_32();
        }

        // Print USB status every 5 seconds (visible when debugger connected)
        if (time_us_32() - last_status_print > 5000000)
        {
            if (tud_mounted())
            {
                printf("USB mounted by host! HID gamepad active.\n");
                // Fast blink when connected
                for (int i = 0; i < 3; i++)
                {
                    gpio_put(LED_PIN, 1); sleep_ms(150);
                    gpio_put(LED_PIN, 0); sleep_ms(150);
                }
            }
            else
            {
                printf("Waiting for USB host...\n");
            }
            last_status_print = time_us_32();
        }

        
    }

    return 0;
}