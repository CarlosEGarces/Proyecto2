#include <stdio.h>
#include <stdlib.h>

typedef struct _tablero{
    int filas;
    int columnas;
    char **tablero;
}Tablero;

void inicializarTablero(Tablero *tablero, int filas, int columnas){
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
}

void imprimirTablero(Tablero *tablero){
    for(int i = 0; i < tablero->columnas + 2; ++i)
        printf("|%c", i + 65);
    printf("|");
    for(int i = 0; i < tablero->columnas; ++i){
        for(int j = 0; j < tablero->filas; ++j){
            printf("|%c");
        }
        printf("|\n");
    }
}

int realizarJugada(Tablero *tablero, int columna, char jugador){
    int fila = tablero->filas;
    while(tablero->tablero[columna][fila] != ' ' && fila >= 0)
        fila--;
    if(tablero->tablero[columna][fila] == ' '){
        tablero->tablero[columna][fila] = jugador;
        return 0;
    }
    return 1;
}

void reiniciarTablero(Tablero *tablero){
    for(int i = 0; i < tablero->columnas; ++i)
        for(int j = 0; j < tablero->filas; ++j)
            tablero->tablero[i][j] = ' ';
}