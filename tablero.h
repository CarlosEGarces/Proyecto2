#include <stdio.h>
#include <stdlib.h>

typedef struct _tablero{
    int filas;
    int columnas;
    char **tablero;
}Tablero;

Tablero *inicializarTablero(int filas, int columnas){
    Tablero *tablero = NULL;

    tablero = (Tablero*)malloc(sizeof(Tablero));
    if(tablero == NULL){
        fprintf(stderr, "Error al inicializar el tablero: falla en malloc.\n");
        exit(1);
    }

    tablero->filas = filas;
    tablero->columnas = columnas;

    tablero->tablero = (char**)malloc(sizeof(char*)*tablero->columnas);
    if(tablero->tablero == NULL){
        fprintf(stderr, "Error al inicializar el tablero: falla en malloc.\n");
        exit(1);
    }

    unsigned long size = sizeof(char) * tablero->filas;
    for(int i = 0; i < tablero->columnas; ++i){
        tablero->tablero[i] = (char*)malloc(size);
        if(tablero->tablero[i] == NULL){
            fprintf(stderr, "Error al inicializar el tablero: falla en malloc.\n");
            exit(1);
        }
    }

    for(int i = 0; i < tablero->columnas; ++i)
        for(int j = 0; j < tablero->filas; ++j)
            tablero->tablero[i][j] = ' ';
            
    return tablero;
}

int realizarJugada(Tablero *tablero, int columna, char jugador){
    for(int i = tablero->filas-1; i >= 0; --i){
        if(tablero->tablero[i][columna] == ' '){
            tablero->tablero[i][columna] = jugador;
            return 0;
        }
    }
    return 1;
}

void reiniciarTablero(Tablero *tablero){
    for(int i = 0; i < tablero->columnas; ++i)
        for(int j = 0; j < tablero->filas; ++j)
            tablero->tablero[i][j] = ' ';
}

int estaLleno(Tablero *tablero){
    for(int i = 0; i < tablero->columnas; ++i){
        if(tablero->tablero[0][i] == ' ')
            return 0;
    }
    return 1;
}