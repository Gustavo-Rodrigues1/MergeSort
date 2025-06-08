#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//struct contendo os dados dos containers
typedef struct {
    char codigo[15];
    char cnpj[20];
    int peso;
    int margemPeso;
    int diferencaPeso;
} Containers;

//Mergesort para ordenar pelo codigo, já que para fazer a busca binária é necessário estar em ordem e como o código é o único dado que não tem diferença entre os containers selecionados e os cadastrados, pode ser usado
void mergeCodigo(Containers *vetor, int inicio, int meio, int fim) {
    //Criação de um vetor de containers auxiliar
    Containers *aux = (Containers *)malloc((fim - inicio + 1) * sizeof(Containers));
    if (aux == NULL) {
        //verifica se o malloc alocou a memória corretamente
        fprintf(stderr, "Falha ao alocar memória para mergeCodigo.\n");
        exit(EXIT_FAILURE);
    }
    
    //logica do mergesort
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
    //libera a memoria
    free(aux);
}

//função recursiva do mergeSort para o codigo do container
void mergeSortCodigo(Containers *vetor, int inicio, int fim) {
    if (inicio < fim) {
        int meio = (inicio + fim) / 2;
        mergeSortCodigo(vetor, inicio, meio);
        mergeSortCodigo(vetor, meio + 1, fim);
        mergeCodigo(vetor, inicio, meio, fim);
    }
}

//função mergesort para ordenar a saida para maior margem de peso a menor
void merge(Containers *vetor, int inicio, int meio, int fim) {
    //Criação de um vetor de containers auxiliar
    Containers *aux = (Containers *)malloc((fim - inicio + 1) * sizeof(Containers));
    if (aux == NULL) {
        //verifica se a memoria foi alocada devidamente
        fprintf(stderr, "Falha ao alocar memória para merge.\n");
        exit(EXIT_FAILURE);
    }

    //lógica do mergesort decrescente
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
    //libera a memoria
    free(aux);
}

//função recursiva do mergesort descrescente
void mergeSort(Containers *vetor, int inicio, int fim) {
    if (inicio < fim) {
        int meio = (inicio + fim) / 2;
        mergeSort(vetor, inicio, meio);
        mergeSort(vetor, meio + 1, fim);
        merge(vetor, inicio, meio, fim);
    }
}

