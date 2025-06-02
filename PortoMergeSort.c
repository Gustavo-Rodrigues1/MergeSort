#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    char codigo[15];
    char cnpj[20];
    int peso;
    int margemPeso;
    int diferencaPeso;
} Containers;

void mergeCodigo(Containers *vetor, int inicio, int meio, int fim) {
    Containers *aux = (Containers *)malloc((fim - inicio + 1) * sizeof(Containers));
    if (aux == NULL) {
        fprintf(stderr, "Falha ao alocar memória para mergeCodigo.\n");
        exit(EXIT_FAILURE);
    }

    int primeiroInicio = inicio, segundoInicio = meio + 1, posicaoAux = 0;
    while (primeiroInicio <= meio && segundoInicio <= fim) {
        if (strcmp(vetor[primeiroInicio].codigo, vetor[segundoInicio].codigo) <= 0) {
            aux[posicaoAux++] = vetor[primeiroInicio++];
        } else {
            aux[posicaoAux++] = vetor[segundoInicio++];
        }
    }
    while (primeiroInicio <= meio) {
        aux[posicaoAux++] = vetor[primeiroInicio++];
    }
    while (segundoInicio <= fim) {
        aux[posicaoAux++] = vetor[segundoInicio++];
    }
    for (primeiroInicio = inicio, posicaoAux = 0; primeiroInicio <= fim; primeiroInicio++, posicaoAux++) {
        vetor[primeiroInicio] = aux[posicaoAux];
    }
    free(aux);
}

void mergeSortCodigo(Containers *vetor, int inicio, int fim) {
    if (inicio < fim) {
        int meio = (inicio + fim) / 2;
        mergeSortCodigo(vetor, inicio, meio);
        mergeSortCodigo(vetor, meio + 1, fim);
        mergeCodigo(vetor, inicio, meio, fim);
    }
}

void merge(Containers *vetor, int inicio, int meio, int fim) {
    Containers *aux = (Containers *)malloc((fim - inicio + 1) * sizeof(Containers));
    if (aux == NULL) {
        fprintf(stderr, "Falha ao alocar memória para merge.\n");
        exit(EXIT_FAILURE);
    }

    int primeiroInicio = inicio, segundoInicio = meio + 1, posicaoAux = 0;
    while (primeiroInicio <= meio && segundoInicio <= fim) {
        if (vetor[primeiroInicio].margemPeso >= vetor[segundoInicio].margemPeso) {
            aux[posicaoAux++] = vetor[primeiroInicio++];
        } else {
            aux[posicaoAux++] = vetor[segundoInicio++];
        }
    }
    while (primeiroInicio <= meio) {
        aux[posicaoAux++] = vetor[primeiroInicio++];
    }
    while (segundoInicio <= fim) {
        aux[posicaoAux++] = vetor[segundoInicio++];
    }
    for (primeiroInicio = inicio, posicaoAux = 0; primeiroInicio <= fim; primeiroInicio++, posicaoAux++) {
        vetor[primeiroInicio] = aux[posicaoAux];
    }
    free(aux);
}

void mergeSort(Containers *vetor, int inicio, int fim) {
    if (inicio < fim) {
        int meio = (inicio + fim) / 2;
        mergeSort(vetor, inicio, meio);
        mergeSort(vetor, meio + 1, fim);
        merge(vetor, inicio, meio, fim);
    }
}

