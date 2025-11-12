#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    // Em uma nova função ou modo de jogo
    char palavra_secreta[20];
    char display[20];
    char letras_tentadas_ia[20] = ""; // Letras que a IA já tentou
    int num_tentativas_ia = 0;
    int erros_ia = 0;
    int max_tentativas = 6;
    int acertou = 0;
    int enforcou = 0;
    int continuar = 1;

    printf("Modo Invertido! Informe a palavra secreta: (Maiusculo, sem acentos)\n");
    scanf("%s", palavra_secreta); // (Use fgets para palavras com espaço)

    // Inicializa o display
    int tamanho = strlen(palavra_secreta);
    for (int i = 0; i < tamanho; i++)
        display[i] = '_';
    display[tamanho] = '\0';

    while (!acertou && !enforcou && continuar)
    { // Laço do jogo
        printf("\n--- Rodada da IA ---\n");
        printf("Palavra: %s\n", display);
        printf("Tentativas da IA: %s\n", letras_tentadas_ia);
        printf("Erros: %d de %d\n", erros_ia, max_tentativas);
        printf("IA Pensando...\n");
        // 1. Engenharia de Prompt Dinâmica
        char prompt_ia[512];
        snprintf(prompt_ia, sizeof(prompt_ia),
                 "Voce eh um jogador de forca. "
                 "TAREFA: Adivinhe UMA letra. "
                 "ESTADO ATUAL: A palavra eh '%s'. "
                 "LETRAS JA TENTADAS: '%s'. "
                 "RESTRICOES: "
                 "1. Responda APENAS com a proxima letra que voce quer chutar."
                 "2. Nao repita letras '%s'. "
                 "3. Responda apenas UMA LETRA MAIUSCULA. "
                 "Qual sua proxima letra?",
                 display, letras_tentadas_ia, letras_tentadas_ia);

        // 2. Montar comando shell
        char comando_shell[768];
        // Lembre-se a atualizar o caminho para o bridge
        snprintf(comando_shell, sizeof(comando_shell), "py \"C:\\CAMINHO_PARA_O_BRIDGE\\gemini_bridge.py\" \"%s\"", prompt_ia);

        // 3. Chamar a IA para obter o chute
        FILE *pipe = popen(comando_shell, "r");
        if (pipe == NULL)
        {
            printf("Erro ao executar a ponte Python!\n");
            return 1;
        }

        char buffer_chute_ia[512];
        fgets(buffer_chute_ia, sizeof(buffer_chute_ia), pipe);
        pclose(pipe);

        char chute_ia = buffer_chute_ia[0]; // Pegamos só a primeira letra
        printf("IA chutou a letra: %c\n", chute_ia);

        // Adiciona o chute da IA ao histórico de letras tentadas
        letras_tentadas_ia[num_tentativas_ia] = chute_ia;
        num_tentativas_ia++;
        letras_tentadas_ia[num_tentativas_ia] = '\0';

        // 4. Processar o chute (lógica normal da forca)


        // 5. Verificar se a IA quer continuar
        printf("Deseja continuar jogando? (0/1): \n"); 
        scanf("%d", &continuar);
    }

    return 0;
}