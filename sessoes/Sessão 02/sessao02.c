#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define PEDRA 0
#define PAPEL 1 
#define TESOURA 2

/*
Nesta primeira versão, vamos traduzir as regras da forma mais direta possível. 
Usaremos ifs aninhados (um dentro do outro). A lógica é: primeiro, verificamos a escolha do jogador. 
Depois, dentro de cada verificação, analisamos todas as possibilidades para a escolha do computador.
*/
void versao_01() {
    int jogador, computador;
    printf("Escolha: 0 (Pedra), 1 (Papel), 2 (Tesoura): ");
    scanf("%d", &jogador);
    computador = rand() % 3; // Gera um número aleatório entre 0 e 2
    printf("Computador escolheu: %d\n", computador);
    if (jogador == PEDRA) {
        if (computador == PEDRA) {
            printf("Empate!\n");
        } else if (computador == PAPEL) {
            printf("Computador vence!\n");
        } else { // computador == TESOURA
            printf("Jogador vence!\n");
        }
    } else if (jogador == PAPEL) {
        if (computador == PEDRA) {
            printf("Jogador vence!\n");
        } else if (computador == PAPEL) {
            printf("Empate!\n");
        } else { // computador == TESOURA
            printf("Computador vence!\n");
        }
    } else { // jogador == TESOURA
        if (computador == PEDRA) {
            printf("Computador vence!\n");
        } else if (computador == PAPEL) {
            printf("Jogador vence!\n");
        } else { // computador == TESOURA
            printf("Empate!\n");
        }
    }
}

/*
Vamos refatorar o código para reduzir o número de estruturas if/else a partir do uso de operadores lógicos 
(&& para"E", || para "OU"). A ideia é agrupar todas as condições de vitória do jogador em uma única expressão.
*/
void versao_02() {
    int jogador, computador;
    printf("Escolha: 0 (Pedra), 1 (Papel), 2 (Tesoura): ");
    scanf("%d", &jogador);
    computador = rand() % 3; // Gera um número aleatório entre 0 e 2
    printf("Computador escolheu: %d\n", computador);
    if (jogador == computador) {
        printf("Empate!\n");
    } else if ((jogador == PEDRA && computador == TESOURA) ||
               (jogador == PAPEL && computador == PEDRA) ||
               (jogador == TESOURA && computador == PAPEL)) {
        printf("Jogador vence!\n");
    } else {
        printf("Computador vence!\n");
    }
}

/*
Para que o jogo possa ser jogado várias vezes sem precisar reiniciar o programa, vamos colocar toda a lógica dentro de um laço de repetição. 
O laço do-while é ideal aqui, pois garante que o jogo seja executado pelo menos uma vez antes de perguntar se o jogador quer continuar.
*/
void versao_03(){
    int jogador, computador;
    char jogar_novamente;
    do {
        printf("Escolha: 0 (Pedra), 1 (Papel), 2 (Tesoura): ");
        scanf("%d", &jogador);
        computador = rand() % 3; // Gera um número aleatório entre 0 e 2
        printf("Computador escolheu: %d\n", computador);
        if (jogador == computador) {
            printf("Empate!\n");
        } else if ((jogador == PEDRA && computador == TESOURA) ||
                   (jogador == PAPEL && computador == PEDRA) ||
                   (jogador == TESOURA && computador == PAPEL)) {
            printf("Jogador vence!\n");
        } else {
            printf("Computador vence!\n");
        }
        printf("Quer jogar novamente? (s/n): ");
        scanf(" %c", &jogar_novamente);
    } while (jogar_novamente == 's' || jogar_novamente == 'S');

}


int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios
    printf("Versão 01:\n");
    versao_01();
    printf("\nVersão 02:\n");
    versao_02();
    printf("\nVersão 03:\n");
    versao_03();
    return 0;
}