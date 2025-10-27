#include <stdio.h>
#include <string.h>

#define MAX_TERRITORIOS 5
#define TAM_NOME 50
#define TAM_COR 30

// Estrutura que representa um território
typedef struct {
    char nome[TAM_NOME];
    char corExercito[TAM_COR];
    int numeroTropas;
} Territorio;

int main() {
    Territorio mapa[MAX_TERRITORIOS];

    // Lista de cores disponíveis
    char coresDisponiveis[5][TAM_COR] = {
        "Vermelho",
        "Azul",
        "Verde",
        "Amarelo",
        "Preto"
    };

    printf("Bem-vindo ao sistema de cadastro de territórios!\n");
    printf("Prepare-se para montar seu próprio mapa de estratégia.\n\n");

    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("Vamos cadastrar o território número %d.\n", i + 1);

        // Nome do território
        printf("Digite o nome do território: ");
        fgets(mapa[i].nome, TAM_NOME, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        // Escolha da cor do exército
        printf("Escolha a cor do exército dominante para esse território:\n");
        for (int j = 0; j < 5; j++) {
            printf("  %d - %s\n", j + 1, coresDisponiveis[j]);
        }

        int escolhaCor;
        do {
            printf("Digite o número correspondente à cor desejada: ");
            scanf("%d", &escolhaCor);
            if (escolhaCor < 1 || escolhaCor > 5) {
                printf("Ops! Essa opção não existe. Tente novamente.\n");
            }
        } while (escolhaCor < 1 || escolhaCor > 5);
        strcpy(mapa[i].corExercito, coresDisponiveis[escolhaCor - 1]);
        getchar(); // Limpa o \n do buffer

        // Número de tropas
        printf("Quantas tropas estão posicionadas nesse território? ");
        scanf("%d", &mapa[i].numeroTropas);
        getchar();

        printf("Território cadastrado com sucesso! Vamos para o próximo.\n\n");
    }

    // Exibição dos dados cadastrados
    printf("Cadastro completo! Aqui está o estado atual do seu mapa:\n");
    printf("--------------------------------------------------------\n");

    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor do Exército: %s\n", mapa[i].corExercito);
        printf("Número de Tropas: %d\n", mapa[i].numeroTropas);
        printf("--------------------------------------------------------\n");
    }

    printf("Tudo pronto! Seu mapa está armado e seus territórios estão prontos para qualquer desafio.\n");

    return 0;
}