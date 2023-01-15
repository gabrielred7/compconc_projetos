//Programação Estrutural
//Problema de multiplicação de matriz-vetor (considerando matrizes quadradas)
#include <stdio.h>
#include <stdlib.h>

float *mat; //matriz de entrada
float *vet; //vetor de entrada
float *saida; //vetor de saida

int main(int argc, char* argv[]){
    int dim; //dimensao da matriz de entrada

    //leitura e avaliação dos paramentros de entrada
    if(argc < 2){
        printf("Digite: %s <dimensao da matris>\n", argv[0]);
        return 1;
    }
    dim = atoi(argv[1]);

    //alocação de memoria para as estruturas de dados
    mat = (float *) malloc(sizeof(float) * dim * dim);
    if (mat == NULL){printf("ERRO--malloc\n"); return 2;}
    vet = (float *) malloc(sizeof(float) * dim);
    if (vet == NULL){printf("ERRO--malloc\n"); return 2;}
    saida = (float *) malloc(sizeof(float) * dim);
    if (saida == NULL){printf("ERRO--malloc\n"); return 2;}

    //inicialização das estruturas de dados
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            mat[i*dim+j] = 1;  //equivalente mat[i][j]
            vet[j] = 1;
        }
        saida[i] = 0;
    }

    //multiplicacao da matriz pelo vetor
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            saida[i] += mat[i*dim+j] * vet[j];
        }
    }

    //exibicao dos resultados
    puts("Matriz de Entrada:");
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++)
            printf("%.1f ", mat[i * dim+j]);
        puts("");
    }

    puts("Vetor de Entrada:");
    for(int j=0; j<dim; j++)
        printf("%.1f ", vet[j]);
    puts("");

    puts("Vetor de Saida:");
    for(int j=0; j<dim; j++)
        printf("%.1f ", saida[j]);
    puts("");

    //liberacao da memoria
    free(mat);
    free(vet);
    free(saida);
    return 0;
}
