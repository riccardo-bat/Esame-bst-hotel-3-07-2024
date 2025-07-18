#ifndef HOTEL_H
    #define HOTEL_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    typedef struct tipo_inf{
        char nome[21]; //20 + terminatore
        char luogo[21]; //20 + terminatore
    } tipo_inf;

    void copy(tipo_inf* dest, tipo_inf source);
    int compare(tipo_inf a, tipo_inf b); 
    void print_tipo_inf(tipo_inf obj);

#endif