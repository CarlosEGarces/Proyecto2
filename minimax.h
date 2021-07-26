#include "salida.h"

#define MIN -1
#define MAX 1
#define max(a, b) ((a > b)?a:b)
#define min(a, b) ((a < b)?a:b)

// LLamada inicial: minimax(tablero, jugadorComputadora, -2, 2, MAX, &columna);
int minimax(Tablero *tablero, int jugador, int alfa, int beta, int modo, int *jugada){
    if(evaluarTablero(tablero, jugador))
        return -1 * modo;
    if(estaLleno(tablero))
        return 0;
    int valor, aux, columna;
    if(modo == MAX){
        valor = aux = -2;
        for(int i = 0; i < tablero->columnas; ++i){
            if(realizarJugada(tablero, i, 2)){
                valor = max(valor, minimax(tablero, 2, alfa, beta, MIN, jugada));
                if(aux != valor){
                    columna = i;
                    aux = valor;
                }
                revertirJugada(tablero, i);
                if(valor >= beta)
                    break;
                alfa = max(alfa, valor);
            }
        }
    }else{ // modo == MIN
        valor = aux = 2;
        for(int i = 0; i < tablero->columnas; ++i){
            if(realizarJugada(tablero, i, 1)){
                valor = min(valor, minimax(tablero, 1, alfa, beta, MAX, jugada));
                if(aux != valor){
                    columna = i;
                    aux = valor;
                }
                revertirJugada(tablero, i);
                if(valor <= alfa)
                    break;
                beta = min(beta, valor);
            }
        }
    }
    *jugada = columna;
    return valor;
}