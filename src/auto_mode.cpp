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

    switch (button_auto_s.function.mouse.mouse_event_sequence[auto_counter_s].type)
    {
    case UP:
      Mouse_move(0, -button_auto_s.function.mouse.mouse_event_sequence[auto_counter_s].value);
      break;
    case DOWN:
      Mouse_move(0, button_auto_s.function.mouse.mouse_event_sequence[auto_counter_s].value);
      break;
    case LEFT:
      Mouse_move(-button_auto_s.function.mouse.mouse_event_sequence[auto_counter_s].value, 0);
      break;
    case RIGH:
      Mouse_move(button_auto_s.function.mouse.mouse_event_sequence[auto_counter_s].value, 0);
      break;
    case LEFT_CLICK:
      Mouse_click(MOUSE_LEFT);
      break;
    case RIGHT_CLICK:
      Mouse_click(MOUSE_RIGHT);
      break;
    case SCROLL_UP:
      Mouse_scroll(button_auto_s.function.mouse.mouse_event_sequence[auto_counter_s].value);
      break;
    case SCROLL_DOWN:
      Mouse_scroll(-button_auto_s.function.mouse.mouse_event_sequence[auto_counter_s].value);
      break;
    default:
      break;
    }
    auto_counter_s++;
    if (auto_counter_s >= button_auto_s.function.mouse.length)
    {
      auto_counter_s = 0;
    }

    auto_next_ms_s = now + button_auto_s.function.mouse.delay;
  }
}