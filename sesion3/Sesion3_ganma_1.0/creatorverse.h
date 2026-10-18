#ifndef CREATORVERSE_H
#define CREATORVERSE_H

#include "abb.h"

/**
 * Crea el arbol, lee el archivo y lo almacena en el arbol
 * @param A Arbol.
 * @param nparam numero de argumentos de main en linea de comandos
 * @param args seran los argumentos de main: "-f" y nombrearchivo
 */
void inicializarCreadores(TABB *A, int nparam, char **args);

/**
 * Anhade un creador a la base de datos
 * @param A Arbol.
 */
void anhadirCreador(TABB *A);

/**
 * Listado de creadores por orden alfabetico
 * @param A Arbol.
 */
void listarCreadores(TABB A);

/**
 * Elimina un creador de la base de datos
 * @param A Arbol.
 */
void eliminarCreador(TABB *A);


//funcion para guardar el arbol en el fichero txt

void guardarEnFichero(TABB A, char* archivo);

void nuevosRetos(TABB *A);

void completarReto(TABB *A);

void buscarCreador(TABB A);

void buscarRetoMasDificil(TABB A);

void buscarCreadoresMasRetos(TABB A);

void modificarCreador(TABB *A);

#endif /* CREATORVERSE_H */

