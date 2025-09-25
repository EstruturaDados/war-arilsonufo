#include <stdio.h>
#include <string.h>

// Definição da struct Territorio
// Armazena nome, cor do exército e quantidade de tropas
typedef struct {
    char nome[30];   // Nome do território
    char cor[10];    // Cor do exército associado ao território
    int tropas;      // Quantidade de tropas no território
} Territorio;

int main() {
    // Declaração de vetor de structs para armazenar 5 territórios
    Territorio territorios[5];

    // Entrada de dados via terminal
    for (int i = 0; i < 5; i++) {
        printf("\nCadastro do território %d:\n", i + 1);

        // Leitura do nome do território
        printf("Digite o nome do território: ");
        scanf(" %[^\n]", territorios[i].nome); // Lê até a quebra de linha

        // Leitura da cor do exército
        printf("Digite a cor do exército: ");
        scanf(" %[^\n]", territorios[i].cor);

        // Leitura da quantidade de tropas
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    // Exibição dos dados cadastrados
    printf("\n=== Territórios cadastrados ===\n");
    for (int i = 0; i < 5; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exército: %s\n", territorios[i].cor);
        printf("Quantidade de tropas: %d\n", territorios[i].tropas);
        printf("-----------------------------\n");
    }

    return 0;
}
