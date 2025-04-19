#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
//constantes que se utilizan en el programa//
#define MAX_TAMA 70
#define NOMBRE_PENDIENTES "LISTA PENDIENTES"
#define NOMBRE_REALIZADS "LISTA REALIZADAS"
//variable para el id autoincremental de las tareas//
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


//funciones con las tareas//
Tarea crearTarea();
void mostrarTarea(Tarea tarea);
//operaciones de la lista//
Nodo * crearListaVacia();
Nodo * crearNodo(Tarea tarea);
void insertarNodo(Nodo ** lista, Nodo * nodo);
Nodo * quitarNodo(Nodo ** lista, int idBuscado);
bool mostrarLista(Nodo * lista, char * NombreLista);
void consultarTareas(Nodo * listaPendientes, Nodo * listaRealizadas);
void recorrerYmostrarSegunCriterio(Nodo * listaPendientes, Nodo * listaRealizadas, int criterio);
//liberar memoria//
void liberarMemoria(Nodo * lista);
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
        int opcion = 0;
        printf("1: MOSTRAR TAREAS PENDIENTES\n");
        printf("2: MOSTRAR TAREAS REALIZADAS\n");
        printf("3: MARCAR TAREA COMO REALIZADA\n");
        printf("4: CONSULTAR TAREAS\n");
        printf("OTRO PARA SALIR\n");
        fflush(stdin);
        scanf("%d",&opcion);
        switch (opcion){
            //variable para las funciones que requieren de pedir un id//
            int idBuscado;
            //variable para las funciones que requieren retornar un puntero a un nodo//
            Nodo * nodoRetornado;
            case 1: 
                mostrarLista(listaPendientes,NOMBRE_PENDIENTES);
            break;

            case 2:
                mostrarLista(listaRealizadas,NOMBRE_REALIZADS);
            break;

            case 3:
                //muestro la lista para que se puedan ver los id//
                bool permitirIngresoId = mostrarLista(listaPendientes,"LISTA PENDIENTES");
                if(permitirIngresoId){
                    printf("ingrese el id de la tarea:");
                    fflush(stdin);
                    scanf("%d",&idBuscado);
                    nodoRetornado = quitarNodo(&listaPendientes,idBuscado);
                    //si se encuentra el nodo lo agregamos a la lista de realizadas//
                    if(nodoRetornado) insertarNodo(&listaRealizadas,nodoRetornado);
                    else printf("No se encontro la Tarea\n\n");
                }else{
                    printf("no hay ninguna tarea pendiente\n\n");
                }
            break;
            
            case 4:
                consultarTareas(listaPendientes,listaRealizadas);
            break;

            default: seguir = false;
        }
    }while(seguir);

    //liberamos memoria//
    liberarMemoria(listaPendientes);
    liberarMemoria(listaRealizadas);
    return 0;
}

//funciones con las tarea//
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
    //id de la tarea//
    tarea.TareaID = id;
    id++;
    //retornamos la tarea//
    return tarea;
}

