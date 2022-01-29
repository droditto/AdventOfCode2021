#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 200
#define TAM 14
#define DIM 8


int main(){

    FILE *f;
    char input[TAM][DIM], car;
    int specialDigits, i, j, size;

    f=fopen("digit.txt", "r");
    if(f==NULL){
        printf("Error abriendo fichero.\n");
        return 0;
    }

    for(specialDigits=0, i=0; i<SIZE; i++){
        
        for(j=0; j<10; j++){
            fscanf(f, "%s", input[j]);
            printf("%s ", input[j]);
        }

        fscanf(f, "%c", &car);
        printf("%c", car);

        for(j=10; j<14; j++){
            fscanf(f, "%s", input[j]);
            size=strlen(input[j]);
            if(size==2||size==4||size==3||size==7){
                specialDigits++;
                printf("\x1b[31m%s\x1b[0m ", input[j]);
            }else{
                printf("%s ", input[j]);
            }
        }



        printf("\n");
    }

    printf("%d\n", specialDigits);
    return 1;
}