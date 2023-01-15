/* Problema: Dada uma sequência de numeros inteiros positivos,
identificar todos os n ́umeros primos e retornar a quantidade 
encontrada */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<pthread.h>

//Função para verificar a primalidade
int ePrimo(long long int n){
    if(n <= 1) return 0;
    if(n == 2) return 1;
    if(n % 2 == 0) return 0;
    for( int i = 3; i < sqrt(n) + 1; i += 2)
        if(n % i == 0) return 0;
    return 1;
}

//Solução 1: Divisão estática das tarefas entre as threads. Essas estrategia faz um caminhamento de alternancia entre as threads

long long int sequencia[N];

void * conta_primos_1(void * arg){
    long int id = (long int) arg;
    long int total = 0, *ret;
    for (long int i = id; i < N; i+= NTHREADS){
        if (ePrimo(sequencial[i])){
           total++;
        }
    }
    ret =  // aloca memoria
    *ret = total;
    pthread_exit((void *) ret)
}

// Essa solução garante balanceamento de carga?

// Análise da Solução 1: Para tempos de execução para N = 1000000:
/* 
Threads/tempos(s) | Sequencial | Concorrente
1 thread            0.525401      0.544142
2 threads           0.525401      0.542982
3 threads           0.525401      0.317463
4 threads           0.525401      0.322370

É necessario que as threads agem quase ao mesmo tempo.
*/

//Solução 2: Divisão dinâmica das tarefas entre as threads. Usa memoria compartilha para aumenta a performace das threads

int i_global = 0; pthread_mutex_t bastao; //variavel compartilhada

void * conta_primos_2(void * arg){
    int t_local, total = 0;
    pthread_mutex_lock(&bastao);
    i_local = i_global; i_global++; //!!acessa variavel compartilhada!!
    pthread_mutex_unlock(&bastao);

    while (i_local < N){
        if (ePrimo(sequencia[i_local])){
            pthread_mutex_lock(&bastao);
            i_local = i_global; i_global++; //!!acessa variavel compartilhada!!
            pthread_mutex_unlock(&bastao);
        }
    }
    //...retorna 'total'
}

// Análise da Solução 2: Para tempos de execução para N = 1000000:
/* 
Threads/tempos(s) | Sequencial | Concorrente
1 thread            0.525401      0.544142
2 threads           0.525401      0.338769
3 threads           0.525401      0.312914
4 threads           0.525401      0.308235

É necessario que as threads agem quase ao mesmo tempo.
*/