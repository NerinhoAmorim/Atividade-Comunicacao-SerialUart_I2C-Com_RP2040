#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "hardware/pio.h"
#include "hardware/i2c.h"
#include "hardware/uart.h"
#include "pio_matrix.pio.h"
#include "include/ssd1306.h"
#include "include/font.h"
#include "include/drawing_leds.h"

// Definições de constantes
#define UART_ID uart0         // Seleciona a UART0
#define I2C_PORT i2c1         // Porta de inicialização do display
#define ENDERECO 0x3C         // Endereço de inicialização do display
#define I2C_SDA 14            // Pino SDA do display
#define I2C_SCL 15            // Pino SCL do display
#define BTN_A 5               // Pino do botão A
#define BTN_B 6               // Pino do botão B
#define OUT_PINO 7            // Pino da matriz de LEDs
#define GREEN_PINO 11         // Pino do LED verde do RGB
#define BLUE_PINO 12          // Pino do LED azul do RGB
#define RED_PINO 13           // Pino do LED vermelho do RGB
#define UART_TX_PINO 0        // Pino GPIO usado para TX
#define UART_RX_PINO 1        // Pino GPIO usado para RX
#define BAUD_RATE 115200      // Define a taxa de transmissão serial
#define NUMERO_DE_LEDS 25     // Número de LEDs na matriz
#define DEBOUNCE_LINE 300000  // 300ms em microsegundos

// Variáveis globais
bool cor = true;                      // Estado da cor
ssd1306_t ssd;                        // Estrutura do display
volatile int btn_a_acionado = 0;     // Controle do botão A pressionado
volatile int btn_b_acionado = 0;     // Controle do botão B pressionado

// Função de callback para interrupção dos botões
void button_callback(uint gpio, uint32_t events) {
    uint32_t marco = time_us_32();  // Obtém o tempo atual em microsegundos

    // Tratamento do botão A
    if (gpio == BTN_A && (marco - btn_a_acionado) > DEBOUNCE_LINE) {
        btn_a_acionado = marco;  // Atualiza o tempo do botão A
        // Alterna o estado do LED verde
        if (gpio_get(GREEN_PINO)) {
            gpio_put(GREEN_PINO, false);
            cor = !cor;
            ssd1306_fill(&ssd, !cor);  // Limpa o display
            ssd1306_draw_string(&ssd, "Verde Desativado", 20, 30);
            ssd1306_send_data(&ssd);  // Atualiza o display
            uart_puts(UART_ID, "\nVerde Desativado!");
        } else {
            gpio_put(GREEN_PINO, true);
            cor = !cor;
            ssd1306_fill(&ssd, !cor);  // Limpa o display
            ssd1306_draw_string(&ssd, "Led Verde Ativado", 20, 30);
            ssd1306_send_data(&ssd);  // Atualiza o display
            uart_puts(UART_ID, "\nLed Verde Ativado!");
        }
    } 
    // Tratamento do botão B
    else if (gpio == BTN_B && (marco - btn_b_acionado) > DEBOUNCE_LINE) {
        btn_b_acionado = marco;  // Atualiza o tempo do botão B

        // Alterna o estado do LED azul
        if (gpio_get(BLUE_PINO)) {
            gpio_put(BLUE_PINO, false);
            cor = !cor;
            ssd1306_fill(&ssd, !cor);  // Limpa o display
            ssd1306_draw_string(&ssd, "Led Azul Desativado", 20, 30);
            ssd1306_send_data(&ssd);  // Atualiza o display
            uart_puts(UART_ID, "\nLed Azul Desativado!");
        } else {
            gpio_put(BLUE_PINO, true);
            cor = !cor;
            ssd1306_fill(&ssd, !cor);  // Limpa o display
            ssd1306_draw_string(&ssd, "Led Azul Ativado", 20, 30);
            ssd1306_send_data(&ssd);  // Atualiza o display
            uart_puts(UART_ID, "\nLed Azul Ativado!");
        }
    }
}

int main() {
    PIO pio = pio0;                      // Inicializa PIO
    uint32_t valor_led = 0;              // Inicializa valor LED
    double r = 0.0, b = 0.0, g = 0.0;    // Inicializa valores RGB
    // Inicializa o programa PIO
    uint offset = pio_add_program(pio, &pio_matrix_program);
    uint sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, OUT_PINO);
    // Inicializa I2C
    i2c_init(I2C_PORT, 400 * 1000);             // 400KHz
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);  // Configura GPIO para I2C
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);  // Configura GPIO para I2C
    gpio_pull_up(I2C_SDA);                      // Ativa pull-up
    gpio_pull_up(I2C_SCL);                      // Ativa pull-up
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, ENDERECO, I2C_PORT);  // Inicializa o display
    ssd1306_config(&ssd);                       // Configura o display
    ssd1306_send_data(&ssd);                    // Envia dados para o display
    // Limpa o display
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);
    // Inicializa a UART
    stdio_init_all();
    uart_init(UART_ID, BAUD_RATE);
    // Inicializa pinos do LED RGB
    gpio_init(RED_PINO);
    gpio_init(GREEN_PINO);
    gpio_init(BLUE_PINO);
    gpio_set_dir(RED_PINO, GPIO_OUT);
    gpio_set_dir(GREEN_PINO, GPIO_OUT);
    gpio_set_dir(BLUE_PINO, GPIO_OUT);
    // Configura pinos UART
    gpio_set_function(UART_TX_PINO, GPIO_FUNC_UART);  // TX
    gpio_set_function(UART_RX_PINO, GPIO_FUNC_UART);  // RX
    // Inicializa // botões A e B
    gpio_init(BTN_A);
    gpio_init(BTN_B);
    gpio_set_dir(BTN_A, GPIO_IN);
    gpio_set_dir(BTN_B, GPIO_IN);
    gpio_pull_up(BTN_A);  // Ativa pull-up para o botão A
    gpio_pull_up(BTN_B);  // Ativa pull-up para o botão B
    // Habilita interrupções para os botões
    gpio_set_irq_enabled_with_callback(BTN_A, GPIO_IRQ_EDGE_FALL, true, &button_callback);
    gpio_set_irq_enabled_with_callback(BTN_B, GPIO_IRQ_EDGE_FALL, true, &button_callback);
    const char *init_message = "Digite o caracter que deseja:\r\n";
    uart_puts(UART_ID, init_message);  // Mensagem inicial na UART

    while (true) {
        cor = !cor;  // Alterna a cor para o display
        ssd1306_fill(&ssd, !cor);  // Limpa o display
        ssd1306_rect(&ssd, 3, 3, 122, 58, cor, !cor);  // Desenha um retângulo
        ssd1306_draw_string(&ssd, "Fev de 2025", 8, 10);  // Exibe data
        ssd1306_draw_string(&ssd, "EMBARCATEC", 20, 30);  // Exibe título
        ssd1306_draw_string(&ssd, "NERINHO AMORIM", 15, 48);  // Exibe nome
        ssd1306_send_data(&ssd);  // Atualiza o display

        // Verifica se há dados disponíveis na UART
        if (uart_is_readable(UART_ID)) {
            char c = uart_getc(UART_ID);  // Lê um caractere da UART
            ssd1306_fill(&ssd, cor);  // Limpa o display
            ssd1306_draw_char(&ssd, c, 20, 30);  // Desenha o caractere recebido
            ssd1306_send_data(&ssd);  // Atualiza o display
        }

        sleep_ms(1000);  // Aguarda 1 segundo antes da próxima atualização
    }
}