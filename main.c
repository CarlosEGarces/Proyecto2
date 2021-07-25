#include <stdio.h>
#include <stdlib.h>
#include "salida.h"

int main(int argc, char const *argv[]){
    Tablero *tablero = inicializarTablero(5, 4);
    int p = 1, aux = 2;
    int columna;

    system("clear");
    while(!estaLleno(tablero)){
        imprimirTablero(tablero);

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

    imprimirTablero(tablero);

    return 0;
}
