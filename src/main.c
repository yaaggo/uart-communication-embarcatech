#include <stdio.h>

#include "pico/stdlib.h"
#include "include/display.h"
#include "include/matrix.h"
#include "include/led.h"

#define BUTTON_A_PIN 5
#define BUTTON_B_PIN 6
#define DEBOUNCE_DELAY 200

#define DEBUG(var) printf("%s: %c\n", #var, var)

display dp;

static volatile uint32_t last_a_interrupt_time = 0;
static volatile uint32_t last_b_interrupt_time = 0;

volatile bool led_green_state = 0;
volatile bool led_blue_state = 0;

void gpio_irq_callback(uint gpio, uint32_t events);
void button_init(uint8_t pin);

int main() {
    stdio_init_all();

    char previous_key = -1;
    bool previous_led_blue = -1;
    bool previous_led_green = -1;
    bool first = 1;

    // inicializando o display
    display_init(&dp);

    // inicializando a matriz de leds
    matrix_init(MATRIX_LED_PIN);

    // inicializando botoes
    button_init(BUTTON_A_PIN);
    button_init(BUTTON_B_PIN);

    // inicializando leds
    led_init(LED_BLUE_PIN);
    led_init(LED_GREEN_PIN);

    while (true) {
        int key_pressed = getchar_timeout_us(0);
        
        if (key_pressed != PICO_ERROR_TIMEOUT && key_pressed != previous_key) {
            DEBUG(key_pressed);

            if (key_pressed >= '0' && key_pressed <= '9') {
                matrix_number(key_pressed - '0', COLOR_RGB(50, 0, 0));
                matrix_update();
            } else {
                matrix_clear();
                matrix_update();
            }

            display_draw_char(128/2 - 4, 8, previous_key, false, &dp);
            display_draw_char(128/2 - 4, 8, key_pressed, true, &dp);
            previous_key = key_pressed;
        }

        if (led_blue_state != previous_led_blue) {
            if(!first) {
                printf("Estado do do LED azul alterado de %s para %s\n", 
                    led_blue_state ? "OFF" : "ON",
                    led_blue_state ? "ON" : "OFF"
                );

            }

            display_draw_string(96, 32, previous_led_blue ? "ON " : "OFF", false, &dp);
            display_draw_string(96, 32, led_blue_state ? "ON " : "OFF", true, &dp);
            previous_led_blue = led_blue_state;
        }

        if (led_green_state != previous_led_green) {

            if(!first) {
                printf("Estado do do LED verde alterado de %s para %s\n", 
                    led_green_state ? "OFF" : "ON",
                    led_green_state ? "ON" : "OFF"
                );
            }


            display_draw_string(96, 48, previous_led_green ? "ON " : "OFF", false, &dp);
            display_draw_string(96, 48, led_green_state ? "ON " : "OFF", true, &dp);
            previous_led_green = led_green_state;
        }

        display_draw_string(8, 32, "LED Azul: ", true, &dp);
        display_draw_string(8, 48, "LED Verde: ", true, &dp);

        display_update(&dp);
        first = 0;

        sleep_ms(50); 
    }
}

// callback para interrupção dos botões
void gpio_irq_callback(uint gpio, uint32_t events) {
    uint32_t current_time = to_ms_since_boot(get_absolute_time());

    // verifica qual botão acionou a interrupção e trata o debounce
    if (gpio == BUTTON_A_PIN) {
        if (current_time - last_a_interrupt_time > DEBOUNCE_DELAY) {
            last_a_interrupt_time = current_time;

            if (events & GPIO_IRQ_EDGE_FALL) {
                led_state(LED_GREEN_PIN, led_green_state = !led_green_state);
            }
        }
    } else if (gpio == BUTTON_B_PIN) {
        if (current_time - last_b_interrupt_time > DEBOUNCE_DELAY) {
            last_b_interrupt_time = current_time;

            if (events & GPIO_IRQ_EDGE_FALL) {   
                led_state(LED_BLUE_PIN, led_blue_state = !led_blue_state);
            }
        }
    }

}

// inicializa o botão e configura interrupções
void button_init(uint8_t pin) {
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_IN);
    gpio_pull_up(pin);

    // habilita interrupções para bordas de subida e descida
    gpio_set_irq_enabled_with_callback(
        pin,
        GPIO_IRQ_EDGE_FALL,
        true,
        &gpio_irq_callback
    );
}
