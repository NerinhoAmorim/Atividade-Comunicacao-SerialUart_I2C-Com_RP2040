```markdown
# Projeto de Comunicação Serial com RP2040 e BitDogLab

## 🎯 Objetivos

- Compreender o funcionamento e a aplicação de comunicação serial em microcontroladores.
- Aplicar os conhecimentos adquiridos sobre UART e I2C na prática.
- Manipular e controlar LEDs comuns e LEDs endereçáveis WS2812.
- Fixar o estudo do uso de botões de acionamento, interrupções e debounce.
- Desenvolver um projeto funcional que combine hardware e software.

## 🛠️ Descrição do Projeto

Neste projeto, você deverá utilizar os seguintes componentes conectados à placa BitDogLab:

- Matriz 5x5 de LEDs (endereçáveis) WS2812 conectada à GPIO 7.
- LED RGB, com os pinos conectados às GPIOs 11, 12 e 13.
- Botão A conectado à GPIO 5.
- Botão B conectado à GPIO 6.
- Display SSD1306 conectado via I2C (GPIO 14 e GPIO 15).

## ⚙️ Funcionalidades do Projeto

1. **Modificação da Biblioteca font.h**
   - Adicionar caracteres minúsculos à biblioteca font.h. Use sua criatividade para criar os novos caracteres.

2. **Entrada de caracteres via PC**
   - Utilize o Serial Monitor do VS Code para digitar os caracteres.
   - Cada caractere digitado no Serial Monitor deve ser exibido no display SSD1306.
   - Quando um número entre 0 e 9 for digitado, um símbolo correspondente ao número deve ser exibido também na matriz 5x5 WS2812.

3. **Interação com o Botão A**
   - Pressionar o botão A deve alternar o estado do LED RGB Verde (ligado/desligado).
   - A operação deve ser registrada de duas formas:
     - Uma mensagem informativa sobre o estado do LED deve ser exibida no display SSD1306.
     - Um texto descritivo sobre a operação deve ser enviado ao Serial Monitor.

4. **Interação com o Botão B**
   - Pressionar o botão B deve alternar o estado do LED RGB Azul (ligado/desligado).
   - A operação deve ser registrada de duas formas:
     - Uma mensagem informativa sobre o estado do LED deve ser exibida no display SSD1306.
     - Um texto descritivo sobre a operação deve ser enviado ao Serial Monitor.

## ✅ Requisitos do Projeto

- **Uso de interrupções:** Todas as funcionalidades relacionadas aos botões devem ser implementadas utilizando rotinas de interrupção (IRQ).
- **Debouncing:** É obrigatório implementar o tratamento do bouncing dos botões via software.
- **Controle de LEDs:** O projeto deve incluir o uso de LEDs comuns e LEDs WS2812, demonstrando o domínio de diferentes tipos de controle.
- **Utilização do Display 128x64:** A utilização de fontes maiúsculas e minúsculas demonstrará o domínio do uso de bibliotecas, o entendimento do princípio de funcionamento do display, bem como a utilização do protocolo I2C.
- **Envio de informação pela UART:** Visa observar a compreensão sobre a comunicação serial via UART.
- **Organização do código:** O código deve estar bem estruturado e comentado para facilitar o entendimento.

## 🚀 Como Usar o Projeto

1. **Clone o repositório**
   ```
   git clone https://github.com/NerinhoAmorim/Atividade-Comunicacao-SerialUart_I2C-Com_RP2040.git
   cd Atividade-Comunicacao-SerialUart_I2C-Com_RP2040
   ```

2. **Compile e carregue o código na placa BitDogLab**
   - Use uma IDE como o VS Code ou outra de sua preferência que suporte a placa RP2040.
   - Certifique-se de que todas as bibliotecas necessárias estejam instaladas.

3. **Conecte a placa ao seu PC**
   - Utilize um cabo USB para conectar a placa ao seu computador.

4. **Abra o Serial Monitor**
   - Utilize o Serial Monitor do VS Code ou outra ferramenta de sua escolha para enviar e receber dados via UART.

5. **Teste as funcionalidades**
   - Digite caracteres no Serial Monitor e observe o comportamento no display SSD1306 e na matriz de LEDs WS2812.
   - Pressione os botões A e B para testar a alternância dos LEDs RGB e observe as mensagens exibidas no display e enviadas ao Serial Monitor.

---

## 🔗 Links Relevantes
- **Repositório:**[Repositório GitHub](https://github.com/NerinhoAmorim/Atividade-Comunicacao-SerialUart_I2C-Com_RP2040.git)
   🔗 [Vídeo Apresentação:](https://vimeo.com/1054789934?share=copy)

## 👨‍💻 Autor
**Nerinho Amorim**
