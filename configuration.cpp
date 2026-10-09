#include "configuration.h"
#include "src/userUsbHidKeyboardMouse/USBHIDKeyboardMouse.h"
#include <Arduino.h>

#define TEXT_DELAY_MS 60

static const char rke2_shell_text[] =
    "export PATH=\"$PATH:/var/lib/rancher/rke2/bin\"; "
    "export KUBECONFIG=/etc/rancher/rke2/rke2.yaml; "
    "export CONTAINER_RUNTIME_ENDPOINT=unix:///run/k3s/containerd/containerd.sock; "
    "export IMAGE_SERVICE_ENDPOINT=unix:///run/k3s/containerd/containerd.sock; "
    "bind '\"\\e[5~\": history-search-backward'; "
    "bind '\"\\e[6~\": history-search-forward'; "
    "source <(kubectl completion bash); "
    "source <(crictl completion bash); "
    "source <(helm completion bash); "
    "source <(openstack complete); "
    "complete -C tofu tofu; "
    "alias k=kubectl; "
    "complete -o default -F __start_kubectl k";

static void button_type_rke2_shell(keyboard_button_keyboard_mode_t mode)
{
    if (mode != BTM_PRESS)
    {
        return;
    }

    for (uint16_t i = 0; i < sizeof(rke2_shell_text) - 1; i++)
    {
        Keyboard_write((uint8_t)rke2_shell_text[i]);
        delay(TEXT_DELAY_MS);
    }
}

static void button_volume_up(keyboard_button_keyboard_mode_t mode)
{
    if (mode == BTM_CLICK)
    {
        Consumer_write(MEDIA_VOLUME_UP);
    }
}

static void button_volume_down(keyboard_button_keyboard_mode_t mode)
{
    if (mode == BTM_CLICK)
    {
        Consumer_write(MEDIA_VOLUME_DOWN);
    }
}

const keyboard_configuration_t configurations[NUM_CONFIGURATION] = {
    {
        .button =
        {
            [BTN_1] = {
                .type = BUTTON_SEQUENCE,
                .function.sequence = {
                    .sequence = {KEY_LEFT_CTRL, KEY_LEFT_ALT, KEY_LEFT_SHIFT, KEY_F20},
                    .length = 4,
                    .delay = 0
                }
           },

            [BTN_2] = {
                .type = BUTTON_SEQUENCE,
                .function.sequence = {
                    .sequence = {
                        'k'
                    },
                    .length = 1,
                    .delay = 0
                }
            },

            [BTN_3] = {
                .type = BUTTON_NULL,
            },

            [ENC_CW] = {
                .type = BUTTON_FUNCTION,
                .function.functionPointer = button_volume_up,
            },

            [ENC_CCW] = {
                .type = BUTTON_FUNCTION,
                .function.functionPointer = button_volume_down,
            },

            [BTN_ENC] = {
                .type = BUTTON_FUNCTION,
                .function.functionPointer = keyboard_press_enc,
            },
        }
    },

    {
        .button =
        {
            [BTN_1] = {
                .type = BUTTON_AUTO_MOUSE,
                .function.mouse = {
                    .mouse_event_sequence = {
                        {
                            .type = UP,
                            .value = 3
                        },
                       {
                            .type = RIGH,
                            .value = 3
                        },
                        {
                            .type = DOWN,
                            .value = 3
                        },
                       {
                            .type = LEFT,
                            .value = 3
                        },

                    },
                    .length = 4,
                    .delay = 250,
                    .keypress = 0
                }
            },
            [BTN_2] = {
                .type = BUTTON_FUNCTION,
                .function.functionPointer = button_type_rke2_shell,
            },

            [BTN_3] = {
                .type = BUTTON_NULL,
            },


            [ENC_CW] = {
                .type = BUTTON_MOUSE,
                .function.mouse = {
                    .mouse_event_sequence = {
                        {
                            .type = SCROLL_UP,
                            .value = 2
                        }
                    },
                    .length = 1,
                    .delay = 0,
                    .keypress = 0
                }
            },

            [ENC_CCW] = {
                .type = BUTTON_MOUSE,
                .function.mouse = {
                    .mouse_event_sequence = {
                        {
                            .type = SCROLL_DOWN,
                            .value = 2
                        }
                    },
                    .length = 1,
                    .delay = 0,
                    .keypress = 0
                }
            },

            [BTN_ENC] = {
                .type = BUTTON_FUNCTION,
                .function.functionPointer = keyboard_press_enc,
            },
        }
    },

    {
        .button =
        {
            [BTN_1] = { .type = BUTTON_NULL },
            [BTN_2] = { .type = BUTTON_NULL },
            [BTN_3] = { .type = BUTTON_NULL },
            [ENC_CW] = { .type = BUTTON_NULL },
            [ENC_CCW] = { .type = BUTTON_NULL },

            [BTN_ENC] = {
                .type = BUTTON_FUNCTION,
                .function.functionPointer = keyboard_press_enc,
            },
        }
    },

    {
        .button =
        {
            [BTN_1] = { .type = BUTTON_NULL },
            [BTN_2] = { .type = BUTTON_NULL },
            [BTN_3] = { .type = BUTTON_NULL },

            [ENC_CW] = {
                .type = BUTTON_FUNCTION,
                .function.functionPointer = button_menu_up,
            },

            [ENC_CCW] = {
                .type = BUTTON_FUNCTION,
                .function.functionPointer = button_menu_down,
            },

            [BTN_ENC] = {
                .type = BUTTON_FUNCTION,
                .function.functionPointer = keyboard_press_enc,
            },
        }
    },
};