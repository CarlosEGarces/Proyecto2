#include <stdio.h>
#include "tablero.h"

#define fisheye "\u25C9"

// Colores
#define RESET    "\x1b[0m"
#define ROJO     "\033[1;31m"
#define VERDE    "\033[1;32m"
#define AMARILLO "\033[1;33m"
#define AZUL     "\033[1;34m"
#define ROSA     "\033[1;35m"
#define CYAN     "\033[1;36m"
#define BLANCO   "\033[1;37m"
#define NARANJA  "\033[0;33m"
#define MORADO   "\033[0;35m"

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
    imprimerEnumeracion(tablero->columnas);
    
    printf(ar_i);
    for(int i = 0; i < tablero->columnas * 2 - 1; ++i){
        if(i & 1)
            printf(T_ar);
        else
            printf(xxxx);
    }
    printf(ar_d);
    printf("\n");

    for(int i = 0; i < tablero->filas * 2 - 1; ++i){
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
                if(j & 1){
                    if(tablero->tablero[i/2][(j - 1)/2] == 0){
                        printf("   ");
                    }else{
                        if(tablero->tablero[i / 2][(j - 1) / 2] == 1)
                            printf(" %s%s%s ", ROJO, fisheye, RESET);
                        else
                            printf(" %s%s%s ", AMARILLO, fisheye, RESET);
                    }
                }else{
                    printf(yyyy);
                }
            }
        }
        printf("\n");
    }

    printf(ab_i);
    for(int i = 0; i < tablero->columnas * 2 - 1; ++i){
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