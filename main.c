#include <stdio.h>
#include <stdlib.h>
#include "salida.h"

int main(int argc, char const *argv[]){
    Tablero *tablero = inicializarTablero(5, 5);
    char p = 'X', aux = 'O';
    int columna;

    system("clear");
    while(!estaLleno(tablero)){
        imprimirTableroV2(tablero);

        printf("\nIngrese la columna:\n>>> ");
        scanf("%i", &columna);
        printf("\n");

        if(!(1 <= columna < tablero->columnas)){
            printf("Columna invalida, intente con otra.\n");
            continue;
        }

        if(realizarJugada(tablero, columna-1, p)){
            printf("Columna llena, intente con otra.\n");
            continue;
        }

        p ^= aux;
        aux ^= p;
        p ^= aux;
    }
    system("clear");

    imprimirTableroV2(tablero);
    return 0;
}
