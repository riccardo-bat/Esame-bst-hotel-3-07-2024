#include "bst.h"
#include "hotel.h"
#include <stdbool.h>

//prototipi
long int int_input(char* msg, int minimum_value, int max_value);
char* string_input(char* msg, int max_length);
void load_bst_from_file(bst* hotels, char* filename);
void stampa(bst hotels);
void ricerca(bst hotels, int threshold_stars, bool maggiori);
int media(bst hotels, int threshold_stars, char* luogo);

int main(){
    bst hotels = NULL;
    load_bst_from_file(&hotels, "hotel.txt");
    stampa(hotels);

    //punto 2a
    printf("\n\n-----------------------------------");
    int threshold_stars = (int) int_input("\nInserire la soglia delle stelle: ", 1, 5);
    bool maggiori = (bool) int_input("\n1 = stampare stelle maggiori della soglia inserita, 0 altrimenti: ", 0, 1);

    ricerca(hotels, threshold_stars, maggiori);


    //punto 2b
    printf("\n\n-----------------------------------");
    char* luogo = string_input("\nInserire il luogo: ", 20);
    printf("\nNumero di hotel con #stelle > %d situati a %s: %d", threshold_stars, luogo, media(hotels, threshold_stars, luogo));


    printf("\n\n");
    return 0;
}

/**
 * @brief Funzione per l'acquisizione di un long int da terminale
 * 
 * @param msg 
 * @param minimum_value 
 * @param max_value 
 * @return long int 
 */
long int int_input(char* msg, int minimum_value, int max_value){
    long int input;
    char buffer[100];

    printf("%s", msg);
    while(fgets(buffer, sizeof(buffer), stdin) == NULL) {
        printf("\nErrore nella lettura dell'input. Riprova: ");
    }

    char *endptr;
    input = strtol(buffer, &endptr, 10);
    if (endptr == buffer || *endptr != '\n' || input < minimum_value || input > max_value) {
        printf("\nInput non valido\n.");
        return int_input(msg, minimum_value, max_value);
    }

    return input;
}

/**
 * @brief Funzione per l'acquisizione di una stringa da terminale
 * 
 */
char* string_input(char* msg, int max_length){
    printf("%s", msg); 
    char* buffer = malloc(max_length * sizeof(char));
    if(!buffer){printf("\n\nMalloc failed"); exit(EXIT_FAILURE);} 

    while(fgets(buffer, max_length, stdin) == NULL){
        printf("\nInput fallito\n");
    }

    buffer[strcspn(buffer, "\r\n")] = '\0';
    return buffer;
}

/**
 * @brief Funzione per il caricamento di un bst da un file testuale
 * 
 * @param hotels 
 * @param filename 
 */
