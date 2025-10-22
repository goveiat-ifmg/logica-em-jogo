#include <Keypad.h>
#include <Servo.h> 

// Define o número de linhas e colunas do teclado
#define LINHAS 4
#define COLUNAS 4

int sorteado; //Variável que armazena o valor sorteado
Servo servo;  //Objeto para a manipulação do servo-motor

int ledsComputador[] = {5, 4, 2};
int ledsJogador[] = {8, 7, 6};
int jogador_ganha[] = {3, 1, 2};
int pontosJogador;
int pontosComputador;

// Mapeamento das teclas
char teclas[LINHAS][COLUNAS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
};

// Pinos conectados às linhas e colunas
byte pinosLinhas[LINHAS] = {13, 12};
byte pinosColunas[COLUNAS] = {11, 10, 9};

// Cria o objeto teclado
Keypad teclado = Keypad(makeKeymap(teclas), pinosLinhas, pinosColunas, LINHAS, COLUNAS);

void setup() {
  Serial.begin(9600);
  sorteado = 0;
  servo.attach(3);
  pontosJogador = 0;
  pontosComputador = 0;
  for(int i = 0; i < 3; i++){
  	pinMode(ledsComputador[i], OUTPUT);
    pinMode(ledsJogador[i], OUTPUT);
  }
  Serial.println("Pedra, Papel, tesoura");
}

void loop() {
  char tecla = teclado.getKey(); // Lê a tecla pressionada

  if (tecla) { // Se alguma tecla for pressionada
    int teclaInt = charParaInt(tecla);
    Serial.print("Tecla pressionada: ");
    Serial.println(tecla);
    sorteado = random(1, 4);
    Serial.print("Valor sorteado: ");
    Serial.println(sorteado);
    switch(sorteado){
      case 1: servo.write(180); break;
      case 2: servo.write(90); break;
      case 3: servo.write(0); break;
      default: Serial.println("Erro!");
    }
    
    if (teclaInt == sorteado) {
      Serial.println("Empate!\n");
    } else if (jogador_ganha[teclaInt-1] == sorteado) {
      Serial.println("Jogador vence!\n");
      pontosJogador++;
      digitalWrite(ledsJogador[pontosJogador-1], HIGH);
    } else {
      Serial.println("Computador vence!\n");
      pontosComputador++;
      digitalWrite(ledsComputador[pontosComputador-1], HIGH);
    }
    
    if(pontosJogador > 3 || pontosComputador > 3){
	  piscaLed(pontosJogador, ledsJogador);
      piscaLed(pontosComputador, ledsComputador);
      pontosComputador = 0;
      pontosJogador = 0;
      for(int i = 0; i < 3; i++){
        digitalWrite(ledsJogador[i], LOW);
        digitalWrite(ledsComputador[i], LOW);
      }
    }
  }

  delay(10);
}

int charParaInt(char c){
	return c - '0';
}

void piscaLed(int pts, int v[]){
      if(pts > 3){
        for(int t = 0; t < 5; t++){
          for(int i = 0; i < 3; i++){
            digitalWrite(v[i], LOW);
          }
          delay(300);
          for(int i = 0; i < 3; i++){
            digitalWrite(v[i], HIGH);
          }
          delay(300);
        }
      }
}
