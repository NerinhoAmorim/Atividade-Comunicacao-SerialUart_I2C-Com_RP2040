#include "led_matrix.h"

// Declaração de variáveis
PIO pio = pio0;
uint sm;

// FUNÇÕES

// Função que inicializa a matriz de LEDs
uint matrix_init(uint pin_out) {

  bool ok;
  ok = set_sys_clock_khz(133000, false);  // configura o clock para 133 MHz
  stdio_init_all();

  printf("Iniciando a transmissão PIO\n");
  if (ok)
    printf("Clock configurado para %ld Hz\n", clock_get_hz(clk_sys));

  uint offset = pio_add_program(pio0, &pio_matrix_program);
  pio = pio0;

  sm = pio_claim_unused_sm(pio, false);
  if (sm < 0) {
    pio = pio1;
    sm = pio_claim_unused_sm(pio, true);
  }

  pio_matrix_program_init(pio, sm, offset, pin_out); 

  return sm;
}

// Função que procura um LED específico na matriz de LEDs, de acordo com seu valor de 0 a 24
int matrix_get_index(int aux) {
  int x = aux % 5;    // coluna
  int y = aux / 5;    // linha
  if (y % 2 == 0) {
    return y * 5 + x; // Linha ímpar (esquerda para direita).
  } else {
    return y * 5 + (4 - x); // Linha par (direita para esquerda).
  }
}

// Função que desenha o padrão passado pela matriz de animação na matriz de LED
void matrix_draw_number(const uint32_t matriz[10][25], uint8_t numero) {
  for (uint8_t aux = 0; aux < NUM_PIXELS; aux++) {
    uint8_t led = matrix_get_index(aux);
    pio_sm_put_blocking(pio0, sm, matriz[numero][24-led]);
  }
}