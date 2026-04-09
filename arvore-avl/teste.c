#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "arvore-avl.h"
#include "../arvore-binaria-de-busca/arvbin_busca.h"

int main () {
    arvore *A;
    // inicializa a árvore AVL, alocando memória para ela e setando a raiz como NULL
    assert(tree_build(&A));

    // cria alguns nodos para inserir na árvore AVL
    nodo *n1, *n2, *n3, *n4, *n5;
    assert(nodo_build(&n1, 10, NULL));
    assert(nodo_build(&n2, 20, NULL));
    assert(nodo_build(&n3, 30, NULL));
    assert(nodo_build(&n4, 40, NULL));
    assert(nodo_build(&n5, 50, NULL));

    // insere os nodos na árvore AVL, mantendo as propriedades da árvore AVL
    avl_insert(A, n1);
    avl_insert(A, n2);
    avl_insert(A, n3);
    avl_insert(A, n4);
    avl_insert(A, n5);

    fprintf(stderr, "Árvore AVL em ordem: ");
    inorder_tree_walk(A->raiz);
    fprintf(stderr, "\n");

    tree_free(A);

    return 0;