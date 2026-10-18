#include <stdio.h>
#include <ctype.h>
#include "creatorverse.h"
#include <string.h>

int main(int argc, char *argv[]) {
    TABB base_datos; 
    char opcion;

    // Se le pasan directamente argc (nparam) y argv (args)
    inicializarCreadores(&base_datos, argc, argv);
    printf("Bienvenid@ a CreatorVerse\n\n");

    // 2. Bucle principal del menu
    do {
        printf("A. Anhadir creador\n");
        printf("L. Listar creadores\n");
        printf("E. Eliminar creador\n");
        printf("N. Anhadir nuevos retos\n");
        printf("B. Buscar Creador\n");
        printf("C. Completar siguiente reto\n");
        printf("D. Buscar reto más dificil\n");
        printf("T. Buscar creador o creadores con mayor numero de retos\n");
        printf("M. Modificar Creador\n");
        printf("S. Salir\n");
        printf("Seleccione una opcion: ");
        
        scanf(" %c", &opcion);
        opcion = toupper(opcion); // Convierte a mayuscula para simplificar el switch

        switch (opcion) {
            case 'A':
                anhadirCreador(&base_datos);
                break;
            case 'L':
                listarCreadores(base_datos);
                break;
            case 'E':
                eliminarCreador(&base_datos);
                break;
            case 'N':
                nuevosRetos(&base_datos);
                break;
            case 'C':
                completarReto(&base_datos);
                break;
            case 'B':
                buscarCreador(base_datos);
                break;
            case 'D':
                buscarRetoMasDificil(base_datos);
                break;
            case 'T':
                buscarCreadoresMasRetos(base_datos);
                break;
            case 'M':
                modificarCreador(&base_datos);
                break;
            case 'S':
                printf("\nGracias por usar nuestro programa.\n");
                break;
            default:
                printf("\nOpcion no valida. Intentelo de nuevo.\n\n");
                break;
        }
    } while (opcion != 'S');

        // Si se cargo un fichero con -f, guardamos en ese; si no, preguntamos el nombre
    char nombre[100];
    if (argc >= 3 && strcmp(argv[1], "-f") == 0) {
        strcpy(nombre, argv[2]);
    } else {
        printf("Nombre del fichero donde guardar: ");
        scanf("%99s", nombre);
    }
    guardarEnFichero(base_datos, nombre);

    // 3. Liberacion de memoria de todo el arbol al salir
    destruirAbb(&base_datos);

    return 0;
}