#include "leds.h"

// Funções

// Função que inicializa o pino do LED e configura como saída
void led_init(uint gpio) {
    gpio_init(gpio);                // inicializa o LED
    gpio_set_dir(gpio, GPIO_OUT);   // configura o LED como saída
}

// Função callback, usada na estrutura de repetição, que muda o estado do LED verde
bool green_repeating_timer_callback(struct repeating_timer *t) {
    gpio_put(GREEN_LED_PIN, !gpio_get(GREEN_LED_PIN));

    // se o retorno for verdadeiro, cria-se um loop na temporização
    return true;
}

// Função callback, usada na estrutura de repetição, que muda o estado do LED azul
bool blue_repeating_timer_callback(struct repeating_timer *t) {
    gpio_put(BLUE_LED_PIN, !gpio_get(BLUE_LED_PIN));

    // se o retorno for verdadeiro, cria-se um loop na temporização
    return true;
}