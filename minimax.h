#include <stdlib.h>
#include <time.h>
#include "heuristica.h"

#define INFINITO 10000
#define MIN -1000
#define MAX 1000
#define EMPATE 0
#define max(a, b) ((a > b)?a:b)
#define min(a, b) ((a < b)?a:b)

static int _minimax(Tablero *tablero, int profundidad, int jugador, int columna, int alfa, int beta, int modo, int *jugada, int vector[]){
    if(verificarGanador(tablero, columna, 4, vector))
        return -1 * modo;
    if(estaLleno(tablero))
        return EMPATE;
    if(profundidad == 0)
        return valorHeuristico(tablero);
    int valor, aux, columnaJugada, n = tablero->columnas;
    if(modo == MAX){ // modo == MAX
        valor = aux = -INFINITO;
        for(int j = 0, i = rand() % n; j < n; ++j, i = (i + 1) % n){
            if(realizarJugada(tablero, i, 2)){
                valor = max(valor, _minimax(tablero, profundidad - 1, 2, i, alfa, beta, MIN, jugada, vector));
                if(aux != valor){
                    columnaJugada = i;
                    aux = valor;
                }
                revertirJugada(tablero, i);
                if(valor >= beta)
                    break;
                alfa = max(alfa, valor);
            }
        }
    }else{ // modo == MIN
        valor = aux = INFINITO;
        for(int i = 0, j = rand() % n; i < n; ++i, j = (j + 1) % n){
            if(realizarJugada(tablero, i, 1)){
                valor = min(valor, _minimax(tablero, profundidad - 1, 1, i, alfa, beta, MAX, jugada, vector));
                if(aux != valor){
                    columnaJugada = i;
                    aux = valor;
                }
                revertirJugada(tablero, i);
                if(valor <= alfa)
                    break;
                beta = min(beta, valor);
            }
        }
    }
    *jugada = columnaJugada;
    return valor;
}

int minimax(Tablero *tablero, int jugador, int profundidad, int *jugada, int vector[]){
    srand(time(0));
    return _minimax(tablero, profundidad, jugador, -1, -INFINITO, INFINITO, MAX, jugada, vector);
}