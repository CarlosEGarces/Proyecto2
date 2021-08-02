#include <stdio.h>
#include <stdlib.h>
#include "salida.h"

struct{
    char nombre[16];
    const char *color;
    const char *bg_color;
    int mode;
}jugadores[2];

struct{
    int fila;
    int columna;
}coordenadas[4] = {
    {-1, -1},
    {-1, -1},
    {-1, -1},
    {-1, -1}
};

struct{
    int filas: 5; // Cantidad de filas del tablero
    int columnas: 5; // Cantidad de columnas del tablero
    int cantFichas: 3; // Cantidad de fichas en linea para ganar
    int dificultad: 3; // Dificultad de la IA
}config = {4, 4, 4, 0};

int **tablero = NULL;

int obtenerJugador(int mode){
    return (jugadores[1].mode == mode) + 1;
}

void inicializarTablero(){
    tablero = (int**)calloc(config.filas, sizeof(int*));

    if(tablero){
            fprintf(stderr, "Error en calloc.\n");
            exit(1);
    }

    for(int i = 0; i < config.filas; ++i){
        tablero[i] = (int*)calloc(config.columnas, sizeof(int));
        if(tablero[i] == NULL){
            fprintf(stderr, "Error en calloc.\n");
            exit(1);
        }
    }
}

// Retorna 1 si pudo realizar la jugada, de lo contrario,
// retorna 0 (Columna llena)
int realizarJugada(int columna, int jugador){
    for(int i = config.filas - 1; i >= 0; --i){
        if(tablero[i][columna] == 0){
            tablero[i][columna] = jugador;
            return 1;
        }
    }
    return 0;
}

void revertirJugada(int columna){
    for(int i = 0; i < config.filas; ++i)
        if(tablero[i][columna] != 0){
            tablero[i][columna] = 0;
            break;
        }
}

void vaciarTablero(){
    for(int i = 0; i < config.filas; ++i)
        for(int j = 0; j < config.columnas; ++j)
            tablero[i][j] = 0;
}

int tableroEstaLleno(){
    for(int i = 0; i < config.columnas; ++i)
        if(tablero[0][i] == 0)
            return 0;
    return 1;
}

void reiniciarTablero();

static int verificarHorizontal(int fila, int columna){
    int contador = 1, valorFicha = tablero[fila][columna];
    int diferencia = config.columnas - columna - 1;
    int indice = 0;

    coordenadas[indice++] = fila;
    coordenadas[indice++] = columna;

    for(int i = 1; i < diferencia + 1; ++i){ // Verifica a la derecha
        if(tablero[fila][columna + i] != valorFicha || contador == config.cantFichas)
            break;
        contador++;
        coordenadas[indice++] = fila;
        coordenadas[indice++] = columna + i;
    }
    diferencia = columna > config.cantFichas ? config.cantFichas - 1 : columna;
    for(int i = 1; i < diferencia + 1; ++i){ // Verifica a la izquierda
        if(tablero[fila][columna - i] != valorFicha || contador == config.cantFichas)
            break;
        contador++;
        coordenadas[indice++] = fila;
        coordenadas[indice++] = columna - i;
    }
    return contador == config.cantFichas;
}

static int verificarVertical(int fila, int columna){
    int contador = 1, valorFicha = tablero[fila][columna];
    int diferencia = config.filas - fila - 1;
    int indice = 0;

    coordenadas[indice++] = fila;
    coordenadas[indice++] = columna;

    for(int i = 1; i < diferencia + 1; ++i){
        if(tablero[fila + i][columna] != valorFicha || contador == config.cantFichas)
            break;
        contador++;
        coordenadas[indice++] = fila + i;
        coordenadas[indice++] = columna;
    }
    return contador == config.cantFichas;
}

// Arriba a la izquierda hacia abajo a la derecha
static int verificarDiagonalPrincipal(int fila, int columna){
    int diferenciaArriba, diferenciaAbajo, contador = 1;
    int valorFicha = tablero[fila][columna];
    int distanciaColumna = config.columnas - columna - 1;
    int distanciaFila = config.filas - fila - 1;
    int indice = 0;

    coordenadas[indice++] = fila;
    coordenadas[indice++] = columna;

    diferenciaArriba = columna > fila ? fila : columna;
    for(int i = 1; i < diferenciaArriba + 1; ++i){ // arriba a la izquierda
        if(tablero[fila - i][columna - i] != valorFicha || contador == config.cantFichas)
            break;
        contador++;
        coordenadas[indice++] = fila - i;
        coordenadas[indice++] = columna - i;
    }

    diferenciaAbajo = distanciaColumna > distanciaFila ? distanciaFila : distanciaColumna;
    for(int i = 1; i < diferenciaAbajo + 1; ++i){ // abajo a la derecha
        if(tablero[fila + i][columna + i] != valorFicha || contador == config.cantFichas)
            break;
        contador++;
        coordenadas[indice++] = fila + i;
        coordenadas[indice++] = columna + i;
    }

    return contador == config.cantFichas;
}

// Abajo a la izquierda hacia arriba a la derecha
static int verificarDiagonalSecundaria(int fila, int columna){
    int diferenciaArriba, diferenciaAbajo, contador = 1;
    int valorFicha = tablero[fila][columna];
    int distanciaColumna = config.columnas - columna - 1;
    int distanciaFila = config.filas - fila - 1;
    int indice = 0;

    coordenadas[indice++] = fila;
    coordenadas[indice++] = columna;

    diferenciaArriba = fila > distanciaColumna ? distanciaColumna : fila;
    for(int i = 1; i < diferenciaArriba + 1; ++i){ // arriba a la derecha
        if(tablero[fila - i][columna + i] != valorFicha || contador == config.cantFichas)
            break;
        contador++;
        coordenadas[indice++] = fila - i;
        coordenadas[indice++] = columna + i;
    }

    diferenciaAbajo = columna > distanciaFila ? distanciaFila : columna;
    for(int i = 1; i < diferenciaAbajo + 1; ++i){ // abajo a la izquierda
        if(tablero[fila + i][columna - i] != valorFicha || contador == config.cantFichas)
            break;
        contador++;
        coordenadas[indice++] = fila + i;
        coordenadas[indice++] = columna - i;
    }

    return contador == config.cantFichas;
}

static int verificarDiagonales(int fila, int columna){
    if(verificarDiagonalPrincipal(fila, columna, coordenadas))
        return 1;
    return verificarDiagonalSecundaria(fila, columna, coordenadas);
}

static void resetearCoordenadas(){
    for(int i = 0; i < 4; ++i){
        coordenadas[i].fila = -1;
        coordenadas[i].columna = -1;
    }
}

// Evalua el tablero y:
// retorna 1 si gano el ultimo jugador en jugar,
// de lo contrario, retorna 0 
int verificarGanador(int columna){
    if(columna < 0)
        return 0;
    for(int i = 0; i < config.filas; ++i){
        if(tablero[i][columna] != 0){
            resetearcoordenadas(coordenadas);
            if(verificarHorizontal(i, columna))
                return 1;

            resetearcoordenadas(coordenadas);
            if(verificarVertical(i, columna))
                return 1;

            resetearcoordenadas(coordenadas);
            if(verificarDiagonales(i, columna))
                return 1;

            break;
        }
    }
    return 0;
}