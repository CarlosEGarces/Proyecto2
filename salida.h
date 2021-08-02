#include <stdio.h>
#include "tablero.h"

#define fisheye "\u25C9"

// Resetear color
const char * const RESET = "\x1b[0m";

// Colores
const char * const ROJO = "\033[1;31m";
const char * const VERDE = "\033[1;32m";
const char * const AMARILLO = "\033[1;33m";
const char * const AZUL = "\033[1;34m";

// Colores de fondo
const char * const BG_ROJO = "\033[1;31;47m";
const char * const BG_VERDE = "\033[1;32;47m";
const char * const BG_AMARILLO = "\033[1;33;47m";
const char * const BG_AZUL = "\033[1;34;47m";

// Caracteres para imprimir el tablero
// ar = arriba; ab = abajo;
// i | ii = izquierda; d | dd = derecha;
// xxxx = horizontal (3 veces); yyyy = verical;
// cruz = centro; T = forma de T;
const char * const ar_i = "\u2554";
const char * const ar_d = "\u2557";
const char * const ab_i = "\u255A";
const char * const ab_d = "\u255D";
const char * const cruz = "\u256C";
const char * const T_ar = "\u2566";
const char * const T_ab = "\u2569";
const char * const T_ii = "\u2560";
const char * const T_dd = "\u2563";
const char * const xxxx = "\u2550\u2550\u2550";
const char * const yyyy = "\u2551";

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

void imprimirTablero(int vector[]){
    imprimerEnumeracion(config.columnas);
    
    printf(ar_i);
    for(int i = 0; i < config.columnas * 2 - 1; ++i){
        if(i & 1)
            printf(T_ar);
        else
            printf(xxxx);
    }
    printf(ar_d);
    printf("\n");

    for(int i = 0; i < config.filas * 2 - 1; ++i){
        if(i & 1){
            printf(T_ii);
            for(int j = 0; j < config.columnas * 2 - 1; ++j){
                if(j & 1)
                    printf(cruz);
                else
                    printf(xxxx);
            }
            printf(T_dd);
        }else{
            for(int j = 0; j < config.columnas * 2 + 1; ++j){
                if(j & 1){
                    if(tablero[i][j] == 0)
                        printf("   ");
                    else{
                        :{>}"?ASG"
                    }
                }else{
                    printf(yyyy);
                }
            }
        }
        printf("\n");
    }

    printf(ab_i);
    for(int i = 0; i < config.columnas * 2 - 1; ++i){
        if(i & 1)
            printf(T_ab);
        else
            printf(xxxx);
    }
    printf(ab_d);
    printf("\n");
}


// Usar esta funcion en caso de que la anterior no funcione

void imprimirTablero(){
    for (int i = 0; i < config.columnas; ++i)
        printf("|%i", i + 1);
    printf("|\n");
    for (int i = 0; i < config.columnas; ++i)
    {
        for (int j = 0; j < config.filas; ++j){
            if(tablero[i][j] == 1)
                putchar('X');
            else if(tablero[i][j] == 2)
                putchar('O');
            else
                putchar(' ');
        }
        printf("|\n");
    }
}
