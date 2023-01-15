#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NTHREADS  4

int status = 0, aux = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
sem_t s, x, h;

void wait(){
    sem_wait(&x); // Decrementa para 0 e retorna
    aux++;
    sem_post(&x); // Incrementa em 1
    pthread_mutex_unlock(&m);
    sem_wait(&h); // Quando entra 0, thread bloqueia
    sem_post(&s); // Incrementa em 1
    pthread_mutex_lock(&m);
}

void notify(){
    sem_wait(&x); // Decrementa para 0 e retorna
    if (aux > 0){
        aux--;
        sem_post(&h); // Desbloqueia a thread 
        sem_wait(&s); // Decrementa para 0 e retorna
    }
    sem_post(&x); // Incrementa em 1
}

void notifyAll(){
    sem_wait(&x); // Decrementa para 0 e retorna
    for (int i = 0; i < aux; i++){
        sem_post(&h); // Desbloqueia as threads 
    }
    while (aux > 0){
        aux--;
        sem_wait(&s); // Decrementa para 0 e retorna
    }
    sem_post(&x); // Incrementa em 1
}

//T1 -> Fique a vontade.
void *A (void *T){
    pthread_mutex_lock(&m);

    if (status == 0){
        wait();
    }
    printf("Fique a vontade!\n");
    status++;
    if (status == 4){
        printf("A:  status = %d, vai sinalizar a condicao \n", status);
        notify();
    }
    pthread_mutex_unlock(&m);

    pthread_exit(NULL);
}

//T2 -> Seja bem-vindo!
void *B (void *T){
    printf("Seja bem-vindo!\n");
    pthread_mutex_lock(&m);

    status++;
    printf("B: status = %d, vai sinalizar a condicao \n", status);
    notifyAll();

    pthread_mutex_unlock(&m);
    pthread_exit(NULL);
}

//T3 -> Volte sempre!
void *C (void *T){
    pthread_mutex_lock(&m);
    status++;
    if (status < 4){
        printf("C: status = %d, vai se bloquear...\n", status);
        wait();
        printf("C: sinal recebido e mutex realocado. status = %d\n", status);
    }
    printf("Volte sempre!\n");
    pthread_mutex_unlock(&m);
    pthread_exit(NULL);
}

//T4 -> Sente-se por favor.
void *D (void *T){
    pthread_mutex_lock(&m);
    if (status == 0){
        wait();
    }
    printf("Sente-se por favor\n");
    status++;
    if (status == 4){
        printf("D:  status = %d, vai sinalizar a condicao \n", status);
        notify();
    }
    pthread_mutex_unlock(&m); 
    pthread_exit(NULL);
}


int main(int argc, char *argv[]) {
    pthread_t threads[NTHREADS];

    //semaforos
    sem_init(&s, 0, 0);
    sem_init(&x, 0, 1);
    sem_init(&h, 0, 0);

    /* Cria as threads */
    pthread_create(&threads[0], NULL, A, NULL);
    pthread_create(&threads[1], NULL, B, NULL);
    pthread_create(&threads[2], NULL, C, NULL);
    pthread_create(&threads[3], NULL, D, NULL);
    
    /* Espera todas as threads completarem */
    for (int i = 0; i < NTHREADS; i++) {
        pthread_join(threads[i], NULL);
    }
}