#include <stdio.h>

#define TAM 990
#define DIM 8

void setDiagram(int diagram[TAM][TAM]){
    int i, j;

    for(i=0;i<TAM;i++){
        for(j=0;j<TAM;j++){
            diagram[i][j]=0;
        }
    }
}

void showDiagram(int diagram[TAM][TAM]){
    int i, j;

    for(i=0;i<TAM;i+=10){
        for(j=0;j<TAM;j+=10){
            printf("%d", diagram[i][j]);
        }
        printf("\n");
    }
}

void fillVertical(int x1, int y1, int y2, int diagram[TAM][TAM]){
    int i;
    if(y1<=y2){
        for(i=y1;i<=y2;i++){
            diagram[i][x1]++;
        }
    }else if(y1>y2){
        for(i=y2;i<=y1;i++){
            diagram[i][x1]++;
        }
    }
    
}

void fillHorizontal(int x1, int x2, int y1, int diagram[TAM][TAM]){
    int i;

    if(x1<=x2){
        for(i=x1;i<=x2;i++){
            diagram[y1][i]++;
        }
    }else if(x1>x2){
        for(i=x2;i<=x1;i++){
            diagram[y1][i]++;
        }
    }
    
}

int overlapCount(int diagram[TAM][TAM]){
    int i, j, count=0;

    for(i=0;i<TAM;i++){
        for(j=0;j<TAM;j++){
            if(diagram[i][j] >= 2){
                count++;
            }
        }
    }

    return count;
}

int main(){

    FILE *f;
    int diagram[TAM][TAM];
    int x1, y1, x2, y2, i;

    f=fopen("lines.txt", "r");
    if(f==NULL){
        printf("Error abriendo fichero.\n");
        return -1;
    }

    setDiagram(diagram);

    for(i=0 ; fscanf(f, "%d,%d -> %d,%d", &x1, &y1, &x2, &y2)==4; i++){

        printf("%d)\t%d,%d -> %d,%d\n", i+1,x1,y1,x2,y2);
        
        if(x1==x2){
            fillVertical(x1, y1, y2, diagram);
        }else if(y1==y2){
            fillHorizontal(x1, x2, y1, diagram);
        }
        
    }
    
    showDiagram(diagram);
    printf("%d points\n", overlapCount(diagram));

    fclose(f);
    return 0;
}