int bbinaria(char *chave, int inicio, int fim, Containers *vetor) {
    if (fim < inicio) {
        return -1;
    } else {
        int meio = (inicio + fim) / 2;
        if (strcmp(vetor[meio].codigo, chave) == 0) {
            return meio;
        } else {
            if (strcmp(vetor[meio].codigo, chave) < 0) {
                return bbinaria(chave, meio + 1, fim, vetor);
            } else {
                return bbinaria(chave, inicio, meio - 1, vetor);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");

    if (input == NULL || output == NULL) {
        fprintf(stderr, "Falha ao abrir o arquivo!\n");
        return EXIT_FAILURE;
    }

    int numeroDeContainersCadastrados, numeroDeContainersSelecionados;

    if (fscanf(input, "%d", &numeroDeContainersCadastrados) != 1) {
        fprintf(stderr, "Erro ao ler o número de containers cadastrados.\n");
        fclose(input);
        fclose(output);
        return EXIT_FAILURE;
    }

    Containers *vetorDeContainersCadastrados = (Containers *)malloc(numeroDeContainersCadastrados * sizeof(Containers));
    if (vetorDeContainersCadastrados == NULL) {
        fprintf(stderr, "Falha ao alocar memória para vetorDeContainersCadastrados.\n");
        fclose(input);
        fclose(output);
        return EXIT_FAILURE;
    }

    for (int contador = 0; contador < numeroDeContainersCadastrados; contador++) {
        if (fscanf(input, "%s %s %d", vetorDeContainersCadastrados[contador].codigo, vetorDeContainersCadastrados[contador].cnpj, &vetorDeContainersCadastrados[contador].peso) != 3) {
            fprintf(stderr, "Erro ao ler os dados do container cadastrado.\n");
            free(vetorDeContainersCadastrados);
            fclose(input);
            fclose(output);
            return EXIT_FAILURE;
        }
    }

    if (fscanf(input, "%d", &numeroDeContainersSelecionados) != 1) {
        fprintf(stderr, "Erro ao ler o número de containers selecionados.\n");
        free(vetorDeContainersCadastrados);
        fclose(input);
        fclose(output);
        return EXIT_FAILURE;
    }

    Containers *vetorDeContainersSelecionados = (Containers *)malloc(numeroDeContainersSelecionados * sizeof(Containers));
    if (vetorDeContainersSelecionados == NULL) {
        fprintf(stderr, "Falha ao alocar memória para vetorDeContainersSelecionados.\n");
        free(vetorDeContainersCadastrados);
        fclose(input);
        fclose(output);
        return EXIT_FAILURE;
    }

    for (int contador = 0; contador < numeroDeContainersSelecionados; contador++) {
        if (fscanf(input, "%s %s %d", vetorDeContainersSelecionados[contador].codigo, vetorDeContainersSelecionados[contador].cnpj, &vetorDeContainersSelecionados[contador].peso) != 3) {
            fprintf(stderr, "Erro ao ler os dados do container selecionado.\n");
            free(vetorDeContainersCadastrados);
            free(vetorDeContainersSelecionados);
            fclose(input);
            fclose(output);
            return EXIT_FAILURE;
        }
    }

    mergeSortCodigo(vetorDeContainersSelecionados, 0, numeroDeContainersSelecionados - 1);

    int numeroDeContainersComMargem = 0;
    Containers *vetorDeContainersComMargem = (Containers *)malloc(numeroDeContainersCadastrados * sizeof(Containers));
    if (vetorDeContainersComMargem == NULL) {
        fprintf(stderr, "Falha ao alocar memória para vetorDeContainersComMargem.\n");
        free(vetorDeContainersCadastrados);
        free(vetorDeContainersSelecionados);
        fclose(input);
        fclose(output);
        return EXIT_FAILURE;
    }

    for (int contador = 0; contador < numeroDeContainersCadastrados; contador++) {
        int posSelecionado = bbinaria(vetorDeContainersCadastrados[contador].codigo, 0, numeroDeContainersSelecionados - 1, vetorDeContainersSelecionados);
        if (posSelecionado != -1) {
            if (vetorDeContainersCadastrados[contador].peso != 0) {
                double diferencaPercentual = round(fabs((vetorDeContainersCadastrados[contador].peso - vetorDeContainersSelecionados[posSelecionado].peso) * 100.0 / vetorDeContainersCadastrados[contador].peso));
                if (strcmp(vetorDeContainersCadastrados[contador].cnpj, vetorDeContainersSelecionados[posSelecionado].cnpj) != 0) {
                    fprintf(output, "%s:%s<->%s\n", vetorDeContainersCadastrados[contador].codigo, vetorDeContainersCadastrados[contador].cnpj, vetorDeContainersSelecionados[posSelecionado].cnpj);
                }
                if (diferencaPercentual > 10) {
                    vetorDeContainersComMargem[numeroDeContainersComMargem] = vetorDeContainersCadastrados[contador];
                    vetorDeContainersComMargem[numeroDeContainersComMargem].margemPeso = (int)diferencaPercentual;
                    vetorDeContainersComMargem[numeroDeContainersComMargem].diferencaPeso = abs(vetorDeContainersCadastrados[contador].peso - vetorDeContainersSelecionados[posSelecionado].peso);
                    numeroDeContainersComMargem++;
                }
            }
        }
    }

    mergeSort(vetorDeContainersComMargem, 0, numeroDeContainersComMargem - 1);

    for (int i = 0; i < numeroDeContainersComMargem; i++) {
        fprintf(output, "%s:%dkg(%d%%)\n", vetorDeContainersComMargem[i].codigo, vetorDeContainersComMargem[i].diferencaPeso, vetorDeContainersComMargem[i].margemPeso);
    }

    fclose(input);
    fclose(output);
    free(vetorDeContainersCadastrados);
    free(vetorDeContainersSelecionados);
    free(vetorDeContainersComMargem);

    return 0;
}