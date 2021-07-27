#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "minimax.h"

int determinarProfundidad(int filas, int columnas);

int main(int argc, char const *argv[]){
    Tablero *tablero = inicializarTablero(4, 4);
    int p = 1, aux = 2;
    int columna;

    // int profundidad = (int)floor((tablero->filas + tablero->columnas)/2.0);
    int profundidad = 6;

    int vector[8];

    system("clear");
    while(!estaLleno(tablero)){
        imprimirTablero(tablero);

        if(p == 1){
            printf("\nJugador %i: Ingrese la columna:\n>>> ", p);
            scanf("%i", &columna);
            printf("\n");

            columna--;

        }else{
            minimax(tablero, p, profundidad, &columna, vector);
        }

        if((columna < 0 || columna > tablero->columnas - 1)){
            printf("Columna invalida, intente con otra.\n");
            continue;
        }

        if(!realizarJugada(tablero, columna, p)){
            printf("Columna llena, intente con otra.\n");
            continue;
        }

        if(verificarGanador(tablero, columna, 4, vector)){
            printf("Gano el jugador %i\n", p);
            for(int i = 0; i < 8; i+=2)
                printf("{%i, %i}\n", vector[i], vector[i + 1]);
            break;
        }
    
        p ^= aux;
        aux ^= p;
        p ^= aux;
    }

    imprimirTablero(tablero);

    return 0;
}
