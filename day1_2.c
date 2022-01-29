#include <stdio.h>

#define TAM 2000

int main(){

    FILE *f;
    int i, x, num, report[TAM], sum[TAM];

    /* Inicializamos sum a 0 */
    for(i=0; i<TAM; i++){
        sum[i]=0;
    }

    f = fopen("report.txt", "r");
    if(f == NULL) {
        printf("Error abriendo el fichero\n");
        return -1;
    }

    /* Guardar report.txt en un array */
    for(i=0; fscanf(f, "%d", &num) == 1; i++){
        report[i]=num;
    }

    /* Calculamos sums */
    for(i=0; i<TAM; i++){
        /* Asumo que la basura es negativa */
        if(report[i]>0 && report[i+1]>0 && report[i+2]>0)
            sum[i]=report[i]+report[i+1]+report[i+2];
    }

    /* Buscamos cuales son mayores que el anterior */
    /* Asumo que no hay sum = 0 */
    for(i=1, x=0; sum[i]!=0; i++){
        if(sum[i]>sum[i-1]){
            x++;
        }
    }

    printf("There are %d sums that are larger than the previous sum.\n", x);

    fclose(f);
    return 0;
}