#include <stdio.h>
#include <stdlib.h>

struct{
    char nombre[15];
    char *color;
    int mode;
    int turno;
}jugadores[2];


int obtenerJugador(int mode){
    if(jugadores[0].mode == mode)
        return jugadores[0].turno;
    return jugadores[1].turno;
}

typedef struct _tablero{
    int filas;
    int columnas;
    int **tablero;
}Tablero;

Tablero *crearTablero(int filas, int columnas){
    Tablero *tablero = NULL;

    tablero = (Tablero*)calloc(1, sizeof(Tablero));
    if(tablero == NULL){
        fprintf(stderr, "Error al inicializar el tablero: falla en malloc.\n");
        exit(1);
    }

    tablero->filas = filas;
    tablero->columnas = columnas;

    tablero->tablero = (int**)calloc(tablero->filas, sizeof(int*));
    if(tablero->tablero == NULL){
        fprintf(stderr, "Error al inicializar el tablero: falla en malloc.\n");
        exit(1);
    }

    for(int i = 0; i < tablero->filas; ++i){
        tablero->tablero[i] = (int*)calloc(tablero->columnas, sizeof(int));
        if(tablero->tablero[i] == NULL){
            fprintf(stderr, "Error al inicializar el tablero: falla en malloc.\n");
            exit(1);
        }
    }

    return tablero;
}

// Retorna 1 si pudo realizar la jugada, de lo contrario,
// retorna 0 (Columna llena)
int realizarJugada(Tablero *tablero, int columna, int jugador){
    for(int i = tablero->filas-1; i >= 0; --i){
        if(tablero->tablero[i][columna] == 0){
            tablero->tablero[i][columna] = jugador;
            return 1;
        }
    }
    return 0;
}

void revertirJugada(Tablero *tablero, int columna){
    for(int i = 0; i < tablero->filas; ++i)
        if(tablero->tablero[i][columna] != 0){
            tablero->tablero[i][columna] = 0;
            break;
        }
}

void reiniciarTablero(Tablero *tablero){
    for(int i = 0; i < tablero->filas; ++i)
        for(int j = 0; j < tablero->columnas; ++j)
            tablero->tablero[i][j] = 0;
}

int estaLleno(Tablero *tablero){
    for(int i = 0; i < tablero->columnas; ++i)
        if(!tablero->tablero[0][i])
            return 0;
    return 1;
}

static int verificarHorizontal(Tablero *tablero, int fila, int columna, int cantidad, int vector[]){
    int contador = 1, valorFicha = tablero->tablero[fila][columna];
    int diferencia = tablero->columnas - columna - 1;
    int indice = 0;

    vector[indice++] = fila;
    vector[indice++] = columna;

    for(int i = 1; i < diferencia + 1; ++i){ // Verifica a la derecha
        if(tablero->tablero[fila][columna + i] != valorFicha || contador == cantidad)
            break;
        contador++;
        vector[indice++] = fila;
        vector[indice++] = columna + i;
    }
    diferencia = columna > cantidad ? cantidad - 1 : columna;
    for(int i = 1; i < diferencia + 1; ++i){ // Verifica a la izquierda
        if(tablero->tablero[fila][columna - i] != valorFicha || contador == cantidad)
            break;
        contador++;
        vector[indice++] = fila;
        vector[indice++] = columna - i;
    }
    return contador == cantidad;
}

static int verificarVertical(Tablero *tablero, int fila, int columna, int cantidad, int vector[]){
    int contador = 1, valorFicha = tablero->tablero[fila][columna];
    int diferencia = tablero->filas - fila - 1;
    int indice = 0;

    vector[indice++] = fila;
    vector[indice++] = columna;

    for(int i = 1; i < diferencia + 1; ++i){
        if(tablero->tablero[fila + i][columna] != valorFicha || contador == cantidad)
            break;
        contador++;
        vector[indice++] = fila + i;
        vector[indice++] = columna;
    }
    return contador == cantidad;
}

