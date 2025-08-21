#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TERRITORIOS 5

// Definição da struct Territorio
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};
typedef struct Territorio Territorio;

// Função para exibir o mapa atual
void mostrarMapa(Territorio *territorios, int n) {
    printf("\n==============================\n");
    printf(" MAPA DO MUNDO - ESTADO ATUAL \n");
    printf("==============================\n");
    for (int i = 0; i < n; i++) {
        printf("%d. %s (Exército %s, Tropas: %d)\n",
               i + 1,
               territorios[i].nome,
               territorios[i].cor,
               territorios[i].tropas);
    }
    printf("==============================\n");
}

// Função de ataque
void atacar(Territorio *atacante, Territorio *defensor) {
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n--- BATALHA ---\n");
    printf("%s (Exército %s, Tropas: %d) ATACA %s (Exército %s, Tropas: %d)\n",
           atacante->nome, atacante->cor, atacante->tropas,
           defensor->nome, defensor->cor, defensor->tropas);

    printf("Dado Atacante: %d | Dado Defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("Resultado: Vitória do Atacante!\n");
        defensor->tropas -= 1;

        if (defensor->tropas <= 0) {
            printf("%s conquistou o território %s!\n",
                   atacante->nome, defensor->nome);
            defensor->tropas = atacante->tropas / 2;
            atacante->tropas /= 2;
            strcpy(defensor->cor, atacante->cor);
        }
    } else {
        printf("Resultado: Defesa bem-sucedida!\n");
        atacante->tropas -= 1;
    }

    printf("\nPressione ENTER para continuar...");
    getchar();
}

int main() {
    srand(time(NULL));
    Territorio *territorios = (Territorio *)calloc(MAX_TERRITORIOS, sizeof(Territorio));

    printf("=============================================================\n");
    printf("  WAR ESTRUTURADO - CADASTRO DE TERRITORIOS \n");
    printf("=============================================================\n");

    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("\n==============================\n");
        printf("   Cadastrando Território %d\n", i + 1);
        printf("==============================\n");

        printf("Nome do Território: ");
        scanf(" %[^\n]", territorios[i].nome);

        printf("Cor do Exército: ");
        scanf(" %[^\n]", territorios[i].cor);

        printf("Número de Tropas: ");
        scanf("%d", &territorios[i].tropas);

        getchar(); // limpa o ENTER do buffer
    }

    // Mostrar mapa inicial
    mostrarMapa(territorios, MAX_TERRITORIOS);
    printf("\nPressione ENTER para iniciar a fase de ataque...");
    getchar();

    // Loop de ataques
    while (1) {
        int idxAtacante, idxDefensor;

        mostrarMapa(territorios, MAX_TERRITORIOS);

        printf("\nEscolha o território atacante (0 para sair): ");
        scanf("%d", &idxAtacante);
        getchar();
        if (idxAtacante == 0) break;

        printf("Escolha o território defensor: ");
        scanf("%d", &idxDefensor);
        getchar();

        if (idxAtacante < 1 || idxAtacante > MAX_TERRITORIOS ||
            idxDefensor < 1 || idxDefensor > MAX_TERRITORIOS ||
            idxAtacante == idxDefensor) {
            printf("Escolhas inválidas! Tente novamente.\n");
            continue;
        }

        atacar(&territorios[idxAtacante - 1], &territorios[idxDefensor - 1]);
    }

    free(territorios);
    printf("\nJogo encerrado.\n");
    return 0;
}
