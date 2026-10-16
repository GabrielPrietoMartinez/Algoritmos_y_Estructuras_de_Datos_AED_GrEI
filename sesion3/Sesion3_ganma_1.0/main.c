#include <stdio.h>
#include <ctype.h>
#include "creatorverse.h"

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
            case 'S':
                printf("\nGracias por usar nuestro programa.\n");
                break;
            default:
                printf("\nOpcion no valida. Intentelo de nuevo.\n\n");
                break;
        }
    } while (opcion != 'S');

    // 3. Liberacion de memoria de todo el arbol al salir
   // destruir_creadores(&base_datos);

    return 0;
}