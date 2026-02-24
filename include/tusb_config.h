#ifndef TUSB_CONFIG_H_
#define TUSB_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

// USB device mode, full speed (RP2350 supports HS, but start simple)
#define CFG_TUSB_RHPORT0_MODE       (OPT_MODE_DEVICE | OPT_MODE_FULL_SPEED)

// CDC serial (for stdio_init_all() printf over USB when main port connected)
#define CFG_TUD_CDC                 1
#define CFG_TUD_CDC_RX_BUFSIZE      64
#define CFG_TUD_CDC_TX_BUFSIZE      64

// HID (gamepad) - start disabled, we'll enable in next step
#define CFG_TUD_HID                 1

// Other required configs
#define CFG_TUSB_MEM_SECTION
#define CFG_TUSB_MEM_ALIGN          __attribute__ ((aligned(4)))

// MCU type
#define CFG_TUSB_MCU                OPT_MCU_RP2040  // Try OPT_MCU_RP2350 if issues

#ifdef __cplusplus
}
#endif

#endif /* TUSB_CONFIG_H_ */