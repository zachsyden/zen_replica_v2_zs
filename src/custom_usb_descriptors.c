#include "tusb.h"

// HID report descriptor (Xbox-style gamepad)
static uint8_t const desc_hid_report[] = {
    0x05, 0x01, 0x09, 0x05, 0xA1, 0x01, 0x85, 0x01,
    0x05, 0x09, 0x19, 0x01, 0x29, 0x10, 0x15, 0x00,
    0x25, 0x01, 0x95, 0x10, 0x75, 0x01, 0x81, 0x02,
    0x05, 0x01, 0x09, 0x39, 0x15, 0x00, 0x25, 0x07,
    0x35, 0x00, 0x46, 0x3B, 0x01, 0x65, 0x14, 0x75,
    0x04, 0x95, 0x01, 0x81, 0x42, 0x75, 0x04, 0x95,
    0x01, 0x81, 0x03, 0x09, 0x30, 0x09, 0x31, 0x15,
    0x81, 0x25, 0x7F, 0x75, 0x08, 0x95, 0x02, 0x81,
    0x02, 0xC0
};

// Device descriptor
static tusb_desc_device_t const desc_device = {
    .bLength            = sizeof(tusb_desc_device_t),
    .bDescriptorType    = TUSB_DESC_DEVICE,
    .bcdUSB             = 0x0200,
    .bDeviceClass       = 0x00,
    .bDeviceSubClass    = 0x00,
    .bDeviceProtocol    = 0x00,
    .bMaxPacketSize0    = CFG_TUD_ENDPOINT0_SIZE,
    .idVendor           = 0x2E8A,
    .idProduct          = 0x000C,
    .bcdDevice          = 0x0100,
    .iManufacturer      = 0x01,
    .iProduct           = 0x02,
    .iSerialNumber      = 0x03,
    .bNumConfigurations = 0x01
};

uint8_t const * tud_descriptor_device_cb(void) {
    return (uint8_t const *) &desc_device;
}

uint8_t const * tud_hid_descriptor_report_cb(uint8_t itf) {
    return desc_hid_report;
}

uint8_t const * tud_descriptor_configuration_cb(uint8_t index) {
    (void) index;
    // Return NULL → TinyUSB uses a default composite config (CDC + HID)
    return NULL;
}

uint16_t const * tud_descriptor_string_cb(uint8_t index, uint16_t langid) {
    (void) langid;
    static uint16_t lang_id[] = { 0x0409 }; // US English
    if (index == 0) return lang_id;
    return NULL; // Use defaults for other strings
}