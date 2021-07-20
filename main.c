#include <stdio.h>
#include <stdlib.h>
#include "libreria.h"


int main(int argc, char const *argv[]){
    Tablero *tablero = inicializarTablero(5, 5);
    char p = 'X', aux = 'O';
    int columna;

    system("clear");
    while(!estaLleno(tablero)){
        imprimirTablero(tablero);

        printf("\nIngrese la columna:\n>>> ");
        scanf("%i", &columna);
        printf("\n");

        if(!(1 <= columna < tablero->columnas)){
            printf("Columna invalida, intente con otra.");
            continue;
        }

        if(realizarJugada(tablero, columna-1, p)){
            printf("Columna llena, intente con otra.");
            continue;
        }

        p ^= aux;
        aux ^= p;
        p ^= aux;
    }
    system("clear");

    imprimirTablero(tablero);
    return 0;
}
