//Comunicação entre threads usando variavel compartilhada

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREADS 2

int s = 0; //variavel compartilhada
pthread_mutex_t lock; //variavel especial para sicronizacao de exclusao mutua

//função executada pelas threads
void *ExecutaTarefa(void *arg){
    long int id = (long int) arg;
    printf("Thread: %ld esta executando...\n", id);
    for (int i = 0; i < 10000; i++){
        pthread_mutex_lock(&lock);
        s++; //incrementa a variavel compartilhada
        pthread_mutex_unlock(&lock);
    }
    printf("Thread: %ld terminou!\n", id);
    pthread_exit(NULL);
}

//fluxo principal
int main(int arc, char *argv[]){
    pthread_t tid[NTHREADS];

    //Inicializa a variavel de exclusao mutua
    pthread_mutex_init(&lock, NULL);
    
    //--cria as threads de 0 a 1
    for (long int t = 0; t < NTHREADS; t++){
        if (pthread_create(&tid[t], NULL, ExecutaTarefa, (void *)t)){
            printf("--ERRO: pthread_create()\n"); exit(-1);
        }
    }
    //--espera todas as threads
    for (int t = 0; t < NTHREADS; t++){
        if (pthread_join(tid[t], NULL)){
            printf("--ERRO: pthread_join()\n"); exit(-1);
        }
    }
    pthread_mutex_destroy(&lock);

    printf("Valor de s = %d\n", s);
    return 0;
}