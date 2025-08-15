#include <stdio.h>
#include <string.h>

// Definição da struct Territorio
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

// Função para limpar o buffer de entrada
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    struct Territorio territorios[5];

    // Mensagem de introdução
    printf("=============================================================\n");
    printf("Vamos cadastrar os 5 territórios iniciais do nosso mundo\n");
    printf("=============================================================\n");

    // Cadastro dos territórios
    for (int i = 0; i < 5; i++) {
        printf("\n--- Cadastrando o território %d ---\n", i + 1);

        printf("Nome do território: ");
        scanf(" %[^\n]", territorios[i].nome);

        printf("Cor do exército (ex: azul, verde): ");
        scanf(" %s", territorios[i].cor);

        printf("Número de tropas: ");
        scanf("%d", &territorios[i].tropas);
        limparBufferEntrada(); // Evita problemas na próxima entrada
    }

    // Exibição dos dados
    printf("\n=== DADOS DOS TERRITÓRIOS ===\n");
    for (int i = 0; i < 5; i++) {
        printf("\nTERRITÓRIO %d\n", i + 1);
        printf("- Nome: %s\n", territorios[i].nome);
        printf("- Dominado por: Exército %s\n", territorios[i].cor);
        printf("- Tropas: %d\n", territorios[i].tropas);
    }

    return 0;
}
