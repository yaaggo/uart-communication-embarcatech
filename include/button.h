#ifndef BUTTON_H
#define BUTTON_H

#define BUTTON_A_PIN 5
#define BUTTON_B_PIN 6
#define DEBOUNCE_DELAY 200

#include <stdint.h>
#include <stdbool.h>

extern volatile int8_t counter;
extern int8_t prev_counter;

void button_init(uint8_t pin);

#endif