# Comunicação Serial com RP2040 UART, SPI e I2C

## Enunciado
  Para consolidar os conceitos sobre o uso de interfaces de comunicação serial no RP2040 e explorar
as funcionalidades da placa de desenvolvimento BitDogLab, propõe-se a realização da seguinte tarefa
individual prática.

---

## Objetivos
- Compreender o funcionamento e a aplicação de comunicação serial em microcontroladores.
- Aplicar os conhecimentos adquiridos sobre UART e I2C na prática.
- Manipular e controlar LEDs comuns e LEDs endereçáveis WS2812.
- Fixar o estudo do uso botões de acionamento, interrupções e Debounce.
- Desenvolver um projeto funcional que combine hardware e software.

---

## Ferramentas da BitDogLab utilizadas

- Matriz 5x5 de LEDs (endereçáveis) WS2812, conectada à GPIO 7.
- LED RGB, com os pinos conectados às GPIOs (11, 12 e 13).
- Botão A conectado à GPIO 5.
- Botão B conectado à GPIO 6.
- Display SSD1306 conectado via I2C (GPIO 14 e GPIO15).
- Botão do joystick conectado à GPIO 22.

---

## Funcionamento do Programa
- Inicialmente o display irá exibir o estados dos LEDs, ambos como desligados.
- Quando o Botão A é pressionado o LED verde terá o seu estado alterado para o oposto do atual.
- Quando o Botão B é pressionado o LED azul terá o seu estado alterado para o oposto do atual.
    - Todas as atualizações referentes aos LEDs serão exibidas no display.
- Utilizando o protocolo de comunicação UART, quando alguma tecla é pressionada no teclado do computador, é passada para a placa e atualizada no display.
    - Quando um número é pressionado, a matriz de LEDs ligam no formato do respectivo valor.

---

## Estrutura do Código
- O programa utiliza uma biblioteca própria para o manuseio do display, que utiliza o protocolo de comunicação i2c.
- A coleta dos inputs do teclado é feita via UART pelo USB da placa, utilizando `getchar_timeout_us(0)`
- As outras implementações seguem os padrões de bibliotecas pessoais sobre as ferramentas das placas feitas para as outras tarefas.

---

## Principais funções e arquivos
- `static inline int getchar_timeout_us(uint32_t timeout_us)` : Pega os dados do buffer de entrada durante um periodo de tempo em microsegundos.
- `void gpio_irq_callback(uint gpio, uint32_t events)` : faz a interrupção responsavel por ligar os leds, trocando também variáveis de monitoramentos do estado dos LEDs.
- `font.h` : onde está a fonte com alguns caracteres, sendo eles também os exigidos, letras maiúsculas e minúsculas.
- `display.h e display.c` : Biblioteca para viabilizar a utilização do display ssd1306
- As demais bibliotecas já foram criadas para outras atividades, visando manipulação dos LEDs e da matriz de LEDs

---

## Como Executar o Projeto

1) **Configurar o ambiente**:
   - Instale o Raspberry Pi Pico SDK.
   - Configure o ambiente de desenvolvimento.

2) **Compilar o código**:
   - Clone o repositório no diretório que você quer compilar utilizando:
     ```bash
     git clone https://github.com/yaaggo/one-shot-timer-embarcatech.git
     ```
   - Compile utilizando as ferramentas do SDK do Pico.
   - (opcional) Se estiver utilizando a extensão do Raspberry Pi Pico SDK no vscode, importe o projeto e compile pela extensão

4) **Fazer upload para a placa**:
   - Conecte a Raspberry Pi Pico via USB.
   - Envie o binário gerado para a placa.

5) **Executar o código**:
   - Para utilizar o terminal do vscode para enviar as teclas pressionadas para a placa:
     -  1° Passo: Entrar na aba do monitor serial no vscode após a execução do código na placa
     -  2° Passo: Ativar a caixinha que troca o modo do terminal para receber inputs
     -  3° Passo: Ativar o monitoramento serial.
   - Agora você pode executar as funções do código.
   - Apertando as teclas, irá apresentar no display o caracter pressionado.
   - Quando esse caracter for um número, vai ligar a matriz de LEDs mostrando o número pressionado.
   - Ao pressionar o botão A, o LED verde irá trocar o seu estado.
   - Ao pressionar o botão B, o LED azul irá trocar o seu estado.
   - Ao pressionar o botão do joystick, a placa irá entrar em modo bootsel
---
## Video demonstrativo
  Link do video com uma explicação curta e demonstrando as features na placa: https://www.youtube.com/watch?v=bs6Rd3-Bzqw
