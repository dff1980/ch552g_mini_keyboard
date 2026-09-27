#include <Arduino.h>
#include "neo/neo.h"
#include "led.h"
#include "auto_mode.h"
#include "userUsbHidKeyboardMouse/USBHIDKeyboardMouse.h"

static enum led_keyboard_mode_t led_mode_s = LED_LOOP;

static uint8_t color_hue_s[3] =
{
  NEO_RED,
  NEO_RED,
  NEO_RED
};

static int current_key_s = -1;
static bool layer_led_mode_s = false;

static uint8_t breath_s = 0;
static bool breath_down_s = false;
static unsigned long breath_last_ms_s = 0;

#define BREATH_STEP_MS 25
#define BREATH_MAX 40

void led_set_color_hue(uint8_t led0, uint8_t led1, uint8_t led2)
{
  color_hue_s[0] = led0;
  color_hue_s[1] = led1;
  color_hue_s[2] = led2;
}

void led_set_mode(enum led_keyboard_mode_t mode)
{
  led_mode_s = mode;
  layer_led_mode_s = false;

  if (mode == LED_LOOP)
  {
    color_hue_s[0] = NEO_RED;
    color_hue_s[1] = NEO_YEL;
    color_hue_s[2] = NEO_GREEN;
  }
}

void led_set_layer(uint8_t hue)
{
  led_mode_s = LED_FIX;
  layer_led_mode_s = true;

  color_hue_s[0] = hue;
  color_hue_s[1] = hue;
  color_hue_s[2] = hue;

  current_key_s = -1;
}

void led_presskey(int key)
{
  current_key_s = key;
}

void led_update(void)
{
  bool status_breathing = false;

  if (layer_led_mode_s)
  {
    if (color_hue_s[0] == NEO_RED)
    {
      status_breathing = (SystemMicrophoneMute_is_muted() != 0);
    }
    else if (color_hue_s[0] == NEO_GREEN)
    {
      status_breathing = auto_is_running();
    }
  }

  unsigned long now = millis();

  if (status_breathing)
  {
    if ((now - breath_last_ms_s) >= BREATH_STEP_MS)
    {
      breath_last_ms_s = now;

      if (!breath_down_s)
      {
        if (breath_s < BREATH_MAX)
        {
          breath_s++;
        }
        else
        {
          breath_down_s = true;
        }
      }
      else
      {
        if (breath_s > 0)
        {
          breath_s--;
        }
        else
        {
          breath_down_s = false;
        }
      }
    }
  }
  else
  {
    breath_s = 0;
    breath_down_s = false;
  }

  for (int led = 0; led < 3; led++)
  {
    if (current_key_s == led)
    {
      NEO_writeColor(led, 255, 255, 255);
    }
    else if (status_breathing && led == 0)
    {
      NEO_writeColor(led, 0, breath_s, 0);
    }
    else
    {
      NEO_writeHue(led, color_hue_s[led], NEO_BRIGHT_KEYS);
    }
  }

  NEO_update();
}
