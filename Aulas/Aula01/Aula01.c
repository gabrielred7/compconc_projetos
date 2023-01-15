#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// funcao que a thread ira executar
void * tarefa (void * arg){
    printf("Ola, sou a thread nova!\n");
    pthread_exit(NULL);
}
// funcao principal/
int main(void){
    pthread_t tid; //identificador da thread no sistema
    //cria a thread nova
    if(pthread_create(&tid, NULL, tarefa, NULL))
        printf("Erro -- pthread_create\n");
    // imprime a mensagem de boas vindas
    printf("Ola, sou a thread principal\n");
    // desvincula o termino da main do termino programa
    pthread_exit(NULL);
    return 0;
}
