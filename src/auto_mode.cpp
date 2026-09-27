#include <Arduino.h>
#include "userUsbHidKeyboardMouse/USBHIDKeyboardMouse.h"
#include "led.h"
#include "keyboard.h"
#include "auto_mode.h"

static button_function_t button_auto_s = {BUTTON_NULL};
static uint8_t auto_counter_s = 0;
static unsigned long auto_next_ms_s = 0;

void auto_set_cycle(button_function_t button_auto)
{
  auto_counter_s = 0;
  button_auto_s = button_auto;
  auto_next_ms_s = 0;
}

bool auto_is_running(void)
{
  return button_auto_s.type != BUTTON_NULL;
}

void auto_update(void)
{
  if (button_auto_s.type == BUTTON_NULL)
  {
    return;
  }

  if (button_auto_s.type == BUTTON_AUTO_KEYBOARD)
  {
    Keyboard_press(button_auto_s.function.sequence.sequence[auto_counter_s]);
    delay(button_auto_s.function.sequence.delay);
    Keyboard_releaseAll();

    auto_counter_s++;

    if (auto_counter_s >= button_auto_s.function.sequence.length)
    {
      auto_counter_s = 0;
    }

    return;
  }

  if (button_auto_s.type == BUTTON_AUTO_MOUSE)
  {
    unsigned long now = millis();

    if (now < auto_next_ms_s)
    {
      return;
    }

    int8_t x;
    int8_t y;

    do
    {
      x = (int8_t)random(-5, 6);
      y = (int8_t)random(-5, 6);
    }
    while (x == 0 && y == 0);

    Mouse_move(x, y);

    auto_next_ms_s = now + button_auto_s.function.mouse.delay;
  }
}