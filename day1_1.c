#include <stdio.h>

int main(){

    FILE *f;
    int x, numero, anterior;

    f = fopen("report.txt", "r");
    if(f == NULL) {
        printf("Error abriendo el fichero\n");
        return -1;
    }

    for(x=0, anterior=0, numero=0; fscanf(f, "%d", &numero) == 1; ){
        if(numero > anterior){
            x++;
        }
        anterior = numero;
    }

    printf("There are %d measurements that are larger than the previous measurement.\n", x-1);

    fclose(f);
    return 0;
}