#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.h"

Estrada *getEstrada(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        return NULL;
    }

    Estrada *estrada = (Estrada *)malloc(sizeof(Estrada));
    if (estrada == NULL) {
        fclose(arquivo);
        return NULL;
    }

    fscanf(arquivo, "%d", &estrada->T);
    fscanf(arquivo, "%d", &estrada->N);

    estrada->C = (Cidade *)malloc(estrada->N * sizeof(Cidade));
    if (estrada->C == NULL) {
        fclose(arquivo);
        free(estrada);
        return NULL;
    }

    for (int i = 0; i < estrada->N; i++) {
        fscanf(arquivo, "%d %s", &estrada->C[i].Posicao, estrada->C[i].Nome);
    }

    fclose(arquivo);
    return estrada;
}

double calcularMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (estrada == NULL) {
        return -1.0;
    }

    double menorVizinhanca = estrada->T;

    for (int i = 0; i < estrada->N; i++) {
        int posicaoAtual = estrada->C[i].Posicao;

        if (i > 0) {
            int posicaoAnterior = estrada->C[i - 1].Posicao;
            double vizinhancaAtual = (posicaoAtual - posicaoAnterior) / 2.0;
            if (vizinhancaAtual < menorVizinhanca) {
                menorVizinhanca = vizinhancaAtual;
            }
        }

        if (i < estrada->N - 1) {
            int posicaoSeguinte = estrada->C[i + 1].Posicao;
            double vizinhancaAtual = (posicaoSeguinte - posicaoAtual) / 2.0;
            if (vizinhancaAtual < menorVizinhanca) {
                menorVizinhanca = vizinhancaAtual;
            }
        }
    }

    free(estrada->C);
    free(estrada);

    return menorVizinhanca;
}

char *cidadeMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (estrada == NULL) {
        return NULL;
    }

    double menorVizinhanca = estrada->T;
    char *cidadeMenor = NULL;

    for (int i = 0; i < estrada->N; i++) {
        int posicaoAtual = estrada->C[i].Posicao;
        double vizinhanca = estrada->T;

        if (i > 0) {
            int posicaoAnterior = estrada->C[i - 1].Posicao;
            vizinhanca = (posicaoAtual - posicaoAnterior) / 2.0;
        }

        if (i < estrada->N - 1) {
            int posicaoSeguinte = estrada->C[i + 1].Posicao;
            double vizinhancaSeguinte = (posicaoSeguinte - posicaoAtual) / 2.0;
            if (vizinhancaSeguinte < vizinhanca) {
                vizinhanca = vizinhancaSeguinte;
            }
        }

        if (vizinhanca < menorVizinhanca) {
            menorVizinhanca = vizinhanca;
            cidadeMenor = estrada->C[i].Nome;
        }
    }

    free(estrada->C);
    free(estrada);

    return cidadeMenor;
}
