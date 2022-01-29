#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM 5
#define TAM 100

void imprimeBingos(int bingo[][DIM][DIM]){

    int i, j, k;

    for(i=0; i<TAM; i++){
        for(j=0; j<DIM; j++){
            for(k=0; k<DIM; k++){
                printf("%2d ", bingo[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

void imprimeCarton(int carton[DIM][DIM]){
    int i, j;
    
    for(i=0; i<DIM; i++){
        for(j=0; j<DIM; j++){
            printf("%2d ", carton[i][j]);
        }
        printf("\n");
    }
}

void inicializaBingos(int bingo[][DIM][DIM]){

    int i, j, k;

    for(i=0; i<TAM; i++){
        for(j=0; j<DIM; j++){
            for(k=0; k<DIM; k++){
                bingo[i][j][k]=0;
            }
        }
    }
}

void rellenaBingos(int bingo[][DIM][DIM], int empty[][DIM][DIM], int num){

    int i, j, k;

    for(i=0; i<TAM; i++){
        for(j=0; j<DIM; j++){
            for(k=0; k<DIM; k++){
                if(bingo[i][j][k]==num){
                    if(empty[i][j][k]==0){
                        empty[i][j][k]=num;
                    }
                }
            }
        }
    }
}

void eliminarCarton(int empty[DIM][DIM]){
    
    int i, j;

    for(i=0;i<DIM;i++){
        for(j=0;j<DIM;j++){
            empty[i][j]=-1;
        }
    }
}

/* Comprueba que no haya bingo y devuelve la posición del cartón ganador en caso de encontrarlo */
void compruebaBingo1(int empty[][DIM][DIM], int *eliminados){
    int i, j, k, contador;

    /* Comprueba filas */
    for(i=0; i<TAM; i++){
        for(j=0; j<DIM; j++){
            for(k=0, contador=0; k<DIM; k++){
                if(empty[i][j][k]==0 || empty[i][j][k]==-1){
                    contador++;
                }
            }
            if(contador==0){
                eliminarCarton(empty[i]);
                (*eliminados)++;
            }
        }
    }

    /* Comprueba columnas */
    for(i=0; i<TAM; i++){
        for(k=0; k<DIM; k++){
            for(j=0, contador=0; j<DIM; j++){
                if(empty[i][j][k]==0 || empty[i][j][k]==-1){
                    contador++;
                }
            }
            if(contador==0){
                eliminarCarton(empty[i]);
                (*eliminados)++;
            }
        }
    }
}

int compruebaBingo2(int empty[][DIM][DIM], int *eliminados){
    int i, j, k, contador;

    /* Comprueba filas */
    for(i=0; i<TAM; i++){
        for(j=0; j<DIM; j++){
            for(k=0, contador=0; k<DIM; k++){
                if(empty[i][j][k]==0 || empty[i][j][k]==-1){
                    contador++;
                }
            }
            if(contador==0){
                return i;
            }
        }
    }

    /* Comprueba columnas */
    for(i=0; i<TAM; i++){
        for(k=0; k<DIM; k++){
            for(j=0, contador=0; j<DIM; j++){
                if(empty[i][j][k]==0 || empty[i][j][k]==-1){
                    contador++;
                }
            }
            if(contador==0){
                return i;
            }
        }
    }

    return -1;
}

int boardScore(int bingo[DIM][DIM], int empty[DIM][DIM], int num){
    
    int suma, i, j;

    for(suma=0,i=0;i<DIM;i++){
        for(j=0;j<DIM;j++){
            if(empty[i][j]==0){
                suma+=bingo[i][j];
            }
        }
    }

    return suma*num;
}


int main(){

    FILE *f;
    int bingo[TAM][DIM][DIM], empty[TAM][DIM][DIM], i, j, eliminados;
    int num[TAM]={37,60,87,13,34,72,45,49,61,27,97,88,50,30,76,40,63,9,38,67,82,6,59,90,99,54,11,66,98,23,64,14,18,4,10,89,46,32,19,5,1,53,25,96,2,12,86,58,41,68,95,8,7,3,85,70,35,55,77,44,36,51,15,52,56,57,91,16,71,92,84,17,33,29,47,75,80,39,83,74,73,65,78,69,21,42,31,93,22,62,24,48,81,0,26,43,20,28,94,79};

    /* Abrimos el fichero */
    f=fopen("bingo.txt", "r");
    if(f==NULL){
        printf("Error abriendo fichero.\n");
        return -1;
    }

    /* Guardamos todos los posibles bingos en un array de 3 dimensiones */
    for(i=0;i<TAM;i++){
        for(j=0; fscanf(f, "%d %d %d %d %d", &bingo[i][j][0], &bingo[i][j][1], &bingo[i][j][2], &bingo[i][j][3], &bingo[i][j][4])==5; ){
            j++;
        }
    }

    inicializaBingos(empty);

    /* Rellena un numero y comprueba bingos hasta encontrar un ganador */
    i=0; 
    eliminados=0;
    do{
        rellenaBingos(bingo, empty, num[i]);
        compruebaBingo1(empty, &eliminados);
        i++;
    }while(eliminados!=99);

    imprimeBingos(empty);

    do{
        rellenaBingos(bingo, empty, num[i]);
        j=compruebaBingo2(empty, &eliminados);
        if(j!=-1){
            printf("\nBingo! (%d)\n", j);
            imprimeCarton(empty[j]);

            printf("\nCarton ganador:\n");
            imprimeCarton(bingo[j]);

            printf("\nScore: %d\n", boardScore(bingo[j], empty[j], num[i]));
        }
        i++;
    }while(j==-1);

    fclose(f);
    return 0;
}