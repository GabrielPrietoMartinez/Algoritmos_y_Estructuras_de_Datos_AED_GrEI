#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "creatorverse.h"

#include "abb.h"

#define MAX_RETO 100

//FUNCIONES PRIVADAS: su prototipo no esta en creatorverse.h
//Listado de los prototipos de las funciones privadas

//Elimina el cambio de linea final si uso gets() o fgets()
void _strip_line(char *linea); 

//Separa cada reto de un creador y lo inserta en la cola de creadores
void _splitByComma(char*field, TCOLA *cola);


//FUNCIONES PUBLICAS: su prototipo está en creatorverse.h

////////////////////////////////////////////////////////////////////////////////////////
// PARA COMPLETAR POR EL/LA ESTUDIANTE:
// COMPLETA TODOS LOS COMENTARIOS INDICADOS EN MAYUSCULAS EN ESTA FUNCION 
// Y EN LA FUNCION PRIVADA _splitByComma()
////////////////////////////////////////////////////////////////////////////////////////
void inicializarCreadores(TABB *A, int nparam, char **args) {
    TIPOELEMENTOABB creador;
    char linea[1000]; //cada linea del archivo tiene toda la informacion de un creador
    char *token; //variable que va leyendo cada campo del creador

    //ANHADE EL CODIGO PARA CREAR EL ARBOL

    crearAbb(A);


    if (nparam < 3 || strcmp(args[1], "-f") != 0) {
        fprintf(stderr, "Para cargar un archivo usa: %s -f <filename>\n", args[0]);
        return;
    }
    FILE *fp = fopen(args[2], "rt");
    if (fp == NULL) {
        perror("Error abriendo el archivo\n");
        return;
    }
    while (fgets(linea, sizeof (linea), fp)) {
        _strip_line(linea); //elimino el cambio de linea final
        token = strtok(linea, "|"); //primer token
        int n = 0; //tengo 7 campos, contador de campos
        while (n < 7) {
            n++;
            switch (n) {
                case 1: //alias
                
                    strncpy(creador.alias, token, MAX_ALIAS);
                    break;
                case 2: //categoria
                    creador.categoria = atoi(token);
                    break;
                case 3: //colectivo
                    
                    strncpy(creador.colectivo, token,   MAX_COLECTIVO);
                    break;
                case 4: //seguidores
                    creador.seguidores = atoi(token);
                    break;
                case 5: //verificado
                    creador.verificado = atoi(token);
                    break;
                case 6: //cola de retos separados por comas
                    // ANHADE EL CODIGO PARA CREAR LA COLA DE RETOS DEL CREADOR ACTUAL
                    // ANHADE EL CODIGO SIGUIENTE: SI token ES DISTINTO DE "-", LLAMAS A LA FUNCIÓN
                    // _splitByComma MODIFICANDO LA SIGUIENTE LINEA SUSTITUYENDO EL DATO ENTRE <> POR LA VARIABLE QUE SE INDICA
                         //_splitByComma(token, <cola de retos del creador>)
                    crearCola(&creador.cola_retos);
                    if (strcmp(token, "-") != 0) {
                    _splitByComma(token, &creador.cola_retos);
                    }
                    break;
                         
                case 7: //descripcion
                    
                    strncpy(creador.descripcion, token, MAX_DESCRIPCION);
                    break;
            }
            token = strtok(NULL, "|");

        }
        //ANHADE EL CODIGO PARA INSERTAR EL CREADOR EN EL ARBOL SOLO SI NO ES MIEMBRO DEL ARBOL

                if (!esMiembroAbb(*A, creador)) { 
            insertarElementoAbb(A, creador);
        }
    }
    fclose(fp);
}

