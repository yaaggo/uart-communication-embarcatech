#include "button.h"
#include "pico/stdlib.h"
#include "matrix.h"

// variaveis de estado para debounce
static volatile uint32_t last_a_interrupt_time = 0;
static volatile uint32_t last_b_interrupt_time = 0;

volatile int8_t counter = 0;

int8_t prev_counter = 0;

// fazer como static impediria o sdk de usar como global
// por ser de uso interno, não vou colocar na .h

// callback para interrupção dos botões
void gpio_irq_callback(uint gpio, uint32_t events) {
    uint32_t current_time = to_ms_since_boot(get_absolute_time());

    // verifica qual botão acionou a interrupção e trata o debounce
    if (gpio == BUTTON_A_PIN) {
        if (current_time - last_a_interrupt_time > DEBOUNCE_DELAY) {
            last_a_interrupt_time = current_time;

            if (events & GPIO_IRQ_EDGE_FALL) {
                counter++;
            }
        }
    } else if (gpio == BUTTON_B_PIN) {
        if (current_time - last_b_interrupt_time > DEBOUNCE_DELAY) {
            last_b_interrupt_time = current_time;

            if (events & GPIO_IRQ_EDGE_FALL) {
                counter--;
            }
        }
    }

    counter = (counter < 0) ? 9 : (counter > 9 ? 0 : counter);
    
    if(counter != prev_counter) {
        matrix_number(counter, COLOR_RGB(1, 1, 1));
    }
    prev_counter = counter;
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