#include <Servo.h>        // Inclui a biblioteca Servo, usada para controlar o motor servo
#define TRIG 11
#define ECHO 10

int sorteado;          	  // Declara variável global para armazenar valor aleatório
Servo servo;              // Cria um objeto servo para controlar o motor no pino 3

void setup()
{
  Serial.begin(9600);     // Inicia comunicação serial com o computador (monitor serial)
  sorteado = 0;           // Inicializa variável A com zero
  pinMode(TRIG, OUTPUT);    // Define o pino 11 como saída (trigger do sensor ultrassônico)
  pinMode(ECHO, INPUT);     // Define o pino 10 como entrada (echo do sensor ultrassônico)
  servo.attach(3);        // Conecta o servo motor ao pino digital (PWM) 3
}

void loop()
{
  // Verifica se a distância medida é menor que 20 cm
  if (verifica_distancia() < 20)
  {
    sorteado = random(0, 3);     // Sorteia um número aleatório entre 0 e 2
    switch (sorteado)             // Seleciona o movimento conforme o valor sorteado
    {
    case 0:
      servo.write(0);   // Gira o servo para 0 graus (representa "Pedra")
      Serial.println("Papel");  // Mostra "Pedra" no monitor serial
      break;
    case 1:
      servo.write(90);  // Gira o servo para 90 graus (representa "Papel")
      Serial.println("Pedra"); // Mostra "Papel" no monitor serial
      break;
    case 2:
      servo.write(180); // Gira o servo para 180 graus (representa "Tesoura")
      Serial.println("Tesoura"); // Mostra "Tesoura" no monitor serial
      break;
    }

    delay(1000);           // Espera 1 segundo antes da próxima medição
  }
  
}

// Função para medir a distância usando o sensor ultrassônico
float verifica_distancia()
{
  digitalWrite(TRIG, LOW);       // Garante que o trigger começa em nível baixo
  delayMicroseconds(2);        // Espera 2 microssegundos
  digitalWrite(TRIG, HIGH);      // Envia pulso de 10 µs no pino trigger
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);       // Termina o pulso

  // Mede o tempo de retorno do eco e converte para distância em centímetros
  // A função pulseIn() mede o tempo (em microssegundos) que o som levou para ir e voltar.
  // Dividindo por 58, obtemos a distância em centímetros.
  float distance = pulseIn(ECHO, HIGH) / 58.00; 
  Serial.println(distance);
  delay(10);                   // Pequeno atraso antes da próxima leitura
  return distance;             // Retorna a distância medida
}
