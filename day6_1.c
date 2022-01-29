/* Day 6 - Parte 1 y 2 */
#include <stdio.h>
#include <stdlib.h>

#define DIM 600
#define DAYS 256
#define TAM 9

int leerEntrada(char *nombre_fichero, long salida[TAM]);

int main(){

    char nombre_fichero[DIM]="input.txt";
    long i, j, salida[TAM], aux[TAM], suma;

    /* Llamada a la función leerEntrada */
    if(leerEntrada(nombre_fichero, salida)==0){
        printf("Error en la función leerEntrada.\n");
        return 0;
    }
    /* Mostramos el resultado inicial */
    printf("\nInitial state: ");
    for(i=0; i<TAM; i++){
        printf("(%ld)=\e[1;34m%-10ld\e[0m ", i, salida[i]);
    }
    
    

    /* Recorremos todos los días definidos en DAYS */
    for(i=0; i<DAYS; i++){
        /* Guardamos los valores en un array auxiliar */
        for(j=0; j<TAM; j++){
            aux[j]=salida[j];
        }
        printf("\nAfter %2ld day:  ", i+1);
        /* Modificamos los valores */
        for(j=TAM-1; j>=0; j--){
            switch (j){
                case 8:
                case 7:
                case 6:
                case 5:
                case 4:
                case 3:
                case 2:
                case 1:
                salida[j-1]=aux[j];
                break;
                case 0:
                salida[6]+=aux[j];
                salida[8]=aux[j];
                break;
            }
            
        }
        for(j=0; j<TAM; j++){
            printf("(%ld)=\e[1;34m%-10ld\e[0m ", j, salida[j]);
        }
    }

    /* Mostramos el resultado por pantalla */
    for(i=0, suma=0; i<TAM; i++){
        suma+=salida[i];
    }
    printf("\nAfter %d days, there would be a total of %ld.\n", DAYS, suma);
    
    printf("\n");
    return 1;
}


int leerEntrada(char *nombre_fichero, long salida[TAM]){

    FILE *pf;
    char car;
    int i;

    /* Abrimos el fichero */
    pf=fopen(nombre_fichero, "r");
    if(pf==NULL){
        printf("Error abriendo fichero (%s).\n", nombre_fichero);
        return 0;
    }

    /* Inicializa salida a ceros */
    for(i=0; i<TAM; i++){
        salida[i]=0;
    }

    /* Contamos cuantos numeros en la entrada */
    for( ; fscanf(pf, "%c", &car)==1; ){
        if(car>='0'&&car<='8'){
            salida[car-'0']++;
        }
    }
    fclose(pf);
    return 1;
}