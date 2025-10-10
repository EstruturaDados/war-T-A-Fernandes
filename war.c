#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Biblioteca padão: Funções de alocação de memória
#include <time.h> // Biblioteca de tempo: Funções para data, hora e inicialização de aleatóriedade (srand)

// ==============================
// Estrutura do Território
// ==============================
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// ==============================
// Função: cadastrarTerritorios
// Cadastra os territórios dinamicamente
// ==============================
void cadastrarTerritorios(Territorio* mapa, int qtd){
    for (int i = 0; i < qtd; i++){
        printf("\n--- Cadastro de Território %d---\n",i + i);

        printf("Nome do Território: ");
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = 0;

        printf("Cor do exército: ");
        fgets(mapa[i].cor, sizeof(mapa[i].cor), stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = 0;

        printf("Número de Tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar();
    }
}

// ==============================
// Função: exibirMapa
// Exibe o estado atual do território
// ==============================
void exibirMapa(Territorio* mapa, int qtd){
    printf("\n==============================\n");
    printf("     ESTADO ATUAL DO MAPA\n");
    printf("==============================\n");
    for (int i = 0; i < qtd; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("   Nome: %s\n", mapa[i].nome);
        printf("   Cor: %s\n", mapa[i].cor);
        printf("   Tropas: %s\n", mapa[i].tropas);
    }
}

// ==============================
// Função: atacar
// imula um ataque entre dois território
// ==============================
void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\n⚠️  Você não pode atacar um território da sua propria cor!\n");
        return;
    }

    if (atacante->tropas < 2){
        printf("\n⚠️  O território atacante precisa ter pelo menos 2 tropas!\n");
        return;
    }

    printf("\n🎲 Rolando os dados...\n");
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("  Dado do atacante: %d\n", dadoAtacante);
    printf("  Dado defensor: %d\n", dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("\n🔥 O atacante venceu a batalha!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2; // Metade das tropas passam
        atacante->tropas /=2;                    // Metade permanecem
    } else {
        printf("\n🛡️ O defensor resistiu ao ataque.\n");
        atacante->tropas -= 1; // atacante perde uma tropa
    }
}

// ==============================
// Função: liberarMemoria
// Libera os espaço alocado dinamicamente
// ==============================
void liberarMemoria(Territorio* mapa){
    free(mapa);
}

// ==============================
// Função: Principal
// ==============================
int main() {
    srand(time(NULL)); // Aleatóriedade

    int qtd;
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &qtd);
    getchar();

    // Alocação do vetor de territórios
    Territorio* mapa = (Territorio*) calloc(qtd, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar mamória!\n");
        return 1;
    }
    
    // Cadastro
    cadastrarTerritorios(mapa, qtd);

    int opcao;
    do {
        exibirMapa(mapa, qtd);
        printf("\nO que deseja fazer?\n");
        printf("1 - Atacar\n");
        printf("2 - sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 1) {
            int iAtacante, iDefensor;

            printf("\nEscolha o número do território atacante: ");
            scanf("%d", &iAtacante);
            getchar();

            printf("Escolha o número do território defensor: ");
            scanf("%d", &iDefensor);
            getchar();

            if (iAtacante < 1 || iAtacante > qtd || iDefensor < 1 || iDefensor > qtd) {
                printf("\n⚠️ Índices invalidos!\n");
            } else {
                atacar(&mapa[iAtacante - 1], &mapa[iDefensor - 1]);
            }
        }
    } while (opcao != 2);
    liberarMemoria(mapa);
    printf("\nMemória liberada. Fim de Jogo!\n");
    
    return 0;
}
