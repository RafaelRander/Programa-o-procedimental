#include <stdio.h>
#include <stdlib.h>

void troca(int *n1, int *n2){
    int aux = *n1;
    *n1 = *n2;
    *n2 = aux;
}

int* bubleSort(int *v, int n){

    int i = 0, j = 0, count = 0;
    for(i=0;i<n;i++){
        for(j=0;j<n-1;j++){
            if(v[j]>v[j+1]){
                troca(&v[j], &v[j+1]);
                count++;
            }
        }
        if(count == 0)
            return v;
        n--;
    }
    return v;

}

int main(){

    int v[] = {2,7,1,0,8,9,3}, i=0;
    bubleSort(v, 7);
    for(i=0;i<7;i++){
        printf("valor na posicao %d = %d\n", i, v[i]);
    }
    return 0;
}




