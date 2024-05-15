#ifndef RS_H_INCLUDED
#define RS_H_INCLUDED
#define MAXRS 207 //p=1.45 por lo que el resultado es techo(206.8965)=207 y no hace falta acercarlo al numero primo mas cercano

struct nodo{
Shipment vipd;
struct Nodo *ps;
};typedef struct nodo Nodo;



typedef struct {
Nodo *cur;
Nodo *acc;
Nodo *aux;} lista_de_shipments;

typedef struct{
    lista_de_shipments ships[MAXRS];
    int cant;

    int indicador[MAXRS];
}rs;

void initializeRS(rs *rs){
    int i;
    for (i=0;i<MAXRS;i++){
        //init(&rs->ships[i]);
        Nodo *actual = rs->ships[i].acc;
        Nodo *siguiente;

    while (actual != NULL) {
        siguiente = actual->ps;
        free(actual);
        actual = siguiente;
    }
        rs->ships[i].acc = NULL;
        rs->ships[i].cur = NULL;
        rs->ships[i].aux = NULL;
        rs->indicador[i]=0;
    }
    rs->cant=0;
}

int LocalizeRs(rs *rs, int *j, char *code, float *costo){

    int i=hashing(code,MAXRS);
    (*j)=i;
    if(rs->ships[i].acc == NULL){
        (*costo)++;
        return FAILURE;
    }
    //reset(&rs->ships[i]);
    rs->ships[i].cur=rs->ships[i].acc;
    rs->ships[i].aux=rs->ships[i].acc;
    while(rs->ships[i].cur != NULL && strcmp(rs->ships[i].cur->vipd.code, code)!=0){
        //foward(&rs->ships[i]);
        rs->ships[i].aux=rs->ships[i].cur;
        rs->ships[i].cur= rs->ships[i].cur->ps;
        (*costo)++;
    }
    if (rs->ships[i].cur!=NULL)
        return SUCCESS;
    else
        return FAILURE;
}

int altaRS(rs *rs, Shipment a){
    if (rs->cant==MAXRS)
        return FAILURE;

    int i, costos;

    if(LocalizeRs(rs,&i,a.code,&costos)==SUCCESS)
        return FAILURE;

    //insertl(&rs->ships[i],a);
     Nodo *p;
    p=(Nodo*)malloc(sizeof(Nodo));
    if (rs->ships[i].cur == rs->ships[i].acc){
(*p).vipd=a;
(*p).ps=rs->ships[i].cur;
rs->ships[i].acc=p;
rs->ships[i].cur=p;
}
else{
    (*p).vipd=a;
    (*p).ps=rs->ships[i].cur;
    rs->ships[i].aux->ps=p;
    rs->ships[i].cur=p;
}
    rs->cant++;
    rs->indicador[i]=1;
    return SUCCESS;
}

int bajaRS(rs *rs, Shipment a){
    if (rs->cant==0)
        return FAILURE;

    int i, costos;

    if(LocalizeRs(rs,&i,a.code,&costos)==FAILURE)
        return FAILURE;

    //supress(&rs->ships[i]);
    if (rs->ships[i].acc == rs->ships[i].cur){
        rs->ships[i].acc = rs->ships[i].cur->ps;
        rs->ships[i].aux=rs->ships[i].cur->ps;
        free(rs->ships[i].cur);
        rs->ships[i].cur = rs->ships[i].acc;
    }
    else
    {
        rs->ships[i].aux->ps=rs->ships[i].cur->ps;
        free(rs->ships[i].cur);
        rs->ships[i].cur=rs->ships[i].aux->ps;

    }
    rs->cant--;

}

int evocarRS(rs *rs, Shipment a, float *costo, Shipment *aux){
    if(rs->cant==0)
        return FAILURE;

    int i;
    float costos=0.0;

    if(LocalizeRs(rs,&i,a.code,&costos)==FAILURE){
        *costo=costos;
        return FAILURE;
    } else {
        *costo=costos;
        return SUCCESS;
    }



}
printRS(rs *rs){



}

#endif // RS_H_INCLUDED
