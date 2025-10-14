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
