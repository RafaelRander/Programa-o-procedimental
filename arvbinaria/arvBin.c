#include <stdio.h>
#include <stdlib.h>
#include "arvBin.h"


Arv arv_cria_vazia(){

    return NULL;

}

Arv arv_cria(int c, Arv e, Arv d){

    Arv no = (Arv) malloc (sizeof(NoArv));
    no->info = c;
    no->esq = e;
    no->dir = d;
    return no;

}

void libera_no(Arv no){

    if(no==NULL)
        return;
    libera_no(no->esq);
    libera_no(no->dir);
    free(no);
    no = NULL;

}

Arv libera_arv(Arv a){

    if(!arv_vazia(a)){

        libera_arv(a->esq);
        libera_arv(a->dir);
        free(a);

    }

    return NULL;

}

int arv_vazia(Arv no){

        return (no == NULL);

}

int pertence_arv(Arv arv, int num){

    if(arv_vazia(arv))
        return 0;
    else
        return (arv->info==num||pertence_arv(arv->esq, num)||pertence_arv(arv->dir, num));

}

void arv_imprime_pre(Arv a){

    if(!arv_vazia(a)){
        printf("%d", (a->info));
        arv_imprime_pre(a->esq);
        arv_imprime_pre(a->dir);

    }

}

void arv_imprime_em(Arv a){

    if(!arv_vazia(a)){
        arv_imprime_pre(a->esq);
        printf("%d", (a->info));
        arv_imprime_pre(a->dir);

    }

}

void arv_imprime_pos(Arv a){

    if(!arv_vazia(a)){
        arv_imprime_pre(a->esq);
        arv_imprime_pre(a->dir);
        printf("%d", (a->info));

    }

}

int max(int a, int b){

    if(a>b)
        return a;
    else
        return b;

}

int arv_altura(Arv arv){

    if(arv_vazia(arv))
        return -1;
    else
        return 1 + max(arv_altura(arv->esq), arv_altura(arv->dir));

}

Arv arv_insere(int num, Arv raiz){

    NoArv* aux;
    if(arv_vazia(raiz)){

        aux=(NoArv*)malloc(sizeof(NoArv));
        aux->info = num;
        aux->esq = NULL;
        aux->dir = NULL;
        return aux;

    } else if(num<raiz->info){

        raiz->esq = arv_insere(num, raiz->esq);

    }else {

        raiz->dir = arv_insere(num, raiz->dir);

    }

    return raiz;

}

Arv arv_maior(Arv a){

    Arv aux;
    if(arv_vazia(a))
        return NULL;
    else{

        aux=a;
        while(!arv_vazia(aux->dir))
            aux=aux->dir;

    }

    return aux;

}

Arv arv_remove(int num, Arv arv){

    Arv aux;
    if(arv_vazia(arv))
        return NULL;
    else if(num==arv->info){

        if(arv_vazia(arv->esq)&&arv_vazia(arv->dir)){

            free(arv);
            return NULL;

        } else if(arv_vazia(arv->esq)){

            aux = arv;
            arv = arv->dir;
            free(aux);

        } else if(arv_vazia(arv->dir)){

            aux = arv;
            arv=arv->esq;
            free(aux);

        } else{

            aux=arv_maior(arv->esq);
            arv->info=aux->info;
            arv->esq=arv_remove(aux->info, arv->esq);

    }

    }else if(num<arv->info)
            arv->esq = arv_remove(num, arv->esq);
    else
          arv->dir = arv_remove(num, arv->dir);
     return arv;

}






