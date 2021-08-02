#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minimax.h"

void menuJugar();
void jvsj();
void jvsc();
void cvsc();

void configuracion();
void acercaDe();

char buffer[100];

void limpiarBuffer(){
    for(int i = 0; i < 256; ++i)
        buffer[i] = 0;
}

int verificarBuffer(int *opcion){
    if(strlen(buffer) > 1){
        printf("Ingreso caracteres invalidos, intente nuevamente.\n");
        return 1;
    }
    *opcion = buffer[0] - 48;
    return 0;
}

void menu(){
    int opcion;
    while(1){
        system("clear");
        limpiarBuffer();
        printf("\t4 EN LINEA\n\n");
        printf("1. Jugar.\n");
        printf("2. Configuracion.\n");
        printf("3. Acerca de.\n");
        printf("4. Salir.\n");
        printf("\n>>> ");
        scanf("%s", buffer);
        printf("\n");

        if(verificarBuffer(&opcion))
            continue;

        switch(opcion){
            case 1:
                menuJugar(buffer);
                break;
            case 2:
                configuracion(buffer);
                break;
            case 3:
                acercaDe(buffer);
                break;
            case 4:
                return;
            default:
                printf("Opcion invalida...\n");

        }
    }
}

void menuJugar(char buffer[]){
    int opcion;
    while(1){
        system("clear");
        limpiarBuffer();
        printf("\tJUGAR\n\n");
        printf("1. Jugador vs Jugador.\n");
        printf("2. Jugador vs Computadora.\n");
        printf("3. Computadora vs computadora.\n");
        printf("4. Volver al menu principal.\n");
        printf("\n>>>");
        scanf("%s", buffer);
        printf("\n");

        if(verificarBuffer(&opcion));
            continue;

        switch(opcion){
            case 1:
                jvsj();
                return;
            case 2:
                jvsc();
                return;
            case 3:
                cvsc();
                return;
            case 4:
                return;
            default:
                printf("Opcion invalida, intente nuevamente.\n");
        }
    }
}

void pedirColor(int jugador){
    jugador--;
    int opcion;
    while(1){
        printf("\nElija un color:\n");
        printf("1. Rojo\n");
        printf("2. Azul\n");
        printf("3. Verde\n");
        printf("4. Amarillo\n>>> ");
        scanf("%s", buffer);
        printf("\n");
        
        if(verificarBuffer(&opcion))
            continue;

        switch(opcion){
            case 1:
                if(jugadores[jugador^1].color == ROJO){
                    printf("El color ya esta en uso, ingrese otro color.\n")
                }else{
                    jugadores[jugador].color = ROJO;
                    jugadores[jugador].bg_color = BG_ROJO; 
                    return;
                }
                break;
            case 2:
                if(jugadores[jugador^1].color == AZUL){
                    printf("El color ya esta en uso, ingrese otro color.\n")
                }else{
                    jugadores[jugador].color = AZUL;
                    jugadores[jugador].bg_color = BG_AZUL; 
                    return;
                }
                break;
            case 3:
                if(jugadores[jugador^1].color == VERDE){
                    printf("El color ya esta en uso, ingrese otro color.\n")
                }else{
                    jugadores[jugador].color = VERDE;
                    jugadores[jugador].bg_color = BG_VERDE; 
                    return;
                }
                break;
            case 4:
                if(jugadores[jugador^1].color == AMARILLO){
                    printf("El color ya esta en uso, ingrese otro color.\n")
                }else{
                    jugadores[jugador].color = AMARILLO;
                    jugadores[jugador].bg_color = BG_AMARILLO; 
                    return;
                }
                break;
            default:
                printf("Opcion invalida, intente nuevamente.\n");
        }
    }
}

void pedirDatosJugador(int jugador){
    limpiarBuffer();
    while(1){
        printf("\nIngrese el nombre del jugador %i. (max 15 caracteres)\n", jugador);
        scanf("%s", buffer);
        if(strlen(buffer) > 15){
            printf("Cantidad de caracteres mayor a la indicada, intente nuevamente.\n");
        }else{
            strcpy(jugadores[jugador-1].nombre, buffer);
            break;
        }
    }
    pedirColor(jugador);
}

int pedirColumna(int jugador){
    int columna;
    while(1){
        printf("%i - %s: Ingrese la columna a jugar\n>>> ", jugador, jugadores[jugador - 1].nombre);
        scanf("%s", buffer);
        
        if(verificarBuffer(&columna))
            continue;
        break;
    }
    return columna;
}

void jvsj(){
    inicializarTablero();

    pedirDatosJugador(1);
    pedirDatosJugador(2);

    srand(time(0));
    int jugador = (rand() % 2) + 1;
    int columna;
    printf("Comienza el jugador: %i - %s\n", jugador, jugadores[jugador - 1].nombre)
    while(!tableroEstaLleno()){
        columna = pedirColumna(jugador);
        realizarJugada(columna, jugador);

        if(verificarGanador(columna)){

        }
    }
}

void configuracion(char buffer[]){

}

void acercaDe(char buffer[]){

}