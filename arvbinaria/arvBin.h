#ifndef ARVBIN_H_INCLUDED
#define ARVBIN_H_INCLUDED

typedef struct noArv{

    int info;
    struct noArv* esq;
    struct noArv* dir;

}NoArv;

typedef struct noArv* Arv;

Arv arv_cria_vazia();
Arv arv_cria(int num, NoArv* e, NoArv* d);
void libera_no(Arv no);
Arv libera_arv(Arv raiz);
int arv_vazia(Arv no);
int pertence_arv(Arv raiz, int num);
void arv_imprime_pre(Arv raiz);
void arv_imprime_pos(Arv raiz);
void arv_imprime_em(Arv raiz);
int max(int a, int b);
int arv_altura(Arv arv);
Arv arv_insere(int num, Arv raiz);
Arv arv_remove(int num, Arv raiz);

#endif // ARVBIN_H_INCLUDED
