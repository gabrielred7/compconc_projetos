//Soma todos os elementos de um vetor inteiro
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

long int dim; // dim do vetor de entrada
int nthreads; // numero de threads
int *vetor; // vetor de entrada com dimensao dim 

int main(int argc, char *argv[]){
    long int somaSeq = 0; //soma sequencial
    long int somaCon = 0; //soma concorrente
    clock_t inicio, fim;
    double delta;

    //recebe e valida os parametros de entrada (dim do vetor, n de threads)
    if(argc < 3){
        fprintf(stderr, "Digite: %s <dim do vetor> <n de threads>\n", argv[0]);
        return 1;
    }
    dim = atoi(argv[1]); //atoi converte string para inteiro
    nthreads = atoi(argv[2]);

    //aloca o vetor de entrada
    vetor = (int*) malloc(sizeof(int)*dim); //malloc converte ponteiro para void
    if (vetor == NULL){fprintf(stderr, "Erro--malloc\n"); return 2;}
    
    //preenche o vetor de entrada
    for(long int i=0; i<dim; i++){
        vetor[i] = i%1000;
    }
    //soma sequencial dos elementos
    inicio = clock();
    for(long int i=0; i<dim; i++){
        somaSeq += vetor[i];
    }
    fim = clock();
    delta = (double)(fim - inicio) * 1000.0 / CLOCKS_PER_SEC; 
    printf("Tempo de sequencial: %lf\n", delta);
    
    //soma concorrente doe elementos

    //criar thread

    //aguardar o termino das threads
    
    //computar o valor final

    //exibir os resultados
    printf("Soma seq: %ld\n", somaSeq);
    printf("Soma conc: %ld\n", somaCon);
    
    //libera a memoria alocada
    free(vetor);

    return 0;
}