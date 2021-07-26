#include <stdio.h>
#include <stdlib.h>

typedef struct _jugador{
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

    for(int i = 0; i < tablero->filas; ++i){
        tablero->tablero[i] = (int*)calloc(tablero->columnas, sizeof(int));
        if(tablero->tablero[i] == NULL){
            fprintf(stderr, "Error al inicializar el tablero: falla en malloc.\n");
            exit(1);
        }
    }

    return tablero;
}

// Retorna 1 si pudo realizar la jugada, de lo contrario,
// retorna 0 (Columna llena)
int realizarJugada(Tablero *tablero, int columna, int jugador){
    for(int i = tablero->filas-1; i >= 0; --i){
        if(tablero->tablero[i][columna] == 0){
            tablero->tablero[i][columna] = jugador;
            return 1;
        }
    }
    return 0;
}

void revertirJugada(Tablero *tablero, int columna){
    for(int i = 0; i < tablero->filas; ++i)
        if(tablero->tablero[i][columna] != 0){
            tablero->tablero[i][columna] = 0;
            break;
        }
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

int verificarHorizontal(Tablero *tablero, int fila, int columna){
    int cont = 1;
    if(columna + 3 < tablero->columnas){
        for(int i = 1; i < 4; ++i){
            if(tablero->tablero[fila][columna + i] != tablero->tablero[fila][columna])
                break;
            cont++;
        }
    }
    return cont == 4;
}

int verificarVertical(Tablero *tablero, int fila, int columna){
    int cont = 1;
    if(fila + 3 < tablero->filas){
        for(int i = 1; i < 4; ++i){
            if(tablero->tablero[fila + i][columna] != tablero->tablero[fila][columna])
                break;
            cont++;
        }
    }
    return cont == 4;
}

int verificarDiagonales(Tablero *tablero, int fila, int columna){
    int cont = 1;
    if(fila + 3 < tablero->filas){
        if(columna + 3 < tablero->columnas){
            for(int i = 1; i < 4; ++i){
                if(tablero->tablero[fila + i][columna + i] != tablero->tablero[fila][columna])
                    break;
                cont++;
            }
        }else if(columna - 3 >= 0){
            for(int i = 1; i < 4; ++i){
                if(tablero->tablero[fila + i][columna - i] != tablero->tablero[fila][columna])
                    break;
                cont++;
            }
        }
    }
    return cont == 4;
}

// Evalua el tablero y:
// retorna 1 si gano el ultimo jugador en jugar,
// de lo contrario, retorna 0 
int evaluarTablero(Tablero *tablero, int jugador){
    for(int i = 0; i < tablero->filas; ++i){
        for(int j = 0; j < tablero->columnas; ++j){
            if(tablero->tablero[i][j] == jugador){
                if(verificarHorizontal(tablero, i, j))
                    return 1;
                if(verificarVertical(tablero, i, j))
                    return 1;
                if(verificarDiagonales(tablero, i, j))
                    return 1;
            }
        }
    }
    return 0;
}