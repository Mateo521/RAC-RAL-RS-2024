#ifndef TDA_LISTA_RESERVA_H_INCLUDED
#define TDA_LISTA_RESERVA_H_INCLUDED
#include "shipment.h"
#include <string.h>

typedef struct {
    struct Nodo *cab;// Puntero al primer nodo de la lista.
} ListaShip;

typedef struct Nodo {
    struct Nodo *sig; // Puntero al siguiente nodo de la lista.
    Shipment ship;
} Nodo;


int InsertList(ListaShip *rs, Shipment a){

Nodo *nodo = malloc(sizeof(Nodo));
if (nodo == NULL) {
    return FAILURE;
}
nodo->sig = NULL;
nodo->ship = a;
//si la lista esta vacia inserta el elemento en el primer lugar
if(rs->cab==NULL){
    rs->cab=nodo;
    return SUCCESS;
}
//Sigue la ejecucion pq la lista no esta vacia y hay que comparar que no haya repetidos

Nodo *aux = rs->cab;

while(aux!=NULL) {
        if(compareShipments(aux->ship,a)==SUCCESS){
           return FAILURE; //encontro el repetido y termina el insert
           }
    aux = aux->sig;
}
//salio del ciclo while, no hay repetidos y procede a insertar el elemento en la cabeza de la lista
nodo->sig = rs->cab;
rs->cab = nodo;
return SUCCESS;

}

int evocarList(ListaShip rs, Shipment a, Shipment aux, float* costo){

  if (rs.cab == NULL) {
    return FAILURE;
  }
Nodo *nodo;

  for (nodo = rs.cab; nodo != NULL; nodo = nodo->sig) {
    if (strcmp(nodo->ship.code, a.code) == 0) {
      aux = (nodo->ship);
      return SUCCESS;
    }
    (*costo)=(*costo)+1;
  }

  return FAILURE;

}

int bajaList(ListaShip *rs, Shipment a){
    Nodo *nodo = rs->cab;
    Nodo *anterior = NULL;

    // Si la lista está vacía, no hace nada.
    if (nodo == NULL) {
        return FAILURE;
    }

    // Si el nodo a eliminar es el primero de la lista.
    if (compareShipments(nodo->ship,a)==SUCCESS) {
        rs->cab = nodo->sig;
        free(nodo);
        return SUCCESS;
    }

    // Recorre la lista hasta encontrar el nodo a eliminar.
    while (nodo->sig != NULL && compareShipments(nodo->sig->ship,a) == FAILURE) {
        anterior = nodo;
        nodo = nodo->sig;
    }

    // Si el nodo no se encontró, no hace nada.
    if (nodo->sig == NULL) {
        return FAILURE;
    }

    // Actualiza el puntero al siguiente nodo del nodo anterior.
    if (anterior != NULL) {
        anterior->sig = nodo->sig;
    } else {
        rs->cab = NULL;
    }

    // Libera la memoria del nodo eliminado.
    free(nodo);
    return SUCCESS;
}

void printList(ListaShip rs){
if(rs.cab==NULL){
    printf("LA LISTA ESTA VACIA\n");
} else {

Nodo *nodo = rs.cab;

while(nodo!=NULL){
    printf("\n//////////////////////////////////////////////\n");
    printShipment(nodo->ship);
    printf("\n//////////////////////////////////////////////\n");
    nodo=nodo->sig;
}

}

}

#endif // TDA_LISTA_RESERVA_H_INCLUDED
