#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "include/frames.h"
#include "include/font.h"
#include "include/ssd1306.h"
#include "include/botoes.h"
#include "include/leds.h"
#include "include/led_matrix.h"

#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define ENDERECO 0x3C

// Cabeçalho da função de callback dos botões
void button_irq_handler(uint gpio, uint32_t events);

// Declaração de variáveis
bool cor = true;
uint8_t num = 0;          // Variável para armazenar números
absolute_time_t debounce; // Variável para controle de debounce
ssd1306_t ssd;            // Estrutura para o display SSD1306

int main()
{
    stdio_init_all(); // Inicializa a comunicação padrão

    // Inicialização e configuração dos componentes a serem utilizados
    led_init(RED_LED_PIN);
    led_init(GREEN_LED_PIN);
    led_init(BLUE_LED_PIN);
    button_init(BUTTON_A_PIN);
    button_init(BUTTON_B_PIN);
    matrix_init(LED_MATRIZ_PIN);

    // Configuração das interrupções nos botões A e B
    gpio_set_irq_enabled_with_callback(BUTTON_A_PIN, GPIO_IRQ_EDGE_FALL, true, &button_irq_handler);
    gpio_set_irq_enabled_with_callback(BUTTON_B_PIN, GPIO_IRQ_EDGE_FALL, true, &button_irq_handler);

    // Inicialização do I2C, usando em 400KHz
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C); // Configura o pino SDA para I2C
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C); // Configura o pino SCL para I2C
    gpio_pull_up(I2C_SDA);                     // Ativa pull-up no SDA
    gpio_pull_up(I2C_SCL);                     // Ativa pull-up no SCL

    // Inicializa e configura o display SSD1306
    ssd1306_init(&ssd, 128, 64, false, ENDERECO, I2C_PORT);
    ssd1306_config(&ssd);
    ssd1306_fill(&ssd, false); // Limpa o display
    ssd1306_send_data(&ssd);   // Envia os dados para o display

    // Mensagem de boas-vindas
    cor = !cor;
    // Atualiza o conteudo do display
    ssd1306_fill(&ssd, !cor);                        // Limpa o display
    ssd1306_draw_string(&ssd, "Bem-vindo!", 8, 10);  // Mensagem fixa
    ssd1306_rect(&ssd, 3, 3, 122, 58, cor, !cor);    // Desenha um retângulo
    ssd1306_draw_string(&ssd, "Fev de 2025", 8, 10); // Desenha uma string
    ssd1306_draw_string(&ssd, "NERINHO AMORIM", 20, 30);   // Desenha uma string
    ssd1306_send_data(&ssd);                         // Envia os dados para o display
    sleep_ms(2000);                                  // Aguarda 2 segundos para visualizar

    debounce = delayed_by_ms(get_absolute_time(), 200); // Inicializa debounce

    while (true)
    {
        // Verifica se há conexão USB para leitura de caracteres
        if (stdio_usb_connected())
        {
            char c;
            scanf(" %c", &c); // Lê um caractere da entrada padrão
            printf("Caractere: '%c'\n", c);

            // Limpa o display antes de desenhar novos caracteres
            ssd1306_fill(&ssd, false); // Limpa o display

            // Atualiza o display com o caractere lido
            ssd1306_draw_string(&ssd, "Caractere: ", 8, 10);
            ssd1306_draw_char(&ssd, c, 90, 10); // Desenha o caractere
            ssd1306_send_data(&ssd);            // Envia os dados para o display

            // Se o caractere for um número, desenha na matriz de LEDs
            if (c >= '0' && c <= '9')
            {
                num = c - '0';                    // Converte o caractere para uint8_t
                matrix_draw_number(numeros, num); // Imprime o número correspondente na matriz de LEDs
            }
        }
        sleep_ms(40); // Aguarda um curto período
    }
}

// Função callback que verifica se o tempo para que o debouncing ocorra foi alcançado
void button_irq_handler(uint gpio, uint32_t events)
{
    if (time_reached(debounce))
    {
        // Debounce para o botão A
        if (gpio == BUTTON_A_PIN)
        {
            // Verifica se o LED azul está ligado. Se sim, desliga para não misturar as cores
            if (gpio_get(BLUE_LED_PIN))
            {
                gpio_put(BLUE_LED_PIN, 0);
            }
            gpio_put(GREEN_LED_PIN, !gpio_get(GREEN_LED_PIN)); // Alterna o estado do LED verde

            // Exibe mensagem de acordo com o estado do LED
            if (gpio_get(GREEN_LED_PIN))
            {
                printf("LED VERDE ON\n");
                ssd1306_draw_string(&ssd, "LED VERDE ON!  ", 15, 48);
            }
            else
            {
                printf("LED VERDE OFF\n");
                ssd1306_draw_string(&ssd, "LED VERDE OFF! ", 15, 48);
            }
        }

        // Debounce para o botão B
        if (gpio == BUTTON_B_PIN)
        {
            // Verifica se o LED verde está ligado. Se sim, desliga para não misturar as cores
            if (gpio_get(GREEN_LED_PIN))
            {
                gpio_put(GREEN_LED_PIN, 0);
            }
            gpio_put(BLUE_LED_PIN, !gpio_get(BLUE_LED_PIN)); // Alterna o estado do LED azul

            // Exibe mensagem de acordo com o estado do LED
            if (gpio_get(BLUE_LED_PIN))
            {
                printf("LED AZUL ON\n");
                ssd1306_draw_string(&ssd, "LED AZUL ON!   ", 15, 48);
            }
            else
            {
                printf("LED AZUL OFF\n");
                ssd1306_draw_string(&ssd, "LED AZUL OFF!  ", 15, 48);
            }
        }

        // Atualiza o display
        ssd1306_send_data(&ssd);
        debounce = delayed_by_ms(get_absolute_time(), 200); // Reinicia o debounce
    }
}