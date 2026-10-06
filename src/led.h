#pragma once

// Key colors (hue value: 0..191)
#define NEO_RED 0
#define NEO_YEL 32
#define NEO_GREEN 64
#define NEO_CYAN 96
#define NEO_BLUE 128
#define NEO_MAG 160
#define NEO_WHITE 191
#define NEO_BRIGHT_KEYS 2

enum led_keyboard_mode_t
{
  LED_LOOP,
  LED_FIX,
  LED_BLINK
};

// change led mode
void led_set_mode(enum led_keyboard_mode_t mode);

// set led color in FIX mode
void led_set_color_hue(uint8_t led0, uint8_t led1, uint8_t led2);

// update led task
void led_update();

// if in loop mode, change color to pressed key
void led_presskey(int key);

// fixed color for current layer
void led_set_layer(uint8_t hue);
