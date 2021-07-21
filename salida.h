#include <stdio.h>
#include "libreria.h"

// Caracteres para imprimir el tablero
// ar = arriba; ab = abajo;
// i | ii = izquierda; d | dd = derecha;
// xxxx = horizontal (3 veces); yyyy = verical;
// cruz = centro; T = forma de T;
#define ar_i "\u2554"
#define ar_d "\u2557"
#define ab_i "\u255A"
#define ab_d "\u255D"
#define cruz "\u256C"
#define T_ar "\u2566"
#define T_ab "\u2569"
#define T_ii "\u2560"
#define T_dd "\u2563"
#define xxxx "\u2550\u2550\u2550"
#define yyyy "\u2551"

static void imprimerEnumeracion(int size){
    printf(ar_i);
    for(int i = 0; i < size * 2 - 1; ++i){
        if(i & 1)
            printf(T_ar);
        else
            printf(xxxx);
    }
    printf(ar_d);
    printf("\n");
    
    for(int i = 0; i < size * 2 + 1; ++i){
        if(i & 1)
            printf(" %i ", (i + 1) >> 1);
        else
            printf(yyyy);
    }
    printf("\n");

    printf(ab_i);
    for(int i = 0; i < size * 2 - 1; ++i){
        if(i & 1)
            printf(T_ab);
        else
            printf(xxxx);
    }
    printf(ab_d);

    printf("\n");
}

void imprimirTablero(Tablero *tablero){
    imprimerEnumeracion(tablero->filas);
    
    printf(ar_i);
    for(int i = 0; i < tablero->filas * 2 - 1; ++i){
        if(i & 1)
            printf(T_ar);
        else
            printf(xxxx);
    }
    printf(ar_d);
    printf("\n");

    for(int i = 0; i < tablero->filas*2-1; ++i){
        if(i & 1){
            printf(T_ii);
            for(int j = 0; j < tablero->columnas * 2 - 1; ++j){
                if(j & 1)
                    printf(cruz);
                else
                    printf(xxxx);
            }
            printf(T_dd);
        }else{
            for(int j = 0; j < tablero->columnas * 2 + 1; ++j){
                if(j & 1)
                    printf(" %c ", tablero->tablero[i/2][(j - 1)/2]);
                else
                    printf(yyyy);
            }
        }
        printf("\n");
    }

    printf(ab_i);
    for(int i = 0; i < tablero->filas * 2 - 1; ++i){
        if(i & 1)
            printf(T_ab);
        else
            printf(xxxx);
    }
    printf(ab_d);
    printf("\n");
}


// Usar esta funcion en caso de que la anterior no funcione

/*
void imprimirTablero(Tablero *tablero){
    for (int i = 0; i < tablero->columnas; ++i)
        printf("|%i", i + 1);
    printf("|\n");
    for (int i = 0; i < tablero->columnas; ++i)
    {
        for (int j = 0; j < tablero->filas; ++j)
        {
            printf("|%c", tablero->tablero[i][j]);
        }
        printf("|\n");
    }
}
*/