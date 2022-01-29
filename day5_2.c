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

    for(i=0;i<TAM;i+=2){
        for(j=0;j<TAM;j+=2){
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

int look45Diagonal(int x1, int x2, int y1, int y2){
    int i;

    if(x1<x2&&y1<y2){
        for(i=0;x1<x2||y1<y2;i++){
            x1++;
            y1++;
            if(x1==x2&&y1==y2){
                return 1;
            }
        }
    }else if(x1>x2&&y1>y2){
        for(i=0;x1>x2||y1>y2;i++){
            x2++;
            y2++;
            if(x1==x2&&y1==y2){
                return 2;
            }
        }
    }else if(x1<x2&&y1>y2){
        for(i=0;x1<x2||y1>y2;i++){
            x1++;
            y2++;
            if(x1==x2&&y1==y2){
                return 3;
            }
        }
    }else if(x1>x2&&y1<y2){
        for(i=0;x1>x2||y1<y2;i++){
            x2++;
            y1++;
            if(x1==x2&&y1==y2){
                return 4;
            }
        }
    }
    return 0;
}

void fillDiagonal(int x1, int x2, int y1, int y2, int diagram[TAM][TAM]){
    int diagonal45, i, j;

    diagonal45=look45Diagonal(x1, x2, y1, y2);
    if(diagonal45==1){
        for(i=x1,j=y1;i<=x2;i++,j++){
            diagram[j][i]++;
        }
    }else if(diagonal45==2){
        for(i=x2,j=y2;i<=x1;i++,j++){
            diagram[j][i]++;
        }
    }else if(diagonal45==3){
        for(i=x1,j=y1;i<=x2;i++,j--){
            diagram[j][i]++;
        }
    }else if(diagonal45==4){
        for(i=x2,j=y2;i<=x1;i++,j--){
            diagram[j][i]++;
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

    for( ; fscanf(f, "%d,%d -> %d,%d", &x1, &y1, &x2, &y2)==4; ){
        
        if(x1==x2){
            fillVertical(x1, y1, y2, diagram);
        }else if(y1==y2){
            fillHorizontal(x1, x2, y1, diagram);
        }else{
            fillDiagonal(x1, x2, y1, y2, diagram);
        }
        
    }
    
    printf("%d points\n", overlapCount(diagram));

    fclose(f);
    return 0;
}