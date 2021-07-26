#include "salida.h"

#define MIN -1
#define MAX 1
#define max(a, b) ((a > b)?a:b)
#define min(a, b) ((a < b)?a:b)

int minimax(Tablero *tablero, int jugador, int modo, int *jugada){
    if(evaluarTablero(tablero, jugador))
        return -1 * modo;
    if(estaLleno(tablero))
        return 0;
    int valor, aux, columna;
    if(modo == MAX){
        valor = aux = -2;
        for(int i = 0; i < tablero->columnas; ++i){
            if(realizarJugada(tablero, i, 2)){
                valor = max(valor, minimax(tablero, 2, MIN, jugada));
                if(aux != valor){
                    columna = i;
                    aux = valor;
                }
                revertirJugada(tablero, i);
            }
        }
    }else{ // modo == MIN
        valor = aux = 2;
        for(int i = 0; i < tablero->columnas; ++i){
            if(realizarJugada(tablero, i, 1)){
                valor = min(valor, minimax(tablero, 1, MAX, jugada));
                if(aux != valor){
                    columna = i;
                    aux = valor;
                }
                revertirJugada(tablero, i);
            }
        }
    }
    *jugada = columna;
    return valor;
}