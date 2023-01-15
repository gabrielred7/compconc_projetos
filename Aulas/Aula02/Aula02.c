#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// funcao que a thread ira executar
void * tarefa (void * arg){
    int ident = * (int *)arg;
    printf("Ola, sou a thread nova! %d!\n", ident);
    pthread_exit(NULL);
}

// funcao principal/
int main(void){
    pthread_t tid; //identificador da thread no sistema
    int ident = 1; //identificador local da thread

    //cria a thread nova
    if(pthread_create(&tid, NULL, tarefa, (void *)&ident))
        printf("Erro -- pthread_create\n");

    // imprime a mensagem de boas vindas
    printf("Ola, sou a thread principal\n");

    // desvincula o termino da main do termino programa
    pthread_exit(NULL);
    return 0;
}
