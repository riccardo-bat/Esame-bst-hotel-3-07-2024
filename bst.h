#ifndef BST_H
#define BST_H

#include "hotel.h"    /* per tipo_inf */

/* Chiave numerica */
typedef int tipo_key;

/* Forward declaration per il nodo */
typedef struct bnode bnode;

/* Nodo dell’albero binario di ricerca */
struct bnode {
    tipo_key   key; //stelle dell'hotel
    tipo_inf   inf;
    bnode     *left;
    bnode     *right;
    bnode     *parent;
};

/* Radice dell’albero */
typedef bnode* bst;

/* --- Prototipi delle funzioni --- */

/**
 * Crea un nuovo nodo con chiave k e valore i.
 * I puntatori left/right/parent vengono inizializzati a NULL.
 */
bnode *bst_newNode(tipo_key k, tipo_inf i);

/** Restituisce la chiave del nodo n */
tipo_key get_key(const bnode *n);

/** Restituisce il valore (tipo_inf) del nodo n */
tipo_inf get_value(const bnode *n);

/** Restituisce il sottoalbero sinistro di t */
bst get_left(bst t);

/** Restituisce il sottoalbero destro di t */
bst get_right(bst t);

/** Restituisce il padre del nodo n */
bnode *get_parent(const bnode *n);

/**
 * Inserisce il nodo n nell’albero *t.
 * Se la radice cambia, ne aggiorna il puntatore *t.
 */
void bst_insert(bst *t, bnode *n);

/** Stampa la chiave k (adatta al tuo tipo_key) */
void print_key(tipo_key k);

/**
 * Cerca nel BST t il nodo con chiave k.
 * Restituisce il puntatore al nodo o NULL se non trovato.
 */
bnode *bst_search(bst t, tipo_key k);

/**
 * Elimina il nodo n dall’albero *t.
 * Se rimuove la radice, ne aggiorna il puntatore *t.
 */
void bst_delete(bst *t, bnode *n);

#endif /* BST_H */