//função de busca binária para achar os containers com margem de peso maior que 10% ou cnpj diferente por meio do codigo
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

    //verifica se os arquivos foram abertos corretamente
    if (input == NULL || output == NULL) {
        fprintf(stderr, "Falha ao abrir o arquivo!\n");
        return EXIT_FAILURE;
    }

    int numeroDeContainersCadastrados, numeroDeContainersSelecionados;

    //função para ler o numero de containers cadastrados e verificar se o dado foi lido corretamente
    if (fscanf(input, "%d", &numeroDeContainersCadastrados) != 1) {
        fprintf(stderr, "Erro ao ler o número de containers cadastrados.\n");
        fclose(input);
        fclose(output);
        return EXIT_FAILURE;
    }

    //declaração do vetor de containers cadastrados por meio de malloc
    Containers *vetorDeContainersCadastrados = (Containers *)malloc(numeroDeContainersCadastrados * sizeof(Containers));
    if (vetorDeContainersCadastrados == NULL) {
        //verifica se a memoria foi alocada corretamente
        fprintf(stderr, "Falha ao alocar memória para vetorDeContainersCadastrados.\n");
        fclose(input);
        fclose(output);
        return EXIT_FAILURE;
    }

    for (int contador = 0; contador < numeroDeContainersCadastrados; contador++) {
        //leitura dos dados no arquivo 
        if (fscanf(input, "%s %s %d", vetorDeContainersCadastrados[contador].codigo, vetorDeContainersCadastrados[contador].cnpj, &vetorDeContainersCadastrados[contador].peso) != 3) {
            fprintf(stderr, "Erro ao ler os dados do container cadastrado.\n");
            //liberação de memoria caso erro na leitura dos dados
            free(vetorDeContainersCadastrados);
            fclose(input);
            fclose(output);
            return EXIT_FAILURE;
        }
    }

    if (fscanf(input, "%d", &numeroDeContainersSelecionados) != 1) {
        //verifica se a memoria foi alocada corretamente
        fprintf(stderr, "Erro ao ler o número de containers selecionados.\n");
        //liberação de memoria caso erro na leitura do dado
        free(vetorDeContainersCadastrados);
        fclose(input);
        fclose(output);
        return EXIT_FAILURE;
    }

    //declaração do vetor de containers selecionados por meio de malloc
    Containers *vetorDeContainersSelecionados = (Containers *)malloc(numeroDeContainersSelecionados * sizeof(Containers));
    if (vetorDeContainersSelecionados == NULL) {
        fprintf(stderr, "Falha ao alocar memória para vetorDeContainersSelecionados.\n");
        //liberação de memoria caso erro na leitura dos dados
        free(vetorDeContainersCadastrados);
        free(vetorDeContainersSelecionados);
        fclose(input);
        fclose(output);
        return EXIT_FAILURE;
    }

    for (int contador = 0; contador < numeroDeContainersSelecionados; contador++) {
        //leitura dos dados dos containers selecionados e liberação de memória caso erro na leitura dos dados
        if (fscanf(input, "%s %s %d", vetorDeContainersSelecionados[contador].codigo, vetorDeContainersSelecionados[contador].cnpj, &vetorDeContainersSelecionados[contador].peso) != 3) {
            fprintf(stderr, "Erro ao ler os dados do container selecionado.\n");
            free(vetorDeContainersCadastrados);
            free(vetorDeContainersSelecionados);
            fclose(input);
            fclose(output);
            return EXIT_FAILURE;
        }
    }

    //ordenação para o uso da busca binária
    mergeSortCodigo(vetorDeContainersSelecionados, 0, numeroDeContainersSelecionados - 1);

    //variável para auxiliar na impressão dos containers com margem de peso posteriormente
    int numeroDeContainersComMargem = 0;
    Containers *vetorDeContainersComMargem = (Containers *)malloc(numeroDeContainersCadastrados * sizeof(Containers));
    if (vetorDeContainersComMargem == NULL) {
        fprintf(stderr, "Falha ao alocar memória para vetorDeContainersComMargem.\n");
        //liberação de memória caso de erro ao alocar a memória por meio do malloc
        free(vetorDeContainersCadastrados);
        free(vetorDeContainersSelecionados);
        fclose(input);
        fclose(output);
        return EXIT_FAILURE;
    }

    for (int contador = 0; contador < numeroDeContainersCadastrados; contador++) {
        //a busca binária retorna o indice do item buscado, caso não seja encontrado ela retorna -1
        int posSelecionado = bbinaria(vetorDeContainersCadastrados[contador].codigo, 0, numeroDeContainersSelecionados - 1, vetorDeContainersSelecionados);
        //verifica se o item foi encontrado
        if (posSelecionado != -1) {
            if (vetorDeContainersCadastrados[contador].peso != 0) {
                //arredondamento do peso e garantia de um valor positivo, é necessário o uso do double pois a função round retorna um double, o uso do int pode acarretar em perca de precisão do resultado
                double diferencaPercentual = round(fabs((vetorDeContainersCadastrados[contador].peso - vetorDeContainersSelecionados[posSelecionado].peso) * 100.0 / vetorDeContainersCadastrados[contador].peso));
                //compara se a diferença no cnpj
                if (strcmp(vetorDeContainersCadastrados[contador].cnpj, vetorDeContainersSelecionados[posSelecionado].cnpj) != 0) {
                    fprintf(output, "%s:%s<->%s\n", vetorDeContainersCadastrados[contador].codigo, vetorDeContainersCadastrados[contador].cnpj, vetorDeContainersSelecionados[posSelecionado].cnpj);
                }
                //verifica se a diferença percentual é maior que 10%
                if (diferencaPercentual > 10) {
                    vetorDeContainersComMargem[numeroDeContainersComMargem] = vetorDeContainersCadastrados[contador];
                    vetorDeContainersComMargem[numeroDeContainersComMargem].margemPeso = (int)diferencaPercentual;
                    vetorDeContainersComMargem[numeroDeContainersComMargem].diferencaPeso = abs(vetorDeContainersCadastrados[contador].peso - vetorDeContainersSelecionados[posSelecionado].peso);
                    numeroDeContainersComMargem++;
                }
            }
        }
    }

    //ordenação descrescente dos containers com margem para a impressão
    mergeSort(vetorDeContainersComMargem, 0, numeroDeContainersComMargem - 1);

    //impressão dos containers com diferença percentual maior que 10% em ordem decrescente
    for (int i = 0; i < numeroDeContainersComMargem; i++) {
        fprintf(output, "%s:%dkg(%d%%)\n", vetorDeContainersComMargem[i].codigo, vetorDeContainersComMargem[i].diferencaPeso, vetorDeContainersComMargem[i].margemPeso);
    }

    //fechamento dos arquivos e liberação de memória
    fclose(input);
    fclose(output);
    free(vetorDeContainersCadastrados);
    free(vetorDeContainersSelecionados);
    free(vetorDeContainersComMargem);

    return 0;
}
