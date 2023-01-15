//Programa��o Concorrente (uso de threads)
//Versao 2.0 - Definindo qual o numero de thread a se usar na saida, escolher o mais proximo ao numero de processadores
//Problema de multiplica��o de matriz-vetor (considerando matrizes quadradas)
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

float *mat; //matriz de entrada
float *vet; //vetor de entrada
float *saida; //vetor de saida
int nthreads; //numero de threads

typedef struct {
    int id; //elemento que a thread ira processar
    int dim; //dimensao das estruturas de entrada
} tArgs; //nome do tipo da struct

//funcao que as threads vao executar (importante alocar memoria e estruturas)
void * tarefa(void *arg){
    //criando um implementa��o generica
    tArgs *args = (tArgs*) arg; //typecast de ponteiro para o novo tipo tArgs
    printf("Thread %d\n", args->id);
    for(int i=args->id; i<args->dim; i+=nthreads){ // estrategia de intercalar as linhas para se adaptar ao numero de threads
        for(int j=0; j<args->dim; j++){
            saida[i] += mat[i * (args->dim) + j] * vet[j];
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char* argv[]){
    int dim; //dimensao da matriz de entrada
    pthread_t *tid; //identificadores das threads no sistema
    tArgs *args; //identificadores locais das threads e dimensao

    //leitura e avalia��o dos paramentros de entrada da main
    if(argc < 3){
        printf("Digite: %s <dim da matris> <n de threads>\n", argv[0]);
        return 1;
    }
    dim = atoi(argv[1]); //transforma string para inteiro de cada dimensao
    nthreads = atoi(argv[2]); //transforma string para inteiro de cada n de threads
    if (nthreads > dim) nthreads = dim;

    //aloca��o de memoria para as estruturas de dados principais
    mat = (float *) malloc(sizeof(float) * dim * dim);
    if (mat == NULL){printf("ERRO--malloc\n"); return 2;}
    vet = (float *) malloc(sizeof(float) * dim);
    if (vet == NULL){printf("ERRO--malloc\n"); return 2;}
    saida = (float *) malloc(sizeof(float) * dim);
    if (saida == NULL){printf("ERRO--malloc\n"); return 2;}

    //inicializa��o das estruturas de dados principais
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            mat[i*dim+j] = 1;  //equivalente mat[i][j]

        }
        vet[i] = 1;
        saida[i] = 0;
    }

    //multiplicacao da matriz pelo vetor
    //alocacao de memoria da estruturas de dado e das threads
    tid = (pthread_t*) malloc(sizeof(pthread_t)*nthreads);
    if(tid==NULL){puts("ERRO--malloc"); return 2;}
    args = (tArgs*) malloc(sizeof(tArgs)*nthreads);
    if(args==NULL){puts("ERRO--malloc");return 2;}

    //criacao das threads
    for(int i=0; i<nthreads; i++){
        (args+i)->id = i;
        (args+i)->dim = dim;
        if(pthread_create(tid+i, NULL, tarefa, (void*)(args+i))){
            puts("ERRO--pthread_create"); return 3;
        }
    }

    //espera pelo termino da threads
    for(int i=0; i<nthreads; i++){
        pthread_join(*(tid+i), NULL);
    }


    //exibicao dos resultados
    puts("Matriz de Entrada:");
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++)
            printf("%.1f ", mat[i*dim+j]);
        puts("");
    }
    puts("Vetor de Entrada:");
    for(int j=0; j<dim; j++)
        printf("%.1f ", vet[j]);
    puts("");


    puts("Vetor de Saida:");
    for(int j=0; j<dim; j++)
        printf("%.1f ", saida[j]);
    puts("");

    //liberacao da memoria
    free(mat);
    free(vet);
    free(saida);
    free(tid);
    free(args);
    return 0;
}
