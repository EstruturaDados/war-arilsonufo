#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ==============================
// Estrutura que representa um território
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
int escolherTerritorio(Territorio* territorios, int quantidade, const char* prompt);
void atacar(Territorio* atacante, Territorio* defensor);
char* atribuirMissao(char* missoes[], int totalMissoes);
void exibirMissao(const char* missao);
int verificarMissao(const char* missao, Territorio* mapa, int tamanho);
void liberarMemoria(Territorio* territorios, char* missao);

// ==============================
// Função principal
// ==============================
int main() {
    srand(time(NULL)); // Inicializa gerador aleatório

    int qtdTerritorios;
    printf("==== WAR - Simulador de Batalhas ====\n");
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &qtdTerritorios);

    // Alocação dinâmica do mapa de territórios
    Territorio* territorios = alocarTerritorios(qtdTerritorios);
    if (territorios == NULL) {
        printf("Erro ao alocar memória para territórios.\n");
        return 1;
    }

    // Cadastro de territórios
    cadastrarTerritorios(territorios, qtdTerritorios);

    // Vetor de missões pré-definidas
    char* missoes[] = {
        "Conquistar 2 territórios inimigos",
        "Eliminar todos os territórios da cor azul",
        "Conquistar um território com mais de 5 tropas",
        "Eliminar todos os territórios da cor vermelha",
        "Ter pelo menos 3 territórios com mais de 3 tropas"
    };
    int totalMissoes = sizeof(missoes) / sizeof(missoes[0]);

    // Atribuição dinâmica da missão
    char* missaoJogador = atribuirMissao(missoes, totalMissoes);

    printf("\n==== Missão Secreta ====\n");
    exibirMissao(missaoJogador);

    char continuar;
    do {
        printf("\n=== Mapa Atual ===\n");
        exibirTerritorios(territorios, qtdTerritorios);

        printf("\nSimular ataque:\n");

        int idxAtacante = escolherTerritorio(territorios, qtdTerritorios, "Escolha o número do território ATACANTE: ");
        int idxDefensor = escolherTerritorio(territorios, qtdTerritorios, "Escolha o número do território DEFENSOR: ");

        // Validações
        if (idxAtacante == idxDefensor) {
            printf("O atacante e o defensor devem ser diferentes.\n");
        } else if (strcmp(territorios[idxAtacante].cor, territorios[idxDefensor].cor) == 0) {
            printf("Não é permitido atacar territórios da mesma cor.\n");
        } else {
            atacar(&territorios[idxAtacante], &territorios[idxDefensor]);
        }

        // Verifica se a missão foi cumprida
        if (verificarMissao(missaoJogador, territorios, qtdTerritorios)) {
            printf("\n🎉 MISSÃO CUMPRIDA! Você venceu o jogo! 🎉\n");
            break;
        }

        printf("\nDeseja realizar outro ataque? (s/n): ");
        scanf(" %c", &continuar);

    } while (continuar == 's' || continuar == 'S');

    liberarMemoria(territorios, missaoJogador);
    printf("Jogo encerrado. Memória liberada com sucesso.\n");

    return 0;
}

// ==============================
// Função para alocar dinamicamente o vetor de territórios
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
// Exibe os territórios no mapa atual
// ==============================
void exibirTerritorios(Territorio* territorios, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("[%d] Nome: %s | Cor: %s | Tropas: %d\n",
               i, territorios[i].nome, territorios[i].cor, territorios[i].tropas);
    }
}

// ==============================
// Escolha de território com validação
// ==============================
int escolherTerritorio(Territorio* territorios, int quantidade, const char* prompt) {
    int indice;
    while (1) {
        printf("%s", prompt);
        scanf("%d", &indice);
        if (indice >= 0 && indice < quantidade)
            return indice;
        printf("Índice inválido. Tente novamente.\n");
    }
}

// ==============================
// Simula um ataque entre dois territórios
// ==============================
void atacar(Territorio* atacante, Territorio* defensor) {
    if (atacante->tropas < 1) {
        printf("Tropas insuficientes para atacar.\n");
        return;
    }

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\nResultado do ataque:\n");
    printf("Atacante (%s) tirou: %d\n", atacante->nome, dadoAtacante);
    printf("Defensor (%s) tirou: %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("Vitória do atacante! Território conquistado.\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        if (defensor->tropas < 1) defensor->tropas = 1;
        atacante->tropas = atacante->tropas / 2;
    } else {
        printf("Defensor resistiu. Atacante perde 1 tropa.\n");
        atacante->tropas--;
    }
}

// ==============================
// Sorteia uma missão aleatória
// ==============================
char* atribuirMissao(char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    char* destino = (char*)malloc(strlen(missoes[indice]) + 1);
    strcpy(destino, missoes[indice]);
    return destino;
}

// ==============================
// Exibe a missão uma vez
// ==============================
void exibirMissao(const char* missao) {
    printf("🕵️ Missão Secreta: %s\n", missao);
}

// ==============================
// Verifica se a missão foi cumprida
// ==============================
int verificarMissao(const char* missao, Territorio* mapa, int tamanho) {
    if (strcmp(missao, "Conquistar 2 territórios inimigos") == 0) {
        int conquistados = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelho") == 0) { // Supondo que jogador é "vermelho"
                conquistados++;
            }
        }
        return conquistados >= 2;
    }

    if (strcmp(missao, "Eliminar todos os territórios da cor azul") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "azul") == 0)
                return 0;
        }
        return 1;
    }

    if (strcmp(missao, "Conquistar um território com mais de 5 tropas") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelho") == 0 && mapa[i].tropas > 5)
                return 1;
        }
        return 0;
    }

    if (strcmp(missao, "Eliminar todos os territórios da cor vermelha") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelho") == 0)
                return 0;
        }
        return 1;
    }

    if (strcmp(missao, "Ter pelo menos 3 territórios com mais de 3 tropas") == 0) {
        int count = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelho") == 0 && mapa[i].tropas > 3)
                count++;
        }
        return count >= 3;
    }

    return 0; // Missão desconhecida
}

// ==============================
// Libera toda a memória alocada
// ==============================
void liberarMemoria(Territorio* territorios, char* missao) {
    free(territorios);
    free(missao);
}
