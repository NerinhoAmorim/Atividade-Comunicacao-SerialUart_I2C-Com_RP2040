# Atividade-Comunicacao-SerialUart_I2C-Com_RP2040

## 📌 Enunciado
Para consolidar os conceitos sobre o uso de interfaces de comunicação serial no RP2040 e explorar as funcionalidades da placa de desenvolvimento BitDogLab, propõe-se a realização da seguinte tarefa individual prática.

## 🎯 Objetivos
- Compreender o funcionamento e a aplicação de comunicação serial em microcontroladores.
- Aplicar os conhecimentos adquiridos sobre UART e I2C na prática.
- Manipular e controlar LEDs comuns e LEDs endereçáveis WS2812.
- Fixar o estudo do uso de botões de acionamento, interrupções e debounce.
- Desenvolver um projeto funcional que combine hardware e software.

## 🛠️ Descrição do Projeto
Neste projeto, você deverá utilizar os seguintes componentes conectados à placa BitDogLab:

- **Matriz 5x5 de LEDs (endereçáveis) WS2812** conectada à GPIO 7.
- **LED RGB**, com os pinos conectados às GPIOs 11, 12 e 13.
- **Botão A** conectado à GPIO 5.
- **Botão B** conectado à GPIO 6.
- **Display SSD1306** conectado via I2C (GPIO 14 e GPIO 15).

## ⚙️ Funcionalidades do Projeto

### 1️⃣ Modificação da Biblioteca `font.h`
- Adicionar caracteres minúsculos à biblioteca `font.h`. Use sua criatividade para criar os novos caracteres.

### 2️⃣ Entrada de caracteres via PC
- Utilize o **Serial Monitor** do VS Code para digitar os caracteres.
- Cada caractere digitado no Serial Monitor deve ser exibido no display **SSD1306**.
- Quando um número entre 0 e 9 for digitado, um símbolo correspondente ao número deve ser exibido também na matriz **5x5 WS2812**.

### 3️⃣ Interação com o Botão A
- Pressionar o **botão A** deve alternar o estado do **LED RGB Verde** (ligado/desligado).
- A operação deve ser registrada de duas formas:
  - Uma **mensagem informativa** sobre o estado do LED deve ser exibida no **display SSD1306**.
  - Um **texto descritivo** sobre a operação deve ser enviado ao **Serial Monitor**.

### 4️⃣ Interação com o Botão B
- Pressionar o **botão B** deve alternar o estado do **LED RGB Azul** (ligado/desligado).
- A operação deve ser registrada de duas formas:
  - Uma **mensagem informativa** sobre o estado do LED deve ser exibida no **display SSD1306**.
  - Um **texto descritivo** sobre a operação deve ser enviado ao **Serial Monitor**.

## ✅ Requisitos do Projeto
1. **Uso de interrupções**: Todas as funcionalidades relacionadas aos botões devem ser implementadas utilizando rotinas de interrupção (**IRQ**).
2. **Debouncing**: É obrigatório implementar o tratamento do bouncing dos botões via software.
3. **Controle de LEDs**: O projeto deve incluir o uso de LEDs comuns e LEDs WS2812, demonstrando o domínio de diferentes tipos de controle.
4. **Utilização do Display 128x64**: A utilização de fontes maiúsculas e minúsculas demonstrará o domínio do uso de bibliotecas, o entendimento do princípio de funcionamento do display, bem como a utilização do protocolo **I2C**.
5. **Envio de informação pela UART**: Visa observar a compreensão sobre a comunicação serial via **UART**.
6. **Organização do código**: O código deve estar bem estruturado e comentado para facilitar o entendimento.

## 🔗 Links Relevantes
- **[Repositório GitHub](https://github.com/NerinhoAmorim/Atividade-Comunicacao-SerialUart_I2C-Com_RP2040.git)**
- **[Vídeo de Apresentação](#) (inserir link do vídeo aqui)**

## 👨‍💻 Autor
**Nerinho Amorim**


