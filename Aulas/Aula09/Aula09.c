//Código barreira (sincronização coletiva)

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREADS 5
#define PASSOS 5

/* Variaveis Globais */
int tBloqueadas = 0;
pthread_mutex_t x_mutex;
pthread_cond_t x_cond;

// Funcao Barreira
void barreira(int nthreads){
    pthread_mutex_lock(&x_mutex); //inicio secao critica
    if (tBloqueadas == (nthreads - 1)){
        //ultima thread a chegar na barreira
        pthread_cond_broadcast(&x_cond);
        tBloqueadas = 0;
    } else {
        tBloqueadas++;
        pthread_cond_wait(&x_cond, &x_mutex);
    }
    pthread_mutex_unlock(&x_mutex);
}

//Funcao thread
void *tarefa (void *arg){
    int id = *(int*)arg;
    int boba1, boba2;

    for (int passos = 0; passos < PASSOS; passos++){
        /* faz alguma coisa... */
        boba1=100; boba2=-100; while (boba2<boba1) boba2++;
        printf("Thread %d: passo =%d\n", id, passos);
        barreira(NTHREADS); //sincronizacao condicional
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){
    pthread_t threads[NTHREADS];
    int id[NTHREADS];
    /* Iniciliza o mutex (lock de exclusao mutua) e a variavel de condicao */
    pthread_mutex_init(&x_mutex, NULL);
    pthread_cond_init(&x_cond, NULL);

    /* Cria as threads */
    for (int i = 0; i < NTHREADS; i++){
        id[i] = i;
        pthread_create(&threads[i], NULL, tarefa, (void *) &id[i]);
    }
    
    /* Espera todas as threads completarem */
    for (int i = 0; i < NTHREADS; i++){
        pthread_join(threads[i], NULL);
    }
    printf("FIM.\n");

    /* Desaloca variaveis e termina */
    pthread_mutex_destroy(&x_mutex);
    pthread_cond_destroy(&x_cond);
    return 0;
}