#include <stdlib.h>
#include <time.h>
#include "heuristica.h"

#define INFINITO 100001
#define MIN -10000
#define MAX 10000
#define EMPATE 0
#define max(a, b) ((a > b)?a:b)
#define min(a, b) ((a < b)?a:b)

int minimax(int profundidad, int *jugada);
static int _minimax(int profundidad, int columna, int alfa, int beta, int modo, int *jugada);
int determinarProfundidad(int filas, int columnas, int cantidadJugadas);

static int _minimax(int profundidad, int columna, int alfa, int beta, int modo, int *jugada){
    if(verificarGanador(columna))
        return -1 * modo;
    if(tableroEstaLleno())
        return EMPATE;
    if(profundidad == 0)
        return valorHeuristico(MAX, MIN);
    int valor, aux, columnaJugada, n = config.columnas;
    int jugador = obtenerJugador(modo);
    if(modo == MAX){ // modo == MAX
        valor = aux = -INFINITO;
        for(int j = 0, i = rand() % n; j < n; ++j, i = (i + 1) % n){
            if(realizarJugada(i, jugador)){
                valor = max(valor, _minimax(profundidad - 1, i, alfa, beta, MIN, jugada));
                if(aux != valor){
                    columnaJugada = i;
                    aux = valor;
                }
                revertirJugada(i);
                if(valor >= beta)
                    break;
                alfa = max(alfa, valor);
            }
        }
    }else{ // modo == MIN
        valor = aux = INFINITO;
        for(int i = 0, j = rand() % n; i < n; ++i, j = (j + 1) % n){
            if(realizarJugada(i, jugador)){
                valor = min(valor, _minimax(profundidad - 1, i, alfa, beta, MAX, jugada));
                if(aux != valor){
                    columnaJugada = i;
                    aux = valor;
                }
                revertirJugada(i);
                if(valor <= alfa)
                    break;
                beta = min(beta, valor);
            }
        }
    }
    *jugada = columnaJugada;
    return valor;
}

int minimax(int profundidad, int *jugada){
    srand(time(0));
    return _minimax(profundidad, -1, -INFINITO, INFINITO, MAX, jugada);
}

int determinarProfundidad(int filas, int columnas, int cantidadJugadas){
    if(config.dificultad = 0)
        return 1;
    if(config.dificultad = 1)
        return 2;
    int d = filas * columnas - cantidadJugadas;
    if(d < 10)
        return 8;
    if(d < 25)
        return 6;
    if(d < 36)
        return 4;
    return 2;
}