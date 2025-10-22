//Bibliotecas do teclado e do servo
#include <Keypad.h>
#include <Servo.h> 

// Define o número de linhas e colunas do teclado
#define LINHAS 2
#define COLUNAS 3

int sorteado; //Variável que armazena o valor sorteado
Servo servo;  //Objeto para a manipulação do servo-motor

//Pinos  dos LEDS
int ledsComputador[] = {5, 4, 2};
int ledsJogador[] = {8, 7, 6};

// Pinos do teclado conectados às linhas e colunas
byte pinosLinhas[] = {13, 12};
byte pinosColunas[] = {11, 10, 9};

// Mapeamento das teclas
char teclas[LINHAS][COLUNAS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
};

// Cria o objeto teclado
Keypad teclado = Keypad(makeKeymap(teclas), pinosLinhas, pinosColunas, LINHAS, COLUNAS);

void setup() {
  Serial.begin(9600);
  sorteado = 0;
  servo.attach(3);
  for(int i = 0; i < 3; i++){
  	pinMode(ledsComputador[i], OUTPUT);
    pinMode(ledsJogador[i], OUTPUT);
  }
  Serial.println("Pedra, Papel, tesoura!");
}

void loop() {
  char jogada = teclado.getKey(); // Lê a tecla pressionada

  if (jogada) { // Se alguma tecla for pressionada
    int jogadaInt = charParaInt(jogada);
    Serial.println(jogadaInt);
    //Verificar se a tecla é válida
    //Sortear o número aleatório
    //Mover o servo de acordo com o valor sorteado
    //Verificar ganhador e marcar os pontos
    //Verificar se algum jogador atingiu mais de 3 pontos
    //Se sim, piscar os LEDs e reiniciar o jogo
  }

  // Delay para aguardar 10ms
  delay(10);
}

int charParaInt(char c){
	return c - '0';
}

