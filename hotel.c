#include "hotel.h"

void copy(tipo_inf* dest, tipo_inf source){
    *dest = source; 
}

int compare(tipo_inf a, tipo_inf b){
    int cmp = strcmp(a.nome, b.nome);
    if(cmp != 0) return cmp; 

    cmp = strcmp(a.luogo, b.luogo); 
    return cmp; 
}

void print_tipo_inf(tipo_inf obj){
    printf("\nL'hotel %s, situato in %s", obj.nome, obj.luogo);
}