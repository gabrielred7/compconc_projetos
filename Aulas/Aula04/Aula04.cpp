//Programação Concorrente (uso de threads)
//Versao 1.0 - Uma thread para cada elemento de saida
//Problema de multiplicação de matriz-vetor (considerando matrizes quadradas)
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

float *mat; //matriz de entrada
float *vet; //vetor de entrada
float *saida; //vetor de saida

typedef struct {
    int id; //elemento que a thread ira processar
    int dim; //dimensao das estruturas de entrada
} tArgs; //nome do tipo da struct

//funcao que as threads vao executar (importante alocar memoria e estruturas)
void * tarefa(void *arg){
    tArgs *args = (tArgs*) arg; //typecast de ponteiro para o novo tipo tArgs
    for(int j=0; j<args->dim; j++)
        saida[args->id] += mat[(args->id) * (args->dim) + j] * vet[j];
    pthread_exit(NULL);
}

int main(int argc, char* argv[]){
    int dim; //dimensao da matriz de entrada
    pthread_t *tid; //identificadores das threads no sistema
    tArgs *args; //identificadores locais das threads e dimensao

    //leitura e avaliação dos paramentros de entrada da main
    if(argc < 2){
        printf("Digite: %s <dimensao da matris>\n", argv[0]);
        return 1;
    }
    dim = atoi(argv[1]);

    //alocação de memoria para as estruturas de dados principais
    mat = (float *) malloc(sizeof(float) * dim * dim);
    if (mat == NULL){printf("ERRO--malloc\n"); return 2;}
    vet = (float *) malloc(sizeof(float) * dim);
    if (vet == NULL){printf("ERRO--malloc\n"); return 2;}
    saida = (float *) malloc(sizeof(float) * dim);
    if (saida == NULL){printf("ERRO--malloc\n"); return 2;}

    //inicialização das estruturas de dados principais
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            mat[i*dim+j] = 1;  //equivalente mat[i][j]
            vet[j] = 1;
        }
        saida[i] = 0;
    }

    //multiplicacao da matriz pelo vetor
    //alocacao de memoria da estruturas de dado e das threads
    tid = (pthread_t*) malloc(sizeof(pthread_t)*dim);
    if(tid==NULL){puts("ERRO--malloc"); return 2;}
    args = (tArgs*) malloc(sizeof(tArgs)*dim);
    if(args==NULL){puts("ERRO--malloc");return 2;}

    //criacao das threads
    for(int i=0; i<dim; i++){
        (args+i)->id = i;
        (args+i)->dim = dim;
        if(pthread_create(tid+i, NULL, tarefa, (void*)(args+i))){
            puts("ERRO--pthread_create"); return 3;
        }
    }

    //espera pelo terminon da threads
    for(int i=0; i<dim; i++){
        pthread_join(*(tid+1), NULL);
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