void load_bst_from_file(bst* hotels, char* filename){
    bst tmp_hotels = *hotels;
    char* mode = "r";

    FILE* fp_hotel = fopen(filename, mode);
    if(!fp_hotel){printf("\nERRORE"); exit(EXIT_FAILURE);}

    //leggo il file
    char buffer[100]; 

    //la prima riga contiene il numero totale di hotel da leggere
    if(fgets(buffer, 100, fp_hotel) == NULL){printf("\nERRORE"); fclose(fp_hotel); exit(EXIT_FAILURE);}
    buffer[strcspn(buffer, "\r\n")] = '\0';
    int totHotels; 
    if(sscanf(buffer, " %d", &totHotels) != 1){printf("\nRIGA NON VALIDA"); fclose(fp_hotel); exit(EXIT_FAILURE);}
    //printf("\nHotel totali: %d", totHotels);

    //posso leggere gli hotel
    for(int i=1; i<=totHotels; i++){
        //printf("\nLETTURA HOTEL %d", i);
        //per ogni hotel leggo 3 righe 
        tipo_key stelle = 0; 
        tipo_inf tmp; 

        //leggo le stelle
        if(fgets(buffer, 100, fp_hotel) == NULL) {printf("\nERRORE"); fclose(fp_hotel); exit(EXIT_FAILURE);}
        buffer[strcspn(buffer, "\r\n")] = '\0';
        if(sscanf(buffer, " %d", &stelle) != 1){printf("\nRIGA NON VALIDA"); fclose(fp_hotel); exit(EXIT_FAILURE);}

        //leggo il nome 
        if(fgets(buffer, 100, fp_hotel) == NULL) {printf("\nERRORE"); fclose(fp_hotel); exit(EXIT_FAILURE);}
        buffer[strcspn(buffer, "\r\n")] = '\0';
        strcpy(tmp.nome, buffer);

        //leggo il luogo
        if(fgets(buffer, 100, fp_hotel) == NULL) {printf("\nERRORE"); fclose(fp_hotel); exit(EXIT_FAILURE);}
        buffer[strcspn(buffer, "\r\n")] = '\0';
        strcpy(tmp.luogo, buffer);

        //l'hotel letto lo inserisco nel bst 
        //printf("\nInserisco l'hotel %s in %s a %d stelle", tmp.nome, tmp.luogo, stelle);
        bst_insert(&tmp_hotels, bst_newNode(stelle, tmp));

    }

    if(fclose(fp_hotel) == EOF){printf("\nERRORE"); exit(EXIT_FAILURE);}
    *hotels = tmp_hotels;
}

/**
 * @brief Procedura di stampa di un bst in ordine decrescente
 * 
 * @param hotel 
 */
void stampa(bst hotel){
    //stampa in ordine decrescente per stelle
    if(hotel != NULL){
        stampa(hotel->left); //stampo le stelle più grandi

        print_tipo_inf(hotel->inf);
        printf(". Numero stelle: %d", hotel->key);

        stampa(hotel->right); //poi quelle più piccole
    }

}

/**
 * @brief Stampa degli hotel con stelle > threshold se maggiori = true, altrimenti gli hotel con un #stelle <= threshold
 * 
 * @param hotels 
 * @param threshold_stars 
 * @param maggiori 
 */
void ricerca(bst hotels, int threshold_stars, bool maggiori){
    if(hotels != NULL){
        if(maggiori && hotels->key > threshold_stars) print_tipo_inf(hotels->inf);
        else if(!maggiori && hotels->key <= threshold_stars) print_tipo_inf(hotels->inf);
        //else --> non stampa

        if(hotels->key > threshold_stars && maggiori){
            ricerca(hotels->left, threshold_stars, maggiori);
            ricerca(hotels->right, threshold_stars, maggiori); //mi permette di non perdere eventuali hotel
        } else if(hotels->key > threshold_stars && !maggiori){
            ricerca(hotels->right, threshold_stars, maggiori);
        } else if(hotels->key <= threshold_stars && maggiori){
            ricerca(hotels->left, threshold_stars, maggiori);
            ricerca(hotels->right, threshold_stars, maggiori);
        } else{
            ricerca(hotels->left, threshold_stars, maggiori);
            ricerca(hotels->right, threshold_stars, maggiori); //mi permette di non perdere eventuali hotel

        }

    }

}

/**
 * @brief Funzione che conta il numero di hotel con #stelle > soglia e che si trovano nel luogo passato per parametro
 * 
 * @param hotels 
 * @param threshold_stars 
 * @param luogo 
 * @return int 
 */
int media(bst hotels, int threshold_stars, char* luogo){
    if(hotels == NULL) return 0;

    //se la root è minore della soglia, è inutile andare a dx
    if(hotels->key < threshold_stars){
        return media(hotels->left, threshold_stars, luogo);
    } else{
        if(strcmp(hotels->inf.luogo, luogo) == 0 && hotels->key > threshold_stars)
            return 1 + media(hotels->left, threshold_stars, luogo) + media(hotels->right, threshold_stars, luogo);
        else return media(hotels->left, threshold_stars, luogo) + media(hotels->right, threshold_stars, luogo);
    }
}