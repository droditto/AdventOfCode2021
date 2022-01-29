#include <stdio.h>
#include <string.h>

#define INT 12
#define CAD 13

int main(){

    FILE *f;
    //int position[TAM_INT];
    int i, j, pos, oneCount, ceroCount, posCheck;
    int Oxygen_10, CO2_10;
    char current[CAD], Oxygen_2[CAD], CO2_2[CAD];

    /* Abrimos el fichero */
    f=fopen("diagnostic.txt", "r");
    if(f==NULL){
        printf("Error abriendo fichero.\n");
        return -1;
    }




    /* ######### Resolver oxygen generator rating ######### */
    /* Para todas las posiciones */
    for(pos=0; pos<CAD-1; pos++){
        /* Recorremos el fichero */
        for(oneCount=0, ceroCount=0; fscanf(f, "%s", current)==1; ){
            /* Comprobamos que las posiciones anteriores a la actual coinciden */
            for(i=0, posCheck=0; i<pos; i++){
                if(current[i]==Oxygen_2[i]){
                    posCheck++;
                }
            }
            /* En ese caso, contamos los ceros y unos de la actual posicion */
            if(posCheck == pos){
                if(current[i]=='1'){
                    oneCount++;
                } else if(current[i]=='0') {
                    ceroCount++;
                }
            }
        }

        if( (ceroCount==0&&oneCount==1) || (ceroCount==1&&oneCount==0) ){ /* Si solo queda un numero */
            /* Volver al principio del fichero */
            fseek(f, 0, SEEK_SET);
            /* Leer toda la lista hasta llegar a ese numero */
            for( ; fscanf(f, "%s", current)==1; ){
                for(i=0, posCheck=0; i<pos; i++){
                    if(current[i]==CO2_2[i]){
                        posCheck++;
                    }
                }
                /* Copiar ese numero y salir */
                if(posCheck==pos){
                    strcpy(Oxygen_2, current);
                }
            }
        } else {
            /* Vemos que numero predomina y lo guardamos en Oxygen_2 */
            if(oneCount >= ceroCount){
                Oxygen_2[pos]='1';
            } else {
                Oxygen_2[pos]='0';
            }
        }
        
        /* Volver al principio del fichero */
        fseek(f, 0, SEEK_SET);
    }
    Oxygen_2[CAD-1]=0;




    /* ######### Resolver CO2 scrubber rating ######### */
    /* Para todas las posiciones */
    for(pos=0; pos<CAD-1; pos++){
        /* Recorremos el fichero */
        for(oneCount=0, ceroCount=0; fscanf(f, "%s", current)==1; ){
            /* Comprobamos que las posiciones anteriores a la actual coinciden */
            for(i=0, posCheck=0; i<pos; i++){
                if(current[i]==CO2_2[i]){
                    posCheck++;
                }
            }
            /* En ese caso, contamos los ceros y unos de la actual posicion */
            if(posCheck == pos){
                if(current[i]=='1'){
                    oneCount++;
                } else if(current[i]=='0') {
                    ceroCount++;
                }
            }
        }

        
        if( (ceroCount==0&&oneCount==1) || (ceroCount==1&&oneCount==0) ){ /* Si solo queda un numero */
            /* Volver al principio del fichero */
            fseek(f, 0, SEEK_SET);
            /* Leer toda la lista hasta llegar a ese numero */
            for( ; fscanf(f, "%s", current)==1; ){
                for(i=0, posCheck=0; i<pos; i++){
                    if(current[i]==CO2_2[i]){
                        posCheck++;
                    }
                }
                /* Copiar ese numero y salir */
                if(posCheck==pos){
                    strcpy(CO2_2, current);
                }
            }
        }else{
            /* Vemos que numero predomina y lo guardamos en Oxygen_2 */
            if(ceroCount <= oneCount){
                CO2_2[pos]='0';
            } else {
                CO2_2[pos]='1';
            }
        }
        /* Volver al principio del fichero */
        fseek(f, 0, SEEK_SET);
    }
    CO2_2[CAD-1]=0;





    /* Binario a decimal */
    for(i=0,j=1;Oxygen_2[i]!=0;i++,j*=2){
        Oxygen_10+=j*(Oxygen_2[11-i]-'0');
        CO2_10+=j*(CO2_2[11-i]-'0');
    }

    /* printf("%s\n%s\n", Oxygen_2, CO2_2); */
    /* printf("%d\n%d\n", Oxygen_10, CO2_10); */
    printf("Life support rating: %d\n", Oxygen_10*CO2_10);

    fclose(f);
    return 0;
}