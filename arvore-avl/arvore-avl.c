#include <stdio.h>
#include <stdlib.h>
#include "arvore-avl.h"
#include "../arvore-binaria-de-busca/arvbin_busca.h"

#define MAX(a,b) ((a)>(b)?(a):(b))
#define ALT(a) ((a == NULL)?(-1):(a->altura))

nodo * rotate_left (nodo* n) {
    nodo * q = n->dir;
    n->dir = q->esq;
    if (q->esq != NULL) {
        q->esq->pai = n;
    }
    q->esq = n;
    q->pai = n->pai;
    n->pai = q;
    n->altura = 1 + MAX(ALT(n->esq), ALT(n->dir));
    q->altura = 1 + MAX(ALT(q->esq), ALT(q->dir));
    return q;
}

nodo * rotate_right (nodo* n) {
    nodo * q = n->esq;
    n->esq = q->dir;
    if (q->dir != NULL) {
        q->dir->pai = n;
    }
    q->dir = n;
    q->pai = n->pai;
    n->pai = q;
    n->altura = 1 + MAX(ALT(n->esq), ALT(n->dir));
    q->altura = 1 + MAX(ALT(q->esq), ALT(q->dir));
    return q;
}   

nodo * rotate_left_right (nodo* n) {
    n->esq = rotate_left(n->esq);
    return rotate_right(n);
}

nodo * rotate_right_left (nodo* n) {
    n->dir = rotate_right(n->dir);
    return rotate_left(n);
}

nodo * avl_balance (nodo *n) {
    int fb = ALT(n->dir) - ALT(n->esq); // fator de balanceamento
    nodo * y = n;

    if (fb < -1) { // subárvore esquerda está mais alta
        if (ALT(n->esq->esq) >= ALT(n->esq->dir)) {
            y = rotate_right(n);
        } else {
            y = rotate_left_right(n);
        }
    } else if (fb > 1) { // subárvore direita está mais alta
        if (ALT(n->dir->dir) >= ALT(n->dir->esq)) {
            y = rotate_left(n);
        } else {
            y = rotate_right_left(n);
        }
    }

    return y;
}

void avl_insert (arvore *A, nodo *n) {
    int a;
    nodo *x, *y;

    n -> altura = 0;
    x = tree_insert(A, n);

    while(x != NULL) {
        a = 1 + MAX(ALT(x->esq), ALT(x->dir));
        y = avl_balance(x);   

        if(y != x) {
            transplant(A, x, y);
            break;
        }

        if(x->altura == a)
            break;

        x->altura = a;
        x = x->pai;
    }    
}

void avl_delete (arvore *A, nodo *n) {
    int fb, a;
    nodo *x, *y, *p;
    
    x = tree_delete(A, n);

    while(x != NULL) {
        a = 1 + MAX(ALT(x->esq), ALT(x->dir));
        y = avl_balance(x);

        if(y != x) {
            transplant(A, x, y);
            x = y;
        }

        if(x->altura == a)
            break;

        x->altura = a;
        x = x->pai;
    }        

}