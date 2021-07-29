#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minimax.h"

int determinarProfundidad(int filas, int columnas, int cantidadJugadas);



int main(int argc, char const *argv[]){
    Tablero *tablero = crearTablero(5, 5);
    int p = 1, aux = 2, cantidadJugadas = 0;
    int columna, profundidad, vector[8];

    strcpy(jugadores[0].nombre, "CPU1");
    jugadores[0].turno = 1;

    strcpy(jugadores[1].nombre, "CPU2");
    jugadores[1].turno = 2;

    profundidad = 6;
    system("clear");
    while(!estaLleno(tablero)){
        imprimirTablero(tablero);

        jugadores[p-1].mode = MAX;
        jugadores[aux-1].mode = MIN;
        minimax(tablero, p, profundidad, &columna, vector);

        if((columna < 0 || columna > tablero->columnas - 1)){
            printf("Columna invalida, intente con otra.\n");
            continue;
        }

        if(!realizarJugada(tablero, columna, p)){
            printf("Columna llena, intente con otra.\n");
            continue;
        }

        if(verificarGanador(tablero, columna, 4, vector)){
            printf("Gano el jugador %s\n", jugadores[p-1].nombre);
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
