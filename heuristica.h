#include "salida.h"

#define ALTO 100
#define MEDIO 50
#define BAJO 10
#define SIN_PUNTUACION 0

//    1           2           3           4
// _XXX_      X_XX_       _X_XX_       _XX_X_      100      
// _XXX        XXX_      XX_X       X_XX          50
// _XX_         X_X_        _X_X        XX__        __XX       10

static int puntuacionHeuristica(int j, int v1, int v2, int v3, int v4, int v5){
    if(v1 == 0 && v2 == j && v3 == j && v4 == j && v5 == 0)
        return ALTO;
        
    if(v1 == 0 && v2 == j && v3 == j && v4 == j)
        return MEDIO;
    if(v1 == j && v2 == j && v3 == j && v4 == 0)
        return MEDIO;
    if(v1 == j && v2 == j && v3 == 0 && v4 == j)
        return MEDIO;
    if(v1 == j && v2 == 0 && v3 == j && v4 == j)
        return MEDIO;

    if(v1 == 0 && v2 == j && v3 == j && v4 == 0)
        return BAJO;
    if(v1 == j && v2 == 0 && v3 == j && v4 == 0)
        return BAJO;
    if(v1 == 0 && v2 == j && v3 == 0 && v4 == j)
        return BAJO;
    if(v1 == 0 && v2 == 0 && v3 == j && v4 == j)
        return BAJO;
    if(v1 == j && v2 == j && v3 == 0 && v4 == 0)
        return BAJO;

    return SIN_PUNTUACION;
}

static int puntuacionHorizontal(Tablero *tablero, int jugador){
    int puntuacion = 0;
    int v1, v2, v3, v4, v5;
    for(int i = 0; i < tablero->filas; ++i){
        for(int j = 0; j < tablero->columnas - 4; ++j){
            v1 = tablero->tablero[i][j];
            v2 = tablero->tablero[i][j + 1];
            v3 = tablero->tablero[i][j + 2];
            v4 = tablero->tablero[i][j + 3];
            v5 = -1;
            if(j + 4 < tablero->columnas)
                v5 = tablero->tablero[i][j + 4];
            puntuacion += puntuacionHeuristica(jugador, v1, v2, v3, v4, v5);
        }
    }
    return puntuacion;
}

static int puntuacionVertical(Tablero *tablero, int jugador){
    int puntuacion = 0;
    int v1, v2, v3, v4, v5;
    for(int i = 0; i < tablero->filas - 4; ++i){
        for(int j = 0; j < tablero->columnas; ++j){
            v1 = tablero->tablero[i][j];
            v2 = tablero->tablero[i + 1][j];
            v3 = tablero->tablero[i + 2][j];
            v4 = tablero->tablero[i + 3][j];
            v5 = -1;
            if(i + 4 < tablero->filas)
                v5 = tablero->tablero[i + 4][j];
            puntuacion += puntuacionHeuristica(jugador, v1, v2, v3, v4, v5);
        }
    }
    return puntuacion;
}

static int puntuacionDiagonalPrincipal(Tablero *tablero, int jugador){
    int puntuacion = 0;
    int v1, v2, v3, v4, v5;
    for(int i = 0; i < tablero->filas - 3; ++i){
        for(int j = 0; j < tablero->columnas - 3; ++j){
            v1 = tablero->tablero[i][j];
            v2 = tablero->tablero[i + 1][j + 1];
            v3 = tablero->tablero[i + 2][j + 2];
            v4 = tablero->tablero[i + 3][j + 3];
            v5 = -1;
            if(j + 4 < tablero->columnas && i + 4 < tablero->filas)
                v5 = tablero->tablero[i + 4][j + 4];
            puntuacion += puntuacionHeuristica(jugador, v1, v2, v3, v4, v5);
        }
    }
    return puntuacion;
}

static int puntuacionDiagonalSecundaria(Tablero *tablero, int jugador){
    int puntuacion = 0;
    int v1, v2, v3, v4, v5;
    for(int i = 0; i < tablero->filas - 3; ++i){
        for(int j = tablero->columnas - 1; j > tablero->columnas - 3; --j){
            v1 = tablero->tablero[i][j];
            v2 = tablero->tablero[i + 1][j - 1];
            v3 = tablero->tablero[i + 2][j - 2];
            v4 = tablero->tablero[i + 3][j - 3];
            v5 = -1;
            if(i + 4 < tablero->filas && j - 4 < tablero->columnas)
                v5 = tablero->tablero[i + 4][j - 4];
            puntuacion += puntuacionHeuristica(jugador, v1, v2, v3, v4, v5);
        }
    }
    return puntuacion;
}

// Buscar las jugadas en todo el tablero
static int costo(Tablero *tablero, int jugador){
    int puntuacion = 0;

    puntuacion += puntuacionHorizontal(tablero, jugador);
    puntuacion += puntuacionVertical(tablero, jugador);
    puntuacion += puntuacionDiagonalPrincipal(tablero, jugador);
    puntuacion += puntuacionDiagonalSecundaria(tablero, jugador);

    return puntuacion;
}

int valorHeuristico(Tablero *tablero){
    return costo(tablero, 2) - costo(tablero, 1);
}