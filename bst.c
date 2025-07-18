// bst.c

#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "hotel.h"   // per copy(), compare(), print_tipo_inf(), ecc.

/* Copia la chiave k in *dest e la restituisce */
static tipo_key copy_key(tipo_key *dest, tipo_key k) {
    *dest = k;
    return *dest;
}

/* Confronta due chiavi */
static int compare_key(tipo_key a, tipo_key b) {
    return b - a;
}

/* Stampa la chiave */
void print_key(tipo_key k) {
    printf("%d", k);
}

/* Accessori */
tipo_key  get_key(const bnode *n)    { return n->key; }
tipo_inf  get_value(const bnode *n)  { return n->inf; }
bst       get_left(bst t)            { return t ? t->left  : NULL; }
bst       get_right(bst t)           { return t ? t->right : NULL; }
bnode    *get_parent(const bnode *n) { return n ? n->parent : NULL; }

/* Crea un nuovo nodo */
bnode *bst_newNode(tipo_key k, tipo_inf i) {
    bnode *n = malloc(sizeof *n);
    if (!n) { perror("malloc"); exit(EXIT_FAILURE); }
    copy(&n->inf, i);
    copy_key(&n->key, k);
    n->left = n->right = n->parent = NULL;
    return n;
}

/* Inserimento in BST */
void bst_insert(bst *bp, bnode *n) {
    bnode *x = *bp, *y = NULL;
    while (x) {
        y = x;
        if (compare_key(get_key(n), get_key(x)) < 0)
            x = x->left;
        else
            x = x->right;
    }
    n->parent = y;
    if (!y) {
        *bp = n;
    }
    else if (compare_key(get_key(n), get_key(y)) < 0) {
        y->left = n;
    } else {
        y->right = n;
    }
}

/* Ricerca in BST */
bnode *bst_search(bst b, tipo_key k) {
    while (b) {
        int cmp = compare_key(k, get_key(b));
        if (cmp == 0)      return b;
        else if (cmp < 0)  b = b->left;
        else               b = b->right;
    }
    return NULL;
}

/* Aggiorna il puntatore del padre di p su q */
static void update_father(bnode *p, bnode *q) {
    bnode *par = p->parent;
    if (!par) return;
    if (par->left == p)  par->left  = q;
    else                  par->right = q;
    if (q) q->parent = par;
}

/* Cancellazione da BST */
void bst_delete(bst *bp, bnode *n) {
    bnode *child = NULL;

    if (!n->left) {
        /* Zero o un figlio a destra */
        child = n->right;
    }
    else if (!n->right) {
        /* Solo figlio sinistro */
        child = n->left;
    }
    else {
        /* Due figli: prendi il predecessore (max nel sottoalbero sinistro) */
        bnode *pred = n->left;
        while (pred->right)
            pred = pred->right;
        /* Copia pred in n */
        copy(&n->inf, pred->inf);
        copy_key(&n->key, pred->key);
        /* Elimina pred al suo posto */
        n = pred;
        child = n->left ? n->left : n->right;
    }

    if (child)
        child->parent = n->parent;

    if (!n->parent) {
        /* n era radice */
        *bp = child;
    } else {
        update_father(n, child);
    }

    free(n);
}
