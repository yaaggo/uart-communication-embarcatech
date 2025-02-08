#include <stdio.h>

#include "pico/stdlib.h"
#include "include/display.h"
#include "include/matrix.h"
#include "include/button.h"
#include "include/led.h"

#define DEBUG(var) printf("%s: %c\n", #var, var)

int main() {
    stdio_init_all();

    char previous_key = -1;

    // inicializando o display
    display display;
    display_init(&display);


    // inicializando a matriz de leds
    matrix_init(MATRIX_LED_PIN);
    
    // inicializando botoes

    while (true) {
        char key_pressed = getchar();
        DEBUG(key_pressed);

        if(key_pressed != previous_key) {
            
            if(key_pressed >= '0' && key_pressed <= '9') {
                matrix_number(key_pressed - '0', COLOR_RGB(50, 0, 0));
                matrix_update();
            } else {
                matrix_clear();
                matrix_update();
            }
            
            display_clear(&display);
            display_draw_char(128/2 - 4, 64/2 - 4, key_pressed, true, &display);
            display_update(&display);
        }

        sleep_ms(100);
    }
}