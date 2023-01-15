#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include <time.h>


long int ntabuadas;
long int nmultiplos;
int nthreads;
long int *vetor;
long int resultado;


int main(int argc, char *argv[]){
    clock_t inicio, fim; //tomada de tempo
    double delta = 0;

    // validar o numero de entradas 
    if(argc < 3){
        fprintf(stderr, "Digite: %s <ntabuadas> <nmult>\n", argv[0]);
        return 1;
    }

    ntabuadas = atoi(argv[1]);
    nmultiplos = atoi(argv[2]);
    //nthreads = atoi(argv[3]);
    resultado = 0;


    //alocar vetor 
    vetor = (long int *) malloc (sizeof(long int)*(ntabuadas*nmultiplos));
    if(vetor == NULL){
        fprintf(stderr,"ERRoO - malloc");
        return 2;
    }

    inicio = clock();
    for (int i = 1; i<=ntabuadas; i++ ){
        for(int j = 1; j<=nmultiplos; j++){
            vetor[resultado] = i*j;
            resultado ++;
            //printf("%d x %d = %ld\n",i,j,resultado);
        }
        //printf("\n");
    }
    fim = clock();
    delta = (double)(fim - inicio) * 1000 / CLOCKS_PER_SEC; 
    printf("Tempo sequencial colocando no vetor: %lf\n", delta);

    resultado = 0;

    inicio = clock();
    for (int i = 1; i<=ntabuadas; i++ ){
        for(int j = 1; j<=nmultiplos; j++){
            if(vetor[resultado] != i*j){
                printf("Erro, alguma conta errada");
                break;
            }
            resultado ++;
        }
    }
    fim = clock();
    delta = (double)(fim - inicio) * 1000 / CLOCKS_PER_SEC;
    printf("Tempo sequencial verificando o vetor: %lf\n", delta);


    inicio = clock();
    for (int i = 0; i<=(ntabuadas*nmultiplos); i++ ){
        printf("%ld\n", vetor[i]);
    }
    fim = clock();
    delta = (double)(fim - inicio) * 1000 / CLOCKS_PER_SEC;
    printf("Tempo sequencial printando: %lf\n", delta);
    return 0;
}