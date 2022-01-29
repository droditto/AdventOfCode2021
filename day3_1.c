#include <stdio.h>
#include <string.h>

#define TAM_CAD 13
#define TAM_INT 12

int main(){

    FILE *f;
    int position[TAM_INT];
    int i, j, gamma_rate10, epsilon_rate10;
    char list[TAM_CAD], gamma_rate2[TAM_CAD], epsilon_rate2[TAM_CAD];

    /* Abrimos el fichero */
    f=fopen("diagnostic.txt", "r");
    if(f==NULL){
        printf("Error abriendo fichero.\n");
        return -1;
    }

    /* Inicializamos postion a 0 */
    for(i=0;i<TAM_INT;i++){
        position[i]=0;
    }
    
    /* Contamos las veces que se repite 1 en cada posición */
    while(fgets(list, TAM_CAD, f)){
        for(i=0;list[i]!=0;i++){
            if(list[i]=='1'){
                position[i]++;
            }
        }
    }

    /* Calculamos gamma rate en binario */
    for(i=0;i<TAM_INT;i++){
        if(position[i] > 500){
            gamma_rate2[i]='1';
        } else {
            gamma_rate2[i]='0';
        }
    }
    gamma_rate2[TAM_CAD-1]='\0';

    /* Calculamos epsilon rate en binario */
    for(i=0;gamma_rate2[i]!=0;i++){
        if(gamma_rate2[i] == '1'){
            epsilon_rate2[i]='0';
        } else {
            epsilon_rate2[i]='1';
        }
    }
    epsilon_rate2[TAM_CAD-1]='\0';

    /* Calculamos gamma y epsilon en decimal */
    for(i=0,j=1;gamma_rate2[i]!=0;i++,j*=2){
        gamma_rate10+=j*(gamma_rate2[TAM_CAD-2-i]-'0');
        epsilon_rate10+=j*(epsilon_rate2[TAM_CAD-2-i]-'0');
    }
    /* printf("%s\n%s\n", gamma_rate2, epsilon_rate2); */
    /* printf("%d\n%d\n", gamma_rate10, epsilon_rate10); */
    printf("Power consumption: %d\n", gamma_rate10*epsilon_rate10);

    fclose(f);
    return 0;
}