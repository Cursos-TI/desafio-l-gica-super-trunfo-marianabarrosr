#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TERRITORIOS 5

// Estrutura que representa um território
typedef struct {
    char nome[20];
    char cor[20]; // Exército
    int tropas;
} Territorio;

// Função para mostrar o mapa do mundo
void mostrarMapa(Territorio territorios[], int numTerritorios) {
    printf("\n================ MAPA DO MUNDO ================\n");
    for (int i = 0; i < numTerritorios; i++) {
        printf("%d. %-10s (Exercito: %-8s , Tropas: %d)\n",
               i + 1, territorios[i].nome, territorios[i].cor, territorios[i].tropas);
    }
    printf("===============================================\n");
}

// Função para realizar um ataque
void atacar(Territorio *atacante, Territorio *defensor, Territorio territorios[], int numTerritorios) {
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n--- RESULTADO DA BATALHA ---\n");
    printf("Ataque (%s - %s): %d | Defesa (%s - %s): %d\n",
           atacante->nome, atacante->cor, dadoAtacante,
           defensor->nome, defensor->cor, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("VITORIA DO ATAQUE! O defensor perdeu 1 tropa.\n");
        defensor->tropas -= 1;

        if (defensor->tropas <= 0) {
            printf("%s conquistou o território %s!\n",
                   atacante->cor, defensor->nome);
            defensor->tropas = atacante->tropas / 2;
            atacante->tropas /= 2;
            strcpy(defensor->cor, atacante->cor);
        }
    } else {
        printf("VITORIA DA DEFESA! O atacante perdeu 1 tropa.\n");
        atacante->tropas -= 1;
    }

    // Espera Enter
    printf("\nPressione Enter para continuar...");
    getchar();

    // Mostra o mapa atualizado
    mostrarMapa(territorios, numTerritorios);
}

// Função para verificar se a missão foi concluída
int verificarMissao(Territorio territorios[], int numTerritorios, char alvoCor[]) {
    for (int i = 0; i < numTerritorios; i++) {
        if (strcmp(territorios[i].cor, alvoCor) == 0) {
            return 0; // ainda existe exército inimigo
        }
    }
    return 1; // missão cumprida
}

int main() {
    srand(time(NULL));
    Territorio territorios[MAX_TERRITORIOS];
    int numTerritorios = 5;

    printf("=============================================================\n");
    printf("  WAR ESTRUTURADO - CADASTRO DE TERRITORIOS \n");
    printf("=============================================================\n");

    // Cadastro inicial dos territórios
    printf("======= CADASTRO DE TERRITORIOS =======\n");
    for (int i = 0; i < numTerritorios; i++) {
        printf("\nNome do territorio %d: ", i + 1);
        scanf(" %[^\n]", territorios[i].nome);

        printf("Cor do exercito: ");
        scanf(" %[^\n]", territorios[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);

        getchar(); // limpa o ENTER que sobra
    }

    // Sorteia missão: um exercito contra outro
    int idxJogador = rand() % numTerritorios;
    char jogadorCor[20];
    strcpy(jogadorCor, territorios[idxJogador].cor);

    int idxAlvo;
    do {
        idxAlvo = rand() % numTerritorios;
    } while (strcmp(territorios[idxAlvo].cor, jogadorCor) == 0);

    char alvoCor[20];
    strcpy(alvoCor, territorios[idxAlvo].cor);

    // Exibe mapa inicial
    mostrarMapa(territorios, numTerritorios);

    printf("\n--- SUA MISSAO (Exercito %s) ---\n", jogadorCor);
    printf("Destruir o exercito %s.\n", alvoCor);

    // Loop principal
    int opcao;
    do {
        printf("\n--- MENU DE ACOES ---\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missao\n");
        printf("0 - Sair\n");
        printf("Escolha sua acao: ");
        scanf("%d", &opcao);

        getchar(); // limpa o ENTER

        if (opcao == 1) {
            int atq, def;
            printf("\nEscolha o territorio ATACANTE: ");
            scanf("%d", &atq);
            printf("Escolha o territorio DEFENSOR: ");
            scanf("%d", &def);
            getchar();

            if (atq < 1 || atq > numTerritorios || def < 1 || def > numTerritorios || atq == def) {
                printf("Escolha invalida!\n");
                continue;
            }

            atacar(&territorios[atq - 1], &territorios[def - 1], territorios, numTerritorios);
        }
        else if (opcao == 2) {
            if (verificarMissao(territorios, numTerritorios, alvoCor)) {
                printf("\nParabens! O exercito %s cumpriu sua missao: destruir o exercito %s!\n",
                       jogadorCor, alvoCor);
                break;
            } else {
                printf("\nMissao ainda nao concluida. Ainda existem territorios do exercito %s!\n", alvoCor);
            }
        }
    } while (opcao != 0);

    printf("\nEncerrando o jogo...\n");
    printf("Memoria liberada com sucesso.\n");

    return 0;
}