void anhadirCreador(TABB *A){
    TIPOELEMENTOABB creador;
    TIPOELEMENTOCOLA reto;

    printf("Alias: ");
    scanf(" %[^\n]", creador.alias);

    // Si el alias ya está en el árbol, no lo añadimos otra vez
    if (esMiembroAbb(*A, creador)) {
        printf("Ya existe un creador con el alias %s\n", creador.alias);
        return;
    }

    printf("Categoria: ");
    scanf("%u", &creador.categoria);

    printf("Colectivo: ");
    scanf(" %[^\n]", creador.colectivo);

    printf("Seguidores: ");
    scanf("%ld", &creador.seguidores);

    // Repetimos hasta que meta un 0 o un 1
    do {
        printf("Verificado? (1 = si, 0 = no): ");
        scanf("%d", &creador.verificado);
    } while (creador.verificado != 0 && creador.verificado != 1);

    printf("Descripcion: ");
    scanf(" %[^\n]", creador.descripcion);

    // Cola de retos: se van añadiendo hasta escribir "fin"
    crearCola(&creador.cola_retos);

    printf("Escriba el nombre del reto, si quiere dejar de escribir retos ponga fin: \n ");
    scanf(" %30[^\n]", reto.titulo);
    

    while (strcmp(reto.titulo, "fin") != 0) {
        do {
        printf("Escriba la dificultad del reto que acaba de escribir (del 1 al 5): \n ");
        scanf("%d", &reto.dificultad);
    } while (reto.dificultad != 1 && reto.dificultad != 2 && reto.dificultad != 3 && reto.dificultad != 4 && reto.dificultad != 5);

        insertarCola(&creador.cola_retos, reto);

        printf("Nombre del reto (\"fin\" para terminar): ");
        scanf(" %30[^\n]", reto.titulo);
    }

    insertarElementoAbb(A, creador);
    printf("Creador %s anadido.\n", creador.alias);
    
}



void _imprimirReto(TIPOELEMENTOCOLA reto) {
    printf("%s (dificultad: %d)\n", reto.titulo, reto.dificultad);
}

void _imprimirCola(TCOLA cola){
    TIPOELEMENTOCOLA reto;
    TCOLA aux;

    if (esVaciaCola(cola)) {
        printf("la cola esta sin retos)\n");
        return;
    }

    crearCola(&aux);

    while (!esVaciaCola(cola)) {
        reto = primeroCola(cola);
        _imprimirReto(reto);
        insertarCola(&aux, reto);
        suprimirCola(&cola);
    }

    // Devuelvo los elementos a la cola original
    while (!esVaciaCola(aux)) {
        reto = primeroCola(aux);
        insertarCola(&cola, reto);
        suprimirCola(&aux);
    }

    destruirCola(&aux);
}





void _imprimirCreador(TIPOELEMENTOABB creador){
    printf("Alias: %s\n", creador.alias);
    printf("  Categoria: %d\n", creador.categoria);
    printf("  Colectivo: %s\n", creador.colectivo);
    printf("  Seguidores: %ld\n", creador.seguidores);
    printf("  Verificado: %s\n", creador.verificado ? "Si" : "No");
    printf("  Descripcion: %s\n", creador.descripcion);
    printf("  Retos:\n");
    _imprimirCola(creador.cola_retos);
}

void listarCreadores(TABB A){
     TIPOELEMENTOABB creador;

    if (!esAbbVacio(A)) {
        listarCreadores(izqAbb(A));
        leerElementoAbb(A, &creador);
        _imprimirCreador(creador);
        listarCreadores(derAbb(A));
    }
}

void eliminarCreador(TABB *A) {
    TIPOELEMENTOABB creador;

    printf("Alias del creador a eliminar: ");
    scanf(" %[^\n]", creador.alias);

    if (esMiembroAbb(*A, creador)) {
        // Cogemos el creador completo para tener su cola de retos
        buscarNodoAbb(*A, creador.alias, &creador);

        

        suprimirElementoAbb(A, creador);

        //destruirCola(&creador.cola_retos);

        // Liberamos la cola, que el árbol no la borra
        

        printf("Creador %s eliminado.\n", creador.alias);
    } else {
        printf("No existe ningun creador con el alias %s.\n", creador.alias);
    }
}


