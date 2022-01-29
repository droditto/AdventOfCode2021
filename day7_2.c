#include <stdio.h>
#include <stdlib.h>

int* leerCangrejo(char *nombre_fichero, int *tamanyo);
void calcminMax(int *num, int tamanyo, int *min, int *max);
int calcFuel(int *num, int tamanyo, int min, int max);

int main(){

    int tamanyo, *num, min, max, fuel, i;

    num = leerCangrejo("crab.txt", &tamanyo);

    /* Mostramos el resultado */
    for(i=0; i<tamanyo; i++){
        printf("%d, ", num[i]);
    }

    calcminMax(num, tamanyo, &min, &max);
    printf("\nmin=%d, max=%d\n", min, max);

    fuel=calcFuel(num, tamanyo, min, max);
    printf("How much fuel must they spend to align to that position? %d\n", fuel);

    /* Liberamos memoria */
    free(num);
    return 1;
}

int* leerCangrejo(char *nombre_fichero, int *tamanyo){

    FILE *f;
    int i, *num;
    char car;

    /* Abrimos el fichero */
    f=fopen(nombre_fichero, "r");
    if(f==NULL){
        printf("Error abriendo fichero.\n");
        return 0;
    }

    /* Contamos las comas para saber cuantos numeros hay */
    for(i=0, *tamanyo=0; fscanf(f, "%c", &car)==1; ){
        if(car==','){
            i++;
        }
    }
    *tamanyo=i+1; /* printf("tamanyo=%d\n", i); */

    /* Reservamos memoria para num */
    num=(int*)calloc(*tamanyo, sizeof(int));
    if(num==NULL){
        printf("Error reservando memoria.\n");
        return NULL;
    }

    /* Guardamos los numeros en un array */
    fseek(f, 0, SEEK_SET);
    for(i=0; i<*tamanyo; i++){
        fscanf(f, "%d", &num[i]);
        fscanf(f, "%c", &car);
    }

    /* Cerramos el fichero */
    fclose(f);
    return &num[0];
}

void calcminMax(int *num, int tamanyo, int *min, int *max){

    int i;

    *min=num[0];
    *max=num[0];

    for(i=0; i<tamanyo; i++){
        if(num[i]>*max){
            *max=num[i];
        }
        if(num[i]<*min){
            *min=num[i];
        }
    }
}

int calcFuel(int *num, int tamanyo, int min, int max){

    int i, j, fuel[max-min], minFuel, suma;

    /* Calculamos fuel para todas las cantidades máximas y mínimas de movimiento */
    for(i=min; i<=max; i++){
        fuel[i]=0;
        for(j=0, suma=0; j<tamanyo; j++){
            if(num[j]-i>=0){
                suma=num[j]-i;
                fuel[i]+=(suma*(suma+1))/2;
            }else{
                suma=i-num[j];
                fuel[i]+=(suma*(suma+1))/2;
            }
        }
    }

    /* Calculamos la menor cantidad de fuel */
    minFuel=fuel[0];
    for(i=0; i<max-min; i++){
        if(fuel[i]<minFuel){
            minFuel=fuel[i];
        }
    }

    return minFuel;
}