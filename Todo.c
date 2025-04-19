#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define MAX_TAMA 70
int id = 1000;

struct Tarea{
    int TareaID;//Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion; // entre 10 – 100
}typedef Tarea;

struct Nodo{
    struct Tarea T;
    struct Nodo *Siguiente;
}typedef Nodo;


//crear tarea//
Tarea crearTarea();
//operaciones de la lista//
Nodo * crearListaVacia();
Nodo * crearNodo(Tarea tarea);
void insertarNodo(Nodo ** start, Nodo * nodo);
int main(){
    //creamos las listas//
    Nodo * listaPendientes = crearListaVacia();
    Nodo * listaRealizadas = crearListaVacia();
    //interfaz de usuario//
    bool seguir = true;
    //carga de tareas//
    do{
        int opcion = 0;
        Tarea tarea = crearTarea();
        Nodo * nodo = crearNodo(tarea);
        insertarNodo(&listaPendientes, nodo);
        printf("1: PARA SEGUIR\n");
        printf("OTRO PARA FINALIZAR LA CARGA\n");
        fflush(stdin);
        scanf("%d",&opcion);
        if(opcion != 1){
            seguir = false;
        }
    }while(seguir);
    seguir = true;
    //menu de opciones//
    do
    {  
       printf("1: MOSTRAR TAREAS PENDIENTES\n");
       printf("2: MOSTRAR TAREAS REALIZADAS\n");
       printf("3: MARCAR TAREA COMO REALIZADA\n");
       printf("4: BUSCAR TAREA POR ID\n");
       printf("5: BUSCAR TAREA POR PALABRA CLAVE\n");
       printf("OTRO PARA SALIR\n"); 
    }while(seguir);
}


//crear tarea//
Tarea crearTarea()
{
    Tarea tarea;
    //descripcion de la tarea//
    char descripcion[MAX_TAMA];
    printf("ingrese la descripcion de la tarea:");
    fflush(stdin);
    gets(descripcion);
    tarea.Descripcion = (char *)malloc(sizeof(char) * strlen(descripcion) + 1);
    strcpy(tarea.Descripcion,descripcion);
    //duracion de la tarea//
    bool continuar = true;
    do{
        int duracion;
        printf("ingrese la duracion de la tarea:");
        fflush(stdin);
        scanf("%d",&duracion);
        if(duracion >= 10 && duracion <= 100){
            tarea.Duracion = duracion;
            continuar = false;
        }else{
            printf("LA TAREA DEBE DURAR ENTRE 10-100 MINUTOS\n");
        }
    }while(continuar);
    //retornamos la tarea//
    return tarea;
}

//operaciones de la lista//
Nodo * crearListaVacia()
{
    return NULL;
}
    
Nodo * crearNodo(Tarea tarea)
{
    Nodo * Tnodo = (Nodo *)malloc(sizeof(Nodo));
    Tnodo->T = tarea;
    Tnodo->Siguiente = NULL;
    return Tnodo;
}

void insertarNodo(Nodo ** start, Nodo * nodo)
{
    nodo->Siguiente = *start;
    *start = nodo;
}