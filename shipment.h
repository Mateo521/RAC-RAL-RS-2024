#ifndef SHIPMENT_H_INCLUDED
#define SHIPMENT_H_INCLUDED
#define SUCCESS 1
#define FAILURE 0
#define FAILURE_EX 2
#define MAX 300
#include "person.h"
#define VIRGEN "*"
#define LIBRE "+"

typedef struct {
    char code[8];
    Person receiver;
    char receiverAddress[81];
    Person sender;
    char sendingDate[11];
    char receptionDate[11];
} Shipment;

int hashing( char* x, int M) {
    int longitud , i;
    int contador = 0;
    longitud = strlen(x);
    for ( i = 0; i < longitud ; i++ )
        contador +=( (int)x[i] ) * ( i+1 );
    return ( contador % M ) ;
}

void printShipment(Shipment shipment){

            printf("\t- CODIGO DE ENVIO: %s\n\n", shipment.code);
            printf("\t* DATOS DEL RECEPTOR:\n");
            printf("\t  - DNI: %d\n", shipment.receiver.dni);
            printf("\t  - NOMBRE COMPLETO:  %s\n", shipment.receiver.fullName);
            printf("\t  - DIRECCION: %s\n\n", shipment.receiverAddress);
            printf("\t* DATOS DEL EMISOR:\n");
            printf("\t  - DNI: %d\n", shipment.sender.dni);
            printf("\t  - NOMBRE COMPLETO: %s\n\n", shipment.sender.fullName);
            printf("\t- FECHA DE ENVIO: %s\n", shipment.sendingDate);
            printf("\t- FECHA DE RECEPCION: %s\n", shipment.receptionDate);
}


int compareShipments(Shipment s1, Shipment s2) {
    if ((strcmp(s1.code, s2.code) == 0) &&
        (cmpPersons(s1.receiver, s2.receiver) == 0) &&
        (strcmp(s1.receiverAddress, s2.receiverAddress) == 0) &&
        (cmpPersons(s1.sender, s2.sender) == 0) &&
        (strcmp(s1.sendingDate, s2.sendingDate) == 0) &&
        (strcmp(s1.receptionDate, s2.receptionDate) == 0)) {
        return SUCCESS;
    } else {
        return FAILURE;
    }
}


#endif // SHIPMENT_H_INCLUDED
