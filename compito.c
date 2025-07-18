#include "bst.h"
#include "hotel.h"

void load_bst_from_file(bst* hotels, char* filename);
void stampa(bst hotels);

int main(){
    bst hotels = NULL;
    load_bst_from_file(&hotels, "hotel.txt");
    stampa(hotels);

    printf("\n\n");
    return 0;
}

void load_bst_from_file(bst* hotels, char* filename){
    bst tmp_hotels = *hotels;
    char* mode = "r";

    FILE* fp_hotel = fopen(filename, mode);
    if(!fp_hotel){printf("\nERRORE"); exit(EXIT_FAILURE);}

    //leggo il file
    char buffer[100]; 

    //la prima riga contiene il numero totale di hotel da leggere
    if(fgets(buffer, 100, fp_hotel) == NULL){printf("\nERRORE"); fclose(fp_hotel); exit(EXIT_FAILURE);}
    int totHotels; 
    if(sscanf(buffer, " %d[^\n]", &totHotels) != 1){printf("\nRIGA NON VALIDA"); fclose(fp_hotel); exit(EXIT_FAILURE);}
    //printf("\nHotel totali: %d", totHotels);

    //posso leggere gli hotel
    for(int i=1; i<=totHotels; i++){
        //printf("\nLETTURA HOTEL %d", i);
        //per ogni hotel leggo 3 righe 
        tipo_key stelle = 0; 
        tipo_inf tmp; 

        //leggo le stelle
        if(fgets(buffer, 100, fp_hotel) == NULL) {printf("\nERRORE"); fclose(fp_hotel); exit(EXIT_FAILURE);}
        if(sscanf(buffer, " %d[^\n]", &stelle) != 1){printf("\nRIGA NON VALIDA"); fclose(fp_hotel); exit(EXIT_FAILURE);}

        //leggo il nome 
        if(fgets(buffer, 100, fp_hotel) == NULL) {printf("\nERRORE"); fclose(fp_hotel); exit(EXIT_FAILURE);}
        strcpy(tmp.nome, buffer);

        //leggo il luogo
        if(fgets(buffer, 100, fp_hotel) == NULL) {printf("\nERRORE"); fclose(fp_hotel); exit(EXIT_FAILURE);}
        strcpy(tmp.luogo, buffer);

        //l'hotel letto lo inserisco nel bst 
        //printf("\nInserisco l'hotel %s in %s a %d stelle", tmp.nome, tmp.luogo, stelle);
        bst_insert(&tmp_hotels, bst_newNode(stelle, tmp));

    }

    if(fclose(fp_hotel) == EOF){printf("\nERRORE"); exit(EXIT_FAILURE);}
    *hotels = tmp_hotels;
}

void stampa(bst hotel){
    //stampa in ordine decrescente per stelle
    if(hotel != NULL){
        stampa(hotel->left); //stampo le stelle più grandi

        print_tipo_inf(hotel->inf);
        printf("Numero stelle: %d", hotel->key);

        stampa(hotel->right); //poi quelle più piccole
    }

}