// Arriba a la izquierda hacia abajo a la derecha
static int verificarDiagonalPrincipal(Tablero *tablero, int fila, int columna, int cantidad, int vector[]){
    int diferenciaArriba, diferenciaAbajo, contador = 1;
    int valorFicha = tablero->tablero[fila][columna];
    int distanciaColumna = tablero->columnas - columna - 1;
    int distanciaFila = tablero->filas - fila - 1;
    int indice = 0;

    vector[indice++] = fila;
    vector[indice++] = columna;

    diferenciaArriba = columna > fila ? fila : columna;
    for(int i = 1; i < diferenciaArriba + 1; ++i){ // arriba a la izquierda
        if(tablero->tablero[fila - i][columna - i] != valorFicha || contador == cantidad)
            break;
        contador++;
        vector[indice++] = fila - i;
        vector[indice++] = columna - i;
    }

    diferenciaAbajo = distanciaColumna > distanciaFila ? distanciaFila : distanciaColumna;
    for(int i = 1; i < diferenciaAbajo + 1; ++i){ // abajo a la derecha
        if(tablero->tablero[fila + i][columna + i] != valorFicha || contador == cantidad)
            break;
        contador++;
        vector[indice++] = fila + i;
        vector[indice++] = columna + i;
    }

    return contador == cantidad;
}

// Abajo a la izquierda hacia arriba a la derecha
static int verificarDiagonalSecundaria(Tablero *tablero, int fila, int columna, int cantidad, int vector[]){
    int diferenciaArriba, diferenciaAbajo, contador = 1;
    int valorFicha = tablero->tablero[fila][columna];
    int distanciaColumna = tablero->columnas - columna - 1;
    int distanciaFila = tablero->filas - fila - 1;
    int indice = 0;

    vector[indice++] = fila;
    vector[indice++] = columna;

    diferenciaArriba = fila > distanciaColumna ? distanciaColumna : fila;
    for(int i = 1; i < diferenciaArriba + 1; ++i){ // arriba a la derecha
        if(tablero->tablero[fila - i][columna + i] != valorFicha || contador == cantidad)
            break;
        contador++;
        vector[indice++] = fila - i;
        vector[indice++] = columna + i;
    }

    diferenciaAbajo = columna > distanciaFila ? distanciaFila : columna;
    for(int i = 1; i < diferenciaAbajo + 1; ++i){ // abajo a la izquierda
        if(tablero->tablero[fila + i][columna - i] != valorFicha || contador == cantidad)
            break;
        contador++;
        vector[indice++] = fila + i;
        vector[indice++] = columna - i;
    }

    return contador == cantidad;
}

static int verificarDiagonales(Tablero *tablero, int fila, int columna, int cantidad, int vector[]){
    if(verificarDiagonalPrincipal(tablero, fila, columna, cantidad, vector))
        return 1;
    return verificarDiagonalSecundaria(tablero, fila, columna, cantidad, vector);
}

static void resetearVector(int vector[]){
    for(int i = 0; i < 8; ++i)
        vector[i] = -1;
}

// Evalua el tablero y:
// retorna 1 si gano el ultimo jugador en jugar,
// de lo contrario, retorna 0 
int verificarGanador(Tablero *tablero, int columna, int cantidad, int vector[]){
    if(columna < 0)
        return 0;
    for(int i = 0; i < tablero->filas; ++i){
        if(tablero->tablero[i][columna] != 0){
            resetearVector(vector);
            if(verificarHorizontal(tablero, i, columna, cantidad, vector))
                return 1;

            resetearVector(vector);
            if(verificarVertical(tablero, i, columna, cantidad, vector))
                return 1;

            resetearVector(vector);
            if(verificarDiagonales(tablero, i, columna, cantidad, vector))
                return 1;

            break;
        }
    }
    return 0;
}