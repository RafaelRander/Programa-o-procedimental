#include <stdio.h>
#include <stdlib.h>

int exponencial(int n){

    //caso base.
    if(n==0)
        return 1;
    //chamadas recursivas para n>1
    return 2 * exponencial(n-1);

}

int fatorial(int n){

     int total = 1;
     for(int i = n; i>0;i--){
        //caso queira calcular o fatorial para um numero negativo irá retornar 0.
        if(n<0)
            return 0;
        //calculando a iteração
        total = i*total;
        }
        return total;

}

int main(){

    int n = 0, resultado = 0;
    printf("Digite um valor inteiro:");
    //recebendo um valor inteiro de n
    scanf("%d", &n);
    //fazendo a chamada da função exponencial passando n como parametro e armazenando o valor em resultado.
    resultado = exponencial(n);
    //imprimindo o resultado.
    printf("resultado exponencial = %d", resultado);
    //fazendo a chamada da função fatorial passando n como parametro e armazenando o valor em resultado.
    resultado = fatorial(n);
    //imprimindo o resultado.
    printf("\nresultado fatorial = %d", resultado);

    return 0;

}