///////////////////////////////////////////////////////
//FUNCIONES PRIVADAS
//////////////////////////////////////////////
//lee una cadena de retos y los almacena en la cola
//el formato de cadena es "titulo1:dificultad1,titulo2:dificultad2,titulo3:dificultad3,...
//el titulo es texto y la dificultad es un entero
void _splitByComma(char *cadena, TCOLA *cola) {
    TIPOELEMENTOCOLA reto; //va a tener los campos titulo y dificultad

     //REVISA SI MAX_RETO EXISTE EN cola.h O LE HAS DADO OTRO NOMBRE A LA LONGITUD MAXIMA DEL TITULO DEL RETO
    char cadenareto[MAX_RETO]; //es cada reto con los campos titulo y dificultad, leo su longitud de la longitud maxima del titulo en cola.h

    char *start = cadena;
    char *end = cadena;
    while (*end != '\0') {
        if (*end == ',') {
            *end = '\0';
            //cadenareto va a contener titulo:dificultad del reto leido
            
            //REVISA SI MAX_RETO EXISTE EN cola.h O LE HAS DADO OTRO NOMBRE
            strncpy(cadenareto, start, MAX_RETO); //MAX_RETO se lee de cola.h

            // podemos separar los campos de cada reto de forma facil con sscanf
            sscanf(cadenareto, " %[^:]:%d", reto.titulo, &reto.dificultad);

            // MODIFICA LA SIGUIENTE LINEA SUSTITUYENDO LOS DATOS ENTRE <> POR LAS VARIABLES QUE SE INDICAN
            // sscanf(cadenareto, " %[^:]:%d", <campo titulo de la variable reto>, <campos dificultad de la variable reto>);
            
            //ANHADE EL CODIGO PARA INSERTAR EL RETO EN LA COLA

            insertarCola(cola, reto);


            start = end + 1;
        }
        end++;
    }
    //Copia el ultimo token
    
    // REVISA SI MAX_RETO EXISTE EN cola.h O LE HAS DADO OTRO NOMBRE
    //MAX_RETO se lee de cola.h

    // MODIFICA LA SIGUIENTE LINEA SUSTITUYENDO LOS DATOS ENTRE <> POR LAS VARIABLES QUE SE INDICAN
    //sscanf(cadenareto, " %[^:]:%d", <campo titulo de la variable reto>, <campos dificultad de la variable reto>);

    
    //ANHADE EL CODIGO PARA INSERTAR EL RETO EN LA COLA
    strncpy(cadenareto, start, MAX_RETO);
    sscanf(cadenareto, " %[^:]:%d", reto.titulo, &reto.dificultad);
    insertarCola(cola, reto);
    
    
}

//Funcion para eliminar el cambio de linea si uso gets() o fgets()
void _strip_line(char *linea) {
    linea[strcspn(linea, "\r\n")] = 0;
}


void escribirRetos(FILE *fp, TCOLA cola){
    TIPOELEMENTOCOLA reto;
    TCOLA aux;
    if (esVaciaCola(cola)) {
        fprintf(fp, "-");
        return;
    }
    crearCola(&aux);
    int pestillo = 1;
    while (!esVaciaCola(cola)){
        reto = primeroCola(cola);
        if(pestillo == 0){
            fprintf(fp, ",");
        }
        pestillo = 0;
        fprintf(fp, "%s:%d", reto.titulo, reto.dificultad);
        insertarCola(&aux, reto);
        suprimirCola(&cola );
    }
     while (!esVaciaCola(aux)) {
        insertarCola(&cola, primeroCola(aux));
        suprimirCola(&aux);
    }
    destruirCola(&aux);


}


void guardarPreorden(TABB A, FILE *fp) {
    TIPOELEMENTOABB c;

    if (esAbbVacio(A)) {
        return;
    }
    leerElementoAbb(A, &c);
    fprintf(fp, "%s|%u|%s|%ld|%d|", c.alias, c.categoria, c.colectivo, c.seguidores, c.verificado);
    escribirRetos(fp, c.cola_retos);
    fprintf(fp, "|%s|\n", c.descripcion);

    guardarPreorden(izqAbb(A), fp);
    guardarPreorden(derAbb(A), fp);
}

void guardarEnFichero(TABB A, char* archivo){
    FILE *fp = fopen(archivo, "wt");
    if (fp == NULL) {
        perror("Error abriendo el archivo para escribir");
        return;
    }
    guardarPreorden(A, fp);
    fclose(fp);
    
}

void nuevosRetos(TABB *A) {
    TIPOELEMENTOABB creador;
    TIPOELEMENTOCOLA reto;


    printf("Alias del creador: ");
    scanf(" %19[^\n]", creador.alias);

    if (!esMiembroAbb(*A, creador)) {
        printf("No existe ningun creador con el alias %s.\n", creador.alias);
        return;
    }

    buscarNodoAbb(*A, creador.alias, &creador);



    printf("Escriba el nombre del reto, si quiere dejar de escribir retos ponga fin: \n ");
    scanf(" %30[^\n]", reto.titulo);
    

    while (strcmp(reto.titulo, "fin") != 0) {
        do {
        printf("Escriba la dificultad del reto que acaba de escribir (del 1 al 5): \n ");
        scanf("%d", &reto.dificultad);
    } while (reto.dificultad != 1 && reto.dificultad != 2 && reto.dificultad != 3 && reto.dificultad != 4 && reto.dificultad != 5);

        insertarCola(&creador.cola_retos, reto);

        printf("Nombre del reto (\"fin\" para terminar): ");
        scanf(" %30[^\n]", reto.titulo);
    }

    modificarElementoAbb(*A, creador);

}


