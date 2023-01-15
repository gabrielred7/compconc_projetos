//Soma todos os elementos de um vetor inteiro
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>>

long int dim; // dim do vetor de entrada
int nthreads; // numero de threads
int *vetor; // vetor de entrada com dimensao dim 

//fluxo das threads
void * tarefa(void * arg){
    long int id = (long int) arg; //identificaor da thread
    long int somaLocal = 0; //var local da soma dos elementos de cada bloco
    
    //dividindo os blocos das threads
    long int tamBloco = dim/nthreads; //tamanho do bloco de cada thread
    long int inicial = id*tamBloco; //elemento inicial do bloco da thread
    long int final; //elemento final do bloco da thread
    if (id == nthreads - 1){final = dim;} // tratamento do final. caso eu seja a ultima thread
    else {final = inicial + tamBloco;} //trata o resto se houver
    
    //soma os elementos do bloco da thread e depois junta num local so
    for (long int i=inicial; i < final; i++){
        somaLocal += vetor[i]; 
    }

    //retorna o resultado da soma local
    pthread_exit((void*) somaLocal);
}

int main(int argc, char *argv[]){
    long int somaSeq = 0; //soma sequencial
    long int somaCon = 0; //soma concorrente
    pthread_t *tid; //identificadores das threads no sistema
    long int retorno; //valor de retorno das threads

    clock_t inic, fim; //tomada de tempo
    double delta;

    //recebe e valida os parametros de entrada (dim do vetor, n de threads)
    if(argc < 3){
        fprintf(stderr, "Digite: %s <dim do vetor> <n de threads>\n", argv[0]);
        return 1;
    }
    dim = atoi(argv[1]); //atoi converte string para inteiro
    nthreads = atoi(argv[2]);

    //aloca o vetor de entrada
    vetor = (int*) malloc(sizeof(int) * dim); //malloc converte ponteiro para void
    if (vetor == NULL){fprintf(stderr, "Erro--malloc\n"); return 2;}
    
    //inicializa e preenche o vetor de entrada
    for(long int i=0; i<dim; i++){
        vetor[i] = i%1000;
    }

    /* SOMA SEQUENCIAL DOS ELEMENTOS */
    inic = clock();
    for(long int i=0; i<dim; i++){
        somaSeq += vetor[i];
    }
    fim = clock();
    delta = (double)(fim - inic) * 1000000000.0 / CLOCKS_PER_SEC; 
    printf("Tempo de sequencial: %.5f\n", delta);
    
    /* SOMA CONCORRENTE DOS ELEMENTOS */
    //aloca as threads
    inic = clock();
    tid = (pthread_t *) malloc(sizeof(pthread_t) * nthreads);
    if (tid == NULL){fprintf(stderr, "ERRO--malloc\n"); return 2;}
    
    //criação thread
    for(long int i=0; i<nthreads; i++){
        if(pthread_create(tid+i, NULL, tarefa, (void*) i)){
            fprintf(stderr, "ERRO--pthread_create\n"); return 3;
        }
    }

    //aguardar o termino das threads
    for(long int i=0; i<nthreads; i++){
        if(pthread_join(*(tid+i), (void**) &retorno)){ //o segundo argumento é o retorna da função
            fprintf(stderr, "ERRO--pthread_join\n"); return 3;            
        }
        //soma global
        somaCon += retorno;
    }

    fim = clock();
    delta = (double)(fim - inic) * 1000000000.0 / CLOCKS_PER_SEC; 
    printf("Tempo de concorrente: %.5f\n", delta);

    //exibir os resultados
    printf("Soma seq: %ld\n", somaSeq);
    printf("Soma conc: %ld\n", somaCon);
    
    //libera a memoria alocada
    free(vetor);
    free(tid);

    return 0;
}