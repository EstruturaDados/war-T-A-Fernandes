#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ==============================
// Estrutura: Território
// Representa cada território do jogo com nome, cor atual, cor original,
// quantidade de tropas e tropas iniciais.
// ==============================
typedef struct {
    char nome[50];
    char cor[20];
    char corOriginal[20];
    int tropas;
    int tropasOriginais;
} Territorio;

// ==============================
// Estrutura: Missão
// Armazena a descrição textual de uma missão estratégica.
// ==============================
typedef struct {
    char descricao[100];
} Missao;

// ==============================
// Estrutura: Empréstimo Temporário
// Representa um empréstimo de tropas entre territórios da mesma cor.
// ==============================
typedef struct {
    int origem;
    int destino;
    int tropasEmprestadas;
    int ativo;
} EmprestimoTemporario;

// ==============================
// Função: cadastrarTerritorios
// Realiza o cadastro dos territórios, preenchendo nome, cor e tropas.
// ==============================
void cadastrarTerritorios(Territorio* mapa, int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("\n--- Cadastro de Território %d ---\n", i + 1);
        printf("Nome do Território: ");
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do Exército: ");
        fgets(mapa[i].cor, sizeof(mapa[i].cor), stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        strcpy(mapa[i].corOriginal, mapa[i].cor);
        printf("Quantidade de Tropas: ");
        scanf("%d", &mapa[i].tropas);
        while (getchar() != '\n');

        mapa[i].tropasOriginais = mapa[i].tropas;
    }
}

// ==============================
// Função: exibirMapa
// Exibe o estado atual do mapa.
// ==============================
void exibirMapa(Territorio* mapa, int qtd) {
    printf("\n==================== 🌍 ESTADO ATUAL DO MAPA ====================\n");
    for (int i = 0; i < qtd; i++) {
        printf("[%d] %-20s | Cor: %-10s | Tropas: %d\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("=================================================================\n");
}

// ==============================
// Função: emprestarTropas
// Permite empréstimo de tropas entre territórios da mesma cor.
// ==============================
EmprestimoTemporario emprestarTropas(Territorio* mapa, int qtd, const char* corJogador) {
    EmprestimoTemporario emp = { -1, -1, 0, 0 };

    int origem = -1, destino = -1;
    for (int i = 0; i < qtd; i++) {
        if (strcmp(mapa[i].cor, corJogador) == 0 && mapa[i].tropas > 1)
            origem = i;
        else if (strcmp(mapa[i].cor, corJogador) == 0 && mapa[i].tropas == 1)
            destino = i;
    }

    if (origem != -1 && destino != -1) {
        mapa[origem].tropas--;
        mapa[destino].tropas++;
        emp.origem = origem;
        emp.destino = destino;
        emp.tropasEmprestadas = 1;
        emp.ativo = 1;
        printf("✅ Tropas emprestadas de %s para %s\n", mapa[origem].nome, mapa[destino].nome);
    } else {
        printf("⚠️ Não há territórios elegíveis para empréstimo.\n");
    }

    return emp;
}

// ==============================
// Função: resolverEmprestimo
// Devolve as tropas após o ataque.
// ==============================
void resolverEmprestimo(Territorio* mapa, EmprestimoTemporario* emp, int atacanteVenceu) {
    if (!emp->ativo) return;

    if (atacanteVenceu) {
        mapa[emp->destino].tropas -= emp->tropasEmprestadas;
        mapa[emp->origem].tropas += emp->tropasEmprestadas;
        printf("🔁 Tropas retornaram para %s após vitória.\n", mapa[emp->origem].nome);
    } else {
        mapa[emp->destino].tropas -= emp->tropasEmprestadas;
        if (mapa[emp->destino].tropas <= 0)
            printf("⚠️ %s ficou vazio e foi conquistado!\n", mapa[emp->destino].nome);
    }

    emp->ativo = 0;
}
