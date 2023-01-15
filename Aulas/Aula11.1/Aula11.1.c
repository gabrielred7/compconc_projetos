#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NTHREADS 2

//Variaveis globais
int s = 0; //compartilhada pelas threads
sem_t em; //semaforo para exclusao mutua entre as threads

//funcao executada pelas threads
void *ExecutaTarefa (void *threadid){
    int *tid = (int*) threadid;
    printf("Thread : %d esta executando...\n", *tid);
    for (int i = 0; i < 1000000; i++){
        sem_wait(&em); //entrando na secao critica
        s++; //secao critica //usa exclusao mutua com semaforo
        sem_post(&em); //saindo da secao critica
    }
    printf("Thread : %d terminou!\n", *tid);
    free(threadid);
    pthread_exit(NULL);
}

//funcao principal
int main(int argc, char *argv[]){
    pthread_t tid[NTHREADS];
    int t, *id;

    //inicia semaforo binario
    sem_init(&em, 0, 1);

    for (t = 0; t < NTHREADS; t++){
        //aloca espaço para o identificador da thread
        if ((id = malloc(sizeof(int)))==NULL){pthread_exit(NULL); return 1;}
        *id = t;
        //print("--Cria a thread %d\\n, t");
        if (pthread_create(&tid[t], NULL, ExecutaTarefa, (void *)id)){
            printf("--Erro: pthread_create()\n"); exit(-1);
        }
    }

    //--espera todas as threads terminarem
    for (t = 0; t < NTHREADS; t++){
        if (pthread_join(tid[t], NULL)){
            printf("--ERRO: pthread_join()\n"); exit(-1);
        }
    }
    printf("Valor de s = %d\n", s);
    pthread_exit(NULL);
}