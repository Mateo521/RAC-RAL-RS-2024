#ifndef TDA_LISTA_RESERVA_H_INCLUDED
#define TDA_LISTA_RESERVA_H_INCLUDED
#include "shipment.h"
struct nodo{
Shipment vipd;
struct Nodo *ps;
};typedef struct nodo Nodo;

typedef struct {
Nodo *cur;
Nodo *acc;
Nodo *aux;} lista_de_shipments;

void init(lista_de_shipments *l){
(*l).acc = NULL;
(*l).cur = NULL;
(*l).aux = NULL;
}

void insertl(lista_de_shipments *l, Shipment a){
    Nodo *p;
    p=(Nodo*)malloc(sizeof(Nodo));
    if ((*l).cur == (*l).acc){
(*p).vipd=a;
(*p).ps=(*l).cur;
(*l).acc=p;
(*l).cur=p;
}
else{
    (*p).vipd=a;
    (*p).ps=(*l).cur;
    (*l).aux->ps=p;
    (*l).cur=p;
};}

void foward(lista_de_shipments *l){
(*l).aux=(*l).cur;
(*l).cur= l->cur->ps;
}

void reset(lista_de_shipments *l){
(*l).cur=(*l).acc;
(*l).aux=(*l).acc;
}

int isOos(lista_de_shipments *l){
if ((l)->cur==NULL)
    return 1;
    else
    return 0;
}

int isFull(){
if ((Nodo*)malloc(sizeof(Nodo*))==NULL)
    return 1;
    else
    return 0;
}

int isEmpty(lista_de_shipments *l){
    if (((*l).acc)==NULL)
        return 1;
    else
        return 0;
}

void supress(lista_de_shipments *l){
    if ((*l).acc == (*l).cur){
        (*l).acc=l->cur->ps;
        (*l).aux=l->cur->ps;
        free((*l).cur);
        (*l).cur=(l)->acc;
    }
    else
    {
        (*l).aux->ps=l->cur->ps;
        free((*l).cur);
        (*l).cur=(l)->aux->ps;

    }}

Shipment* copy(lista_de_shipments *a){
    return &a->cur->vipd;
}













#endif // TDA_LISTA_RESERVA_H_INCLUDED
