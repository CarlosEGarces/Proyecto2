#include <stdio.h>
#include <stdlib.h>
#include "minimax.h"

int main(int argc, char const *argv[]){
    Tablero *tablero = inicializarTablero(4, 4);
    int p = 1, aux = 2;
    int columna;

    system("clear");
    while(!estaLleno(tablero)){
        imprimirTablero(tablero);

        printf("\nJugador %i: Ingrese la columna:\n>>> ", p);
        scanf("%i", &columna);
        printf("\n");

        if(columna == 10){
            printf("minimax: %i\n", minimax(tablero, p, -2, 2, MAX, &columna));
            printf("columna: %i\n", ++columna);
        }

        if((columna < 1 || columna > tablero->columnas)){
            printf("Columna invalida, intente con otra.\n");
            continue;
        }

        if(!realizarJugada(tablero, columna-1, p)){
            printf("Columna llena, intente con otra.\n");
            continue;
        }

        if(evaluarTablero(tablero, p)){
            printf("Gano el jugador %i\n", p);
            break;
        }
    
        p ^= aux;
        aux ^= p;
        p ^= aux;
    }

    imprimirTablero(tablero);

    return 0;
}