//mostrar tarea//
void mostrarTarea(Tarea tarea)
{   
    printf("----------TAREA----------\n");
    printf("ID TAREA: %d\n",tarea.TareaID);
    printf("DURACION: %d\n",tarea.Duracion);
    printf("DESCRIPCION: %s\n",tarea.Descripcion);
    printf("\n");
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

void insertarNodo(Nodo ** lista, Nodo * nodo)
{
    nodo->Siguiente = *lista;
    *lista = nodo;
}

Nodo * quitarNodo(Nodo ** lista, int idBuscado){
    Nodo ** aux = lista;

    while (*aux && (*aux)->T.TareaID != idBuscado){
        aux = &(*aux)->Siguiente;
    }

    if (*aux){
        Nodo * temp = *aux;
        *aux = (*aux)->Siguiente;
        temp->Siguiente = NULL;
        return temp;
    }

    return NULL;
}

void consultarTareas(Nodo * listaPendientes, Nodo * listaRealizadas)
{
    int opcion;
    printf("----------CONSULTAR TAREAS----------\n");
    do{
        printf("1: Consultar tarea por id\n");
        printf("2: Consultar tarea por Palabra Clave\n");
        printf("ELIGA UNA OPCION:");
        fflush(stdin);
        scanf("%d",&opcion);
    }while(!(opcion == 1 || opcion == 2));
    //variable para recibir los nodos que retornen las funciones//
    Nodo * nodoRetornado;
    recorrerYmostrarSegunCriterio(listaPendientes,listaRealizadas,opcion);
}

bool mostrarLista(Nodo * lista, char * NombreLista)
{
    //uso booleanos para cuando se quiera marcar una tarea como realizada y la lista este vacia retornar false y saber que no hay tareas pendientes//
    printf("----------%s----------\n",NombreLista);
    if(lista){
        while(lista){
            mostrarTarea(lista->T);
            lista = lista->Siguiente;
        }
    }else{
        printf("LA LISTA ESTA VACIA\n\n");
        return false;
    }
    return true;
}

void recorrerYmostrarSegunCriterio(Nodo * listaPendientes, Nodo * listaRealizadas, int critero)
{
    //variable que se utilizara para indicar si no se encontro ninguna tarea//
    bool seEncontro = false;
    //funcionalidad por si se elige buscar la tarea por id//
    if(critero == 1){
        //pedimos al usuario que ingrese el id//
        int idBuscado;
        printf("ingrese el id:");
        fflush(stdin);
        scanf("%d",&idBuscado);
        //recorremos la lista buscando el id, si se encuentra se indica que estamos en la lista de pendientes//
        while(listaPendientes){
            if(listaPendientes->T.TareaID == idBuscado){
                printf("\nTAREA ENCONTRADA EN PENDIENTES\n");
                mostrarTarea(listaPendientes->T);
                seEncontro = true;
            }
            listaPendientes = listaPendientes->Siguiente;
        }
        //recorrermos la lista buscando el id, si se encuentra se indica que estamos en la lista de realizadas//
        while(listaRealizadas){
            if(listaRealizadas->T.TareaID == idBuscado){
                printf("\nTAREA ENCONTRADA EN REALIZADAS\n");
                mostrarTarea(listaRealizadas->T);
                seEncontro = true;
            }
            listaRealizadas = listaRealizadas->Siguiente;
        }

    }else{
        //funcionalidad por si se elige buscar la tarea por palabra clave//
        //pedimos al usuario que ingrese o las palabras//
        char palabrasClaves[MAX_TAMA];
        printf("ingrese la/las palabras claves:");
        fflush(stdin);
        gets(palabrasClaves);
        //recorrermos la lista buscando la palabra clave, si se encuentra se indica que estamos en la lista de pendientes//
        while(listaPendientes){
            if(strstr(listaPendientes->T.Descripcion,palabrasClaves)){
                printf("\nTAREA ENCONTRADA EN PENDIENTES\n");
                mostrarTarea(listaPendientes->T);
                seEncontro = true;
            }
            listaPendientes = listaPendientes->Siguiente;
        }
        //recorrermos la lista buscando la palabra clave, si se encuentra se indica que estamos en la lista de realizadas//
        while(listaRealizadas){
            if(strstr(listaRealizadas->T.Descripcion,palabrasClaves)){
                printf("\nTAREA ENCONTRADA EN REALIZADAS\n");
                mostrarTarea(listaRealizadas->T);
                seEncontro = true;
            }
            listaRealizadas = listaRealizadas->Siguiente;
        }
    }
    if(!seEncontro){
        printf("\nno se encontro la tarea en ninguna lista\n");
    }
}

//liberar memoria//
void liberarMemoria(Nodo * lista)
{
    while(lista){
        Nodo * aux = lista;
        lista = lista->Siguiente;
        free(aux->T.Descripcion);
        free(aux);
    }
}