#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREADS 10

// funcao que a thread irá executar
void * tarefa (void * arg){
    int ident = * (int *)arg;
    printf("Ola, sou a thread nova %d!\n", ident);
    pthread_exit(NULL);
}

// funcao principal/
int main(void){
    pthread_t tid[NTHREADS]; //identificador da thread no sistema
    int ident[NTHREADS]; //identificador local da thread

    //cria as threads novas
    for(int i=1; i<=NTHREADS; i++){
        ident[i-1] = i;
        if(pthread_create(&tid[i-1], NULL, tarefa, (void *)&ident[i-1]))
            printf("Erro -- pthread_create\n");
    }

    // imprime a mensagem de boas vindas
    printf("Ola, sou a thread principal\n");

    // desvincula o termino da main do termino programa
    pthread_exit(NULL);
    return 0;
}
