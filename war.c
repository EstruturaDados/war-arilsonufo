#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ==============================
// Estrutura que representa um território no jogo WAR
// ==============================
typedef struct {
    char nome[30];   // Nome do território
    char cor[10];    // Cor do exército
    int tropas;      // Número de tropas
} Territorio;

// ==============================
// Protótipos das funções
// ==============================
Territorio* alocarTerritorios(int quantidade);
void cadastrarTerritorios(Territorio* territorios, int quantidade);
void exibirTerritorios(Territorio* territorios, int quantidade);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* territorios);
int escolherTerritorio(Territorio* territorios, int quantidade, const char* prompt);

// ==============================
// Função principal
// ==============================
int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    int qtdTerritorios;

    printf("==== WAR - Simulador de Batalhas ====\n");
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &qtdTerritorios);

    // Alocação dinâmica de territórios
    Territorio* territorios = alocarTerritorios(qtdTerritorios);
    if (territorios == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    // Cadastro inicial
    cadastrarTerritorios(territorios, qtdTerritorios);

    char continuar;
    do {
        printf("\n=== Mapa Atual ===\n");
        exibirTerritorios(territorios, qtdTerritorios);

        printf("\nSimular ataque:\n");

        // Escolher atacante e defensor com validações
        int idxAtacante = escolherTerritorio(territorios, qtdTerritorios, "Escolha o número do território ATACANTE: ");
        int idxDefensor = escolherTerritorio(territorios, qtdTerritorios, "Escolha o número do território DEFENSOR: ");

        // Validações
        if (idxAtacante == idxDefensor) {
            printf("O atacante e o defensor devem ser territórios diferentes.\n");
        } else if (strcmp(territorios[idxAtacante].cor, territorios[idxDefensor].cor) == 0) {
            printf("Você não pode atacar um território da mesma cor.\n");
        } else {
            atacar(&territorios[idxAtacante], &territorios[idxDefensor]);
        }

        printf("\nDeseja realizar outro ataque? (s/n): ");
        scanf(" %c", &continuar);

    } while (continuar == 's' || continuar == 'S');

    // Liberação da memória alocada
    liberarMemoria(territorios);

    printf("Jogo encerrado. Memória liberada com sucesso.\n");
    return 0;
}

// ==============================
// Função para alocar memória para os territórios
// ==============================
Territorio* alocarTerritorios(int quantidade) {
    return (Territorio*)calloc(quantidade, sizeof(Territorio));
}

// ==============================
// Função para cadastrar os territórios
// ==============================
void cadastrarTerritorios(Territorio* territorios, int quantidade) {
    printf("\n=== Cadastro de Territórios ===\n");

    for (int i = 0; i < quantidade; i++) {
        printf("\nTerritório %d:\n", i);
        printf("Nome: ");
        scanf(" %[^\n]", territorios[i].nome);
        printf("Cor do exército (ex: vermelho, azul): ");
        scanf(" %9s", territorios[i].cor);
        printf("Número de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }
}

// ==============================
// Função para exibir todos os territórios
// ==============================
void exibirTerritorios(Territorio* territorios, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("[%d] Nome: %s | Cor: %s | Tropas: %d\n",
               i, territorios[i].nome, territorios[i].cor, territorios[i].tropas);
    }
}

// ==============================
// Função que simula um ataque entre dois territórios
// ==============================
void atacar(Territorio* atacante, Territorio* defensor) {
    if (atacante->tropas < 1) {
        printf("O território atacante não possui tropas suficientes para atacar.\n");
        return;
    }

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\nResultado da batalha:\n");
    printf("Dado do Atacante (%s): %d\n", atacante->nome, dadoAtacante);
    printf("Dado do Defensor (%s): %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        // Atacante vence
        printf("O atacante venceu! Conquistou o território.\n");

        // Transfere a cor e parte das tropas
        strcpy(defensor->cor, atacante->cor);

        // Novo número de tropas no defensor (metade do atacante)
        defensor->tropas = atacante->tropas / 2;
        if (defensor->tropas < 1) defensor->tropas = 1;

        // Atacante perde metade das tropas
        atacante->tropas = atacante->tropas / 2;

    } else {
        // Defensor vence
        printf("O defensor resistiu ao ataque.\n");
        atacante->tropas--;
    }
}

// ==============================
// Função para o usuário escolher um território válido
// ==============================
int escolherTerritorio(Territorio* territorios, int quantidade, const char* prompt) {
    int indice;

    while (1) {
        printf("\n");
        exibirTerritorios(territorios, quantidade);
        printf("%s", prompt);
        scanf("%d", &indice);

        if (indice >= 0 && indice < quantidade) {
            return indice;
        } else {
            printf("Índice inválido. Tente novamente.\n");
        }
    }
}

// ==============================
// Função para liberar memória alocada
// ==============================
void liberarMemoria(Territorio* territorios) {
    free(territorios);
}
