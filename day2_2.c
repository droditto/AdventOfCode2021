#include <stdio.h>
#include <string.h>

#define TAM 16

int main(){
    
    FILE *f;
    char palabra[TAM];
    int depth, forward, aim, numero;
    
    f=fopen("commands.txt", "r");
    if(f==NULL){
        printf("Error abriendo fichero\n");
        return -1;
    }
    
    for(depth=0,forward=0,aim=0; fscanf(f, "%s %d", palabra, &numero) == 2; ){

        if(strcmp(palabra, "forward") == 0){
            forward+=numero;
            depth+=aim*numero;
        } else if(strcmp(palabra, "down") == 0){
            aim+=numero;
        } else if(strcmp(palabra, "up") == 0){
            aim-=numero;
        }
    }
    
    printf("forward=%d depth=%d\nforward*depth=%d\n", forward, depth, forward*depth);

    return 0;
}