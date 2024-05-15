#ifndef RAC_H_INCLUDED
#define RAC_H_INCLUDED
#include "shipment.h"
#define MAXRAC 401 ///p=0.75


//ESTRUCTURA
typedef struct{
    Shipment shipments[MAXRAC];
    int cant;
}rac;

//INICIALIZAR
void initializeRAC (rac *rac){
    int i;
    for ( i = 0; i < MAXRAC; i++)
    {
        strcpy(rac->shipments[i].code, VIRGEN); //Ninguna celda ha sido usada
    }
    rac->cant = 0;
}

//LOCALIZAR
int localizarRAC(rac *rac, char code[], int *pos, float *celdasConsult)
{
    int i = hashing(code, MAXRAC), cont=0, celdaLibre = -1, p = 1, costosAux = 0;

    while ((cont < MAXRAC) && (strcmp(rac->shipments[i].code, VIRGEN)!=0) && (strcmp(rac->shipments[i].code, code)!=0)){

        if((celdaLibre==-1)&&(strcmp(rac->shipments[i].code,LIBRE)==0)){
                celdaLibre=i; //CELDA LIBRE EN I
        }

        i = (i + p) % MAXRAC;
        cont++;
        p+=1;
        costosAux++;
    }

    if(cont<MAXRAC){
        costosAux+=1;
    }
    (*celdasConsult)=costosAux;
    if ((cont<MAXRAC) && (stricmp(rac->shipments[i].code, code)==0)){ //EXITO
            (*pos)=i;
        return SUCCESS;
    } else if(cont<MAXRAC){ //FRACASO
                    if(celdaLibre!=-1){ //CELDA LIBRE
                        (*pos)=celdaLibre;
                        return FAILURE;
                    } else { //CELDA VIRGEN
                        (*pos)=i;
                        return FAILURE;
                    }
        } else { //FRACASO, RECORRI� TODA LA ESTRUCTURA
                return FAILURE_EX;
        }
}

//ALTA
int altaRAC (rac *rac, Shipment shipment)
{
    int pos;
    float celdasConsult = 0.0;
    int loc = localizarRAC (rac,shipment.code,&pos,&celdasConsult);
    if(loc == FAILURE ){ //EXITO, NO ESTA EN LA ESTRUCTURA
            rac->shipments[pos]=shipment;
            rac->cant++;
            return SUCCESS;
    } else if(loc == SUCCESS){ //FRACASO, ESTA EN LA ESTRUCURA
            return FAILURE;
        } else {
                return FAILURE_EX; //FRACASO, ESTRUCTURA LLENA
            }
}

//BAJA
int bajaRAC (rac *rac, Shipment shipment){
    int pos, confirm;
    float celdas_consultadas=0.0;
   if(localizarRAC(rac,shipment.code,&pos,&celdas_consultadas)==FAILURE){ //FRACASO, NO SE ENCUENTRA EN LA ESTRUCTURA
        return FAILURE;
    }else{
        confirm=compareShipments(shipment,rac->shipments[pos]);
        if(confirm==SUCCESS){ //EXITO, CELDA LIBRE
           strcpy(rac->shipments[pos].code, LIBRE);
            rac->cant--;
            return SUCCESS;
        }else{
            return FAILURE_EX; //FRACASO, NO SON IGUALES
        }
    }
}
//EVOCAR
int evocarRAC(rac *rac, char code[] ,Shipment *shipment, float* costo){
    int pos;
    float costosAux=0.0;
    if ( localizarRAC(rac,code,&pos,&costosAux) == FAILURE){ //FRACASO, NO SE ENCONTRO EN LA ESTRUCTURA
        (*costo) = costosAux;
        return FAILURE;
    }else{
        strcpy(shipment->code, rac->shipments[pos].code);
        shipment->receiver.dni = rac->shipments[pos].receiver.dni;
        strcpy(shipment->receiver.fullName, rac->shipments[pos].receiver.fullName);
        strcpy(shipment->receiverAddress, rac->shipments[pos].receiverAddress);
        shipment->sender.dni = rac->shipments[pos].sender.dni;
        strcpy(shipment->sender.fullName, rac->shipments[pos].sender.fullName);
        shipment->sender.dni = rac->shipments[pos].sender.dni;
        strcpy(shipment->sendingDate, rac->shipments[pos].sendingDate);
        strcpy(shipment->receptionDate, rac->shipments[pos].receptionDate);
        (*costo) = costosAux;
        return SUCCESS;
    }
}

//MOSTRAR
void printRAC (rac rac){
    int i = 0;
        for (i=0; i < MAXRAC ; i++) {
             if(strcmp(rac.shipments[i].code,LIBRE)==0){
            printf("\t--------------------------------------");
            printf("\n\tElemento N #%d de %d \n", i, MAXRAC);
            printf("\tCELDA LIBRE +\n");
            printf("\t--------------------------------------\n\n");
        }
        else if(strcmp(rac.shipments[i].code, VIRGEN)==0){
            printf("\n\t--------------------------------------");
            printf("\n\tElemento N #%d de %d \n", i, MAXRAC);
            printf("\tCELDA VIRGEN *\n");
           printf("\t--------------------------------------\n\n");
        }
         else {
                 printf("\n\t--------------------------------------");
                    printf("\n\tElemento N #%d de %d\n", i, MAXRAC);
                    printShipment(rac.shipments[i]);
                    printf("\t--------------------------------------\n");
            }
            if ((i+1) % 5 == 0) system("pause");
        }
}



#endif // RAC_H_INCLUDED
