#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Struct para armazenar pontos
typedef struct {
    float coordenadaX;
    float coordenadaY;
} Ponto;

// Função para ler os vértices do arquivo
Ponto *lerPontosDoArquivo(const char *nomeArquivo, int *numPontos) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    fscanf(arquivo, "%d", numPontos);

    Ponto *pontos = (Ponto *)malloc(*numPontos * sizeof(Ponto));
    if (pontos == NULL) {
        printf("Erro de alocação de memória.\n");
        fclose(arquivo);
        return NULL;
    }

    for (int i = 0; i < *numPontos; i++) {
        fscanf(arquivo, "%f %f", &pontos[i].coordenadaX, &pontos[i].coordenadaY);
    }

    fclose(arquivo);
    return pontos;
}

// Função para calcular a área de um triângulo
float calcularAreaTriangulo(Ponto A, Ponto B, Ponto C) {
    return 0.5f * ((A.coordenadaX * (B.coordenadaY - C.coordenadaY)) + (B.coordenadaX * (C.coordenadaY - A.coordenadaY)) + (C.coordenadaX * (A.coordenadaY - B.coordenadaY)));
}

// Função para calcular a área de um polígono
float calcularAreaPoligono(Ponto pontos[], int numPontos) {
    float area = 0.0f;
    int j;

    for (int i = 0; i < numPontos; i++) {
        j = (i + 1) % numPontos;
        area += (pontos[i].coordenadaX * pontos[j].coordenadaY) - (pontos[j].coordenadaX * pontos[i].coordenadaY);
    }

    area = area / 2.0f;
    if (area < 0) {
        area = -area;
    }

    return area;
}

int main() {
    int numPontos;
    Ponto *pontos;
    float area;

    pontos = lerPontosDoArquivo("vertices.txt", &numPontos);
    if (pontos == NULL) {
        return 1;
    }

    area = calcularAreaPoligono(pontos, numPontos);
    printf("A área do polígono é: %.2f\n", area);

    free(pontos);
    return 0;
}