void completarReto(TABB *A) {
    TIPOELEMENTOABB creador;
    TIPOELEMENTOCOLA reto;

    printf("Alias del creador: ");
    scanf(" %19[^\n]", creador.alias);

    if (!esMiembroAbb(*A, creador)) {
        printf("No existe ningun creador con el alias %s.\n", creador.alias);
        return;
    }

    buscarNodoAbb(*A, creador.alias, &creador);

    if (esVaciaCola(creador.cola_retos)) {
        printf("%s no tiene retos pendientes.\n", creador.alias);
        return;
    }

    // El reto que toca es el primero de la cola
    reto = primeroCola(creador.cola_retos);
    printf("Reto completado: %s (dificultad: %d)\n", reto.titulo, reto.dificultad);
    suprimirCola(&creador.cola_retos);

    // Mostramos el siguiente, si queda alguno
    if (esVaciaCola(creador.cola_retos)) {
        printf("%s ha completado todos sus retos.\n", creador.alias);
    } else {
        reto = primeroCola(creador.cola_retos);
        printf("Siguiente reto: %s (dificultad: %d)\n", reto.titulo, reto.dificultad);
    }

    modificarElementoAbb(*A, creador);
}


void buscarCreador(TABB A) {
    TIPOELEMENTOABB creador;

    printf("Alias del creador a buscar: ");
    scanf(" %19[^\n]", creador.alias);

    if (!esMiembroAbb(A, creador)) {
        printf("No existe ningun creador con el alias %s.\n", creador.alias);
        return;
    }

    buscarNodoAbb(A, creador.alias, &creador);
    _imprimirCreador(creador);
}




void _acumularMaximos(TABB A, TCOLA cola, int *dificultad){
    TIPOELEMENTOABB elem_abb_aux;
    TIPOELEMENTOCOLA reto, reto_guardado;
    TCOLA aux;

    if(esAbbVacio(A)){
        return;
    }

    leerElementoAbb(A, &elem_abb_aux);
    crearCola(&aux); // solo para recorrer los retos de este creador

    while (!esVaciaCola(elem_abb_aux.cola_retos)) {
        reto = primeroCola(elem_abb_aux.cola_retos);

        // Nuevo maximo: tiramos los retos que teniamos guardados
        if (reto.dificultad > *dificultad) {
            *dificultad = reto.dificultad;
            while (!esVaciaCola(cola)) {
                suprimirCola(&cola);
            }
        }

        // Si llega al maximo, lo guardamos con el alias delante
        if (reto.dificultad == *dificultad) {
            reto_guardado.dificultad = reto.dificultad;
            snprintf(reto_guardado.titulo, sizeof(reto_guardado.titulo), "%s: %s", elem_abb_aux.alias, reto.titulo);
            insertarCola(&cola, reto_guardado);
        }

        insertarCola(&aux, reto);
        suprimirCola(&elem_abb_aux.cola_retos);
    }

    // Devolvemos los retos a su cola en el mismo orden
    while (!esVaciaCola(aux)) {
        insertarCola(&elem_abb_aux.cola_retos, primeroCola(aux));
        suprimirCola(&aux);
    }
    destruirCola(&aux);

    _acumularMaximos(izqAbb(A), cola, dificultad);
    _acumularMaximos(derAbb(A), cola, dificultad);
}



void buscarRetoMasDificil(TABB A){
    TCOLA cola;
    crearCola(&cola);
    int dificultad_max = 0;

    if(esAbbVacio(A)){
        printf("El arbol esta vacio, por tanto no hay retos.\n");
        destruirCola(&cola);
        return;
    }

    _acumularMaximos(A, cola, &dificultad_max);

    if (esVaciaCola(cola)) {
        printf("Ningun creador tiene retos.\n");
    } else {
        printf("Retos de dificultad maxima (%d):\n", dificultad_max);
        while (!esVaciaCola(cola)) {
            printf("  %s\n", primeroCola(cola).titulo);
            suprimirCola(&cola);
        }
    }

    destruirCola(&cola);
}