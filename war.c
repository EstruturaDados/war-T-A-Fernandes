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

int main() {

    // Vetor que ira armazenar 5 territórios
    Territorio territorios[5];

    // Entrada de dados
    printf("==============================================================\n");
    printf("Vamos cadastrar os 5 territórios iniciais do nosso mundo.\n");
    printf("==============================================================\n");
    for(int i = 0; i < 5; i++) {
        printf("\n--- Cadastranto Território %d ---\n", i + 1);

        // Lendo o nome do território
        printf("Nome do território: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin); // fgets permite ler strings com espaços
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = 0; // Remove o '\n' final da string

        // Lendo a cor do exército
        printf("Cor do exército: ");
        fgets(territorios[i].cor, sizeof(territorios[i].cor), stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = 0; 

        // Lendo número de tropas
        printf("Número de tropas: ");
        scanf("%d", &territorios[i].tropas);
        getchar(); // Limpa o '\n' deixado pelo scanf
    }

    // Exibição dos dados
    printf("\n==================================\n");
    printf("Mapa do Mundo - ESTADO ATUAL\n");
    printf("==================================\n");

    for(int i = 0; i < 5; i++) {
        printf("\nTerritório %d\n", i + 1); 
        printf("   - Nome: %s\n", territorios[i].nome);
        printf("   - Dominado por: %s\n", territorios[i].cor);
        printf("   - Tropas: %d\n", territorios[i].tropas);
    }

    return 0;
}