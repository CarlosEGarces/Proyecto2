#include <stdio.h>
#include <stdlib.h>

typedef struct _jugador{
    int turno;
    char nombre[15];
    char *color;
}Jugador;

typedef struct _tablero{
    int filas;
    int columnas;
    int **tablero;
}Tablero;

Tablero *inicializarTablero(int filas, int columnas){
    Tablero *tablero = NULL;

    tablero = (Tablero*)calloc(1, sizeof(Tablero));
    if(tablero == NULL){
        fprintf(stderr, "Error al inicializar el tablero: falla en malloc.\n");
        exit(1);
    }

    tablero->filas = filas;
    tablero->columnas = columnas;

    tablero->tablero = (int**)calloc(tablero->filas, sizeof(int*));
    if(tablero->tablero == NULL){
        fprintf(stderr, "Error al inicializar el tablero: falla en malloc.\n");
        exit(1);
    }

    for(int i = 0; i < tablero->columnas; ++i){
        tablero->tablero[i] = (int*)calloc(tablero->columnas, sizeof(int));
        if(tablero->tablero[i] == NULL){
            fprintf(stderr, "Error al inicializar el tablero: falla en malloc.\n");
            exit(1);
        }
    }

    return tablero;
}

// Retorna 0 si pudo realizar la jugada, de lo contrario,
// retorna 1 (Columna llena)
int realizarJugada(Tablero *tablero, int columna, int jugador){
    for(int i = tablero->filas-1; i >= 0; --i){
        if(tablero->tablero[i][columna] == 0){
            tablero->tablero[i][columna] = jugador;
            return 0;
        }
    }
    return 1;
}

void reiniciarTablero(Tablero *tablero){
    for(int i = 0; i < tablero->filas; ++i)
        for(int j = 0; j < tablero->columnas; ++j)
            tablero->tablero[i][j] = 0;
}

int estaLleno(Tablero *tablero){
    for(int i = 0; i < tablero->columnas; ++i)
        if(!tablero->tablero[0][i])
            return 0;
    return 1;
}