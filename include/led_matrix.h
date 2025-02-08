#ifndef LED_MATRIX_H
#define LED_MATRIX_H

#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"

// Biblioteca gerada pelo arquivo .pio durante compilação.
#include "../build/pio_matrix.pio.h"

// Defines
#define LED_MATRIZ_PIN 7
#define NUM_PIXELS 25
#define COLOR_HEX(r, g, b) (g << 24) | (r << 16) | (b << 8)

// Cabeçalhos das funções
uint matrix_init(uint pin_out);
int matrix_get_index(int aux);
void matrix_draw_number(const uint32_t matriz[10][25], uint8_t numero);

#endif