#include "tablero.h"

// Puntuaciones
#define ALTA 100
#define OTRA 75
#define MEDIA 50
#define BAJA 15
#define NADA 0

static int puntuacionHeuristica(int j, int v1, int v2, int v3, int v4, int v5){
    if(v1 == 0 && v2 == j && v3 == j && v4 == j && v5 == 0) // _XXX_
        return ALTA;

    if(v1 == j && v2 == 0 && v3 == j && v4 == j && v5 == j) // X_XXX
        return OTRA;
    if(v1 == j && v2 == j && v3 == j && v4 == 0 && v5 == j) // XXX_X
        return OTRA;

    if(v1 == 0 && v2 == j && v3 == j && v4 == j) // _XXX
        return MEDIA;
    if(v1 == j && v2 == j && v3 == j && v4 == 0) // XXX_
        return MEDIA;
    if(v1 == j && v2 == j && v3 == 0 && v4 == j) // XX_X
        return MEDIA;
    if(v1 == j && v2 == 0 && v3 == j && v4 == j) // X_XX
        return MEDIA;

    if(v1 == 0 && v2 == j && v3 == j && v4 == 0) // _XX_
        return BAJA;
    if(v1 == j && v2 == 0 && v3 == j && v4 == 0) // X_X_
        return BAJA;
    if(v1 == 0 && v2 == j && v3 == 0 && v4 == j) // _X_X
        return BAJA;
    if(v1 == 0 && v2 == 0 && v3 == j && v4 == j) // __XX
        return BAJA;
    if(v1 == j && v2 == j && v3 == 0 && v4 == 0) // XX__
        return BAJA;

    return NADA;
}


static int puntuacionHorizontal(int jugador){
    int puntuacion = 0;
    int v1, v2, v3, v4, v5;
    for(int i = 0; i < config.filas; ++i){
        for(int j = 0; j < config.columnas - (config.cantFichas - 1); ++j){
            v1 = tablero[i][j];
            v2 = tablero[i][j + 1];
            v3 = tablero[i][j + 2];
            v4 = tablero[i][j + 3];
            v5 = -1;
            if(j + 4 < config.columnas)
                v5 = tablero[i][j + 4];
            puntuacion += puntuacionHeuristica(jugador, v1, v2, v3, v4, v5);
        }
    }
    return puntuacion;
}

static int puntuacionVertical(int jugador){
    int puntuacion = 0;
    int v1, v2, v3, v4, v5;
    for(int i = 0; i < config.filas - (config.cantFichas - 1); ++i){
        for(int j = 0; j < config.columnas; ++j){
            v1 = tablero[i][j];
            v2 = tablero[i + 1][j];
            v3 = tablero[i + 2][j];
            v4 = tablero[i + 3][j];
            v5 = -1;
            if(i + 4 < config.filas)
                v5 = tablero[i + 4][j];
            puntuacion += puntuacionHeuristica(jugador, v1, v2, v3, v4, v5);
        }
    }
    return puntuacion;
}

static int puntuacionDiagonalPrincipal(int jugador){
    int puntuacion = 0;
    int v1, v2, v3, v4, v5;
    for(int i = 0; i < config.filas - (config.cantFichas - 1); ++i){
        for(int j = 0; j < config.columnas - (config.cantFichas - 1); ++j){
            v1 = tablero[i][j];
            v2 = tablero[i + 1][j + 1];
            v3 = tablero[i + 2][j + 2];
            v4 = tablero[i + 3][j + 3];
            v5 = -1;
            if(j + 4 < config.columnas && i + 4 < config.filas)
                v5 = tablero[i + 4][j + 4];
            puntuacion += puntuacionHeuristica(jugador, v1, v2, v3, v4, v5);
        }
    }
    return puntuacion;
}

static int puntuacionDiagonalSecundaria(int jugador){
    int puntuacion = 0;
    int v1, v2, v3, v4, v5;
    for(int i = 0; i < config.filas - (config.cantFichas - 1); ++i){
        for(int j = config.columnas - 1; j > config.columnas - (config.cantFichas - 1); --j){
            v1 = tablero[i][j];
            v2 = tablero[i + 1][j - 1];
            v3 = tablero[i + 2][j - 2];
            v4 = tablero[i + 3][j - 3];
            v5 = -1;
            if(i + 4 < config.filas && j - 4 < config.columnas)
                v5 = tablero[i + 4][j - 4];
            puntuacion += puntuacionHeuristica(jugador, v1, v2, v3, v4, v5);
        }
    }
    return puntuacion;
}

// Buscar las jugadas en todo el tablero
static int costo(int jugador){
    int puntuacion = 0;

    puntuacion += puntuacionHorizontal(jugador);
    puntuacion += puntuacionVertical(jugador);
    puntuacion += puntuacionDiagonalPrincipal(jugador);
    puntuacion += puntuacionDiagonalSecundaria(jugador);

    return puntuacion;
}

int valorHeuristico(int MAX, int MIN){
    return costo(obtenerJugador(MAX)) - costo(obtenerJugador(MIN));
}