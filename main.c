#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include <ctype.h>
#include <math.h>
#include "rac.h"
#include "ral.h"
#include "costos.h"
#include "rs.h"

//typedef int bool;

////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
SEGUN LOS RESULTADOS OBTENIDOS EN EL LABORATORIO ES MAS CONVENIENTE UTILIZAR EL REBALSE SEPARADO YA QUE SU ESFUERZO PROMEDIO
Y LA CANTIDAD ACUMULADA TANTO EN EL FRACASO COMO EN EL EXITO DE LA EVOCACION, SON MUCHISIMO MENORES EN COMPARACION AL REBALSE LINEAL
Y AL REBALSE LINEAL CUADRATICO

RESULTADOS:
                         |                           |              |              |              |
                         |                           |     RAL      |    RAC       |     RS       |
                         |___________________________|______________|______________|______________|
                         | Evocar exitoso            |              |              |              |
                         |    Cantidad               |     258      |     258      |     258      |
                         |    Costo Acumulado        |     433.00   |     445.00   |     333.00    |
                         |    Costo Maximo           |     6.00     |     7.00     |     4.00     |
                         |    Costo Promedio         |     1.68     |     1.72     |     1.29     |
                         |___________________________|______________|______________|______________|
                         | Evocar fracaso            |              |              |              |
                         |    Cantidad               |     105      |     105      |     105      |
                         |    Costo Acumulado        |     379.00   |     387.00   |     300.00    |
                         |    Costo Maximo           |     9.00     |     11.00    |     3.00     |
                         |    Costo Promedio         |     3.61     |     3.69     |     2.86    |
                         |___________________________|______________|______________|______________|


*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// MENU /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//INICIALIZAR ESTRUCTURAS
void initializeAll(TablaCostos *tabla, rac *rac, ral *ral, rs *rs){
    initializeRAC(rac);
    initializeRAL(ral);
    initializeRS(rs);
    resetTabla(tabla);
}

//COMPARACION DE ESTRUCTURAS
int readFile(TablaCostos *tabla,rac *rac, ral *ral, rs *rs){
    int tipo;
    FILE* fp ;
    Shipment aux, auxS;
    int operacion, statusEvocar = 0;
    float costo = 0.0;

    if ((fp = fopen ("Operaciones-Envios.txt","r")) == NULL){
        return 0;
    }else{
        if(fgetc(fp) != EOF){
            rewind(fp);
            while (!(feof(fp) )){
                fscanf(fp,"%d",&operacion);
                if (operacion == 1 || operacion == 2){
                    fscanf(fp, " %[^\n]", aux.code);
                    for(int i=0; aux.code[i] != '\0'; i++){
                       aux.code[i]=toupper(aux.code[i]);
                    }
                    fscanf(fp, "%d", &aux.receiver.dni);
                    fscanf(fp, " %[^\n]", aux.receiver.fullName);
                    fscanf(fp, " %[^\n]", aux.receiverAddress);
                    fscanf(fp, "%d", &aux.sender.dni);
                    fscanf(fp, " %[^\n]", aux.sender.fullName);
                    fscanf(fp, " %[^\n]", aux.sendingDate);
                    fscanf(fp, " %[^\n]", aux.receptionDate);
                    fgetc(fp);
                }
                switch(operacion){
                case 1:{ //ALTAS
                    //RAC------------------------------------------------------------
                    costo = 0.0;
                    if (rac->cant < MAX){
                        costo = 0.0;
                        if ((altaRAC(rac, aux)) == SUCCESS){
                            tabla->rac.acAltas = tabla->rac.acAltas + costo;
                            tabla->rac.cantAltas++;
                            if (tabla->rac.maxAltas < costo){
                                tabla->rac.maxAltas = costo;
                            }
                        }
                    }
                    ///COMPLETAR
                     //RAL------------------------------------------------------------
                    costo = 0.0;
                    if (ral->cant < MAX){
                        costo = 0.0;
                        if ((altaRAL(ral, aux)) == SUCCESS){
                            tabla->ral.acAltas = tabla->ral.acAltas + costo;
                            tabla->ral.cantAltas++;
                            if (tabla->ral.maxAltas < costo){
                                tabla->ral.maxAltas = costo;
                            }
                        }
                    }
                    //RS-------------------------------------------------------------
                    altaRS(rs,aux);

                }break;
                case 2:{ //BAJAS
                     //RACS--------------------------------------------------------------
                    if (rac->cant != 0){
                        costo = 0.0;
                        if ((bajaRAC(rac,aux)) == SUCCESS){
                            tabla->rac.cantBajas++;
                            tabla->rac.acBajas=tabla->rac.acBajas + costo;
                            if (tabla->rac.maxBajas< costo){
                                tabla->rac.maxBajas = costo;
                            }
                        }

                    }
                    ///COMPLETAR
                    //RAL------------------------------------------------------------
                    if (ral->cant != 0){
                        costo = 0.0;
                        if ((bajaRAL(ral,aux)) == SUCCESS){
                            tabla->ral.cantBajas++;
                            tabla->ral.acBajas=tabla->ral.acBajas + costo;
                            if (tabla->ral.maxBajas< costo){
                                tabla->ral.maxBajas = costo;
                            }
                        }

                    }
                    //RS-------------------------------------------------------------

                bajaRS(rs,aux);

                }break;
                case 3:{ //EVOCAR
                    fscanf(fp, " %[^\n]", aux.code);
                    for(int i=0; aux.code[i] != '\0'; i++){
                       aux.code[i]=toupper(aux.code[i]);
                    }
                    fgetc(fp);
                    //RAC--------------------------------------------------------------
                    if (rac->cant != 0){
                        costo = 0.0;
                        statusEvocar = evocarRAC(rac, aux.code, &auxS, &costo);
                        if ( statusEvocar == SUCCESS){
                            tabla->rac.cantEvocarE++;
                            tabla->rac.acEvocarE = tabla->rac.acEvocarE + costo;
                            if (tabla->rac.maxEvocarE < costo){
                                tabla->rac.maxEvocarE = costo;
                            }
                        }else{
                            tabla->rac.cantEvocarF++;
                            tabla->rac.acEvocarF = tabla->rac.acEvocarE + costo;
                            if (tabla->rac.maxEvocarF < costo){
                                tabla->rac.maxEvocarF = costo;
                            }
                        }
                    }else{
                        tabla->rac.cantEvocarF++;
                    }

                    ///COMPLETAR
                    //RAL------------------------------------------------------------
                    if (ral->cant != 0){
                        costo = 0.0;
                        statusEvocar = evocarRAL(ral, aux.code, &auxS, &costo);
                        if (statusEvocar == SUCCESS){
                            tabla->ral.cantEvocarE++;
                            tabla->ral.acEvocarE = tabla->ral.acEvocarE + costo;
                            if (tabla->ral.maxEvocarE < costo){
                                tabla->ral.maxEvocarE = costo;
                            }
                        }else{
                            tabla->ral.cantEvocarF++;
                            tabla->ral.acEvocarF = tabla->ral.acEvocarE + costo;
                            if (tabla->ral.maxEvocarF < costo){
                                tabla->ral.maxEvocarF = costo;
                            }
                        }
                    }else{
                        tabla->ral.cantEvocarF++;
                    }
                    //RS--------------------------------------------------------------
                        costo = 0.0;
                        statusEvocar = evocarRS(rs,aux,&costo,&auxS);
                        if (statusEvocar == SUCCESS){
                            tabla->rs.cantEvocarE++;
                            tabla->rs.acEvocarE = tabla->rs.acEvocarE + costo;
                            if (tabla->rs.maxEvocarE < costo){
                                tabla->rs.maxEvocarE = costo;
                            }
                        }else{

                            tabla->rs.cantEvocarF++;
                            tabla->rs.acEvocarF = tabla->rs.acEvocarE + costo;
                            if (tabla->rs.maxEvocarF < costo){
                                tabla->rs.maxEvocarF = costo;
                            }
                        }





                }break;
                default: return 0;

                }
                }
                }
                fclose(fp);

        //MEDIO RAC//--------------------------------------------------------------
        tabla->rac.MedioAltas = tabla->rac.acAltas / tabla->rac.cantAltas;
        tabla->rac.MedioBajas = tabla->rac.acBajas / tabla->rac.cantBajas;
        tabla->rac.MedioEvocarE = tabla->rac.acEvocarE / tabla->rac.cantEvocarE;
        tabla->rac.MedioEvocarF = tabla->rac.acEvocarF / tabla->rac.cantEvocarF;
        //MEDIO RAL//------------------------------------------------------------
        tabla->ral.MedioAltas = tabla->ral.acAltas / tabla->ral.cantAltas;
        tabla->ral.MedioBajas = tabla->ral.acBajas / tabla->ral.cantBajas;
        tabla->ral.MedioEvocarE = tabla->ral.acEvocarE / tabla->ral.cantEvocarE;
        tabla->ral.MedioEvocarF = tabla->ral.acEvocarF / tabla->ral.cantEvocarF;
        //MEDIO RS//--------------------------------------------------------------
        tabla->rs.MedioEvocarE = tabla->rs.acEvocarE / tabla->rs.cantEvocarE;
        tabla->rs.MedioEvocarF = tabla->rs.acEvocarF / tabla->rs.cantEvocarF;
            return SUCCESS;

    }

}





int main()
{

    int opt,optE=0;
    Shipment s;
    rac rac;
    ral ral;
    rs rs;
    TablaCostos tabla;
    initializeAll(&tabla,&rac,&ral,&rs);

    do{
        system("clear");

            printf("\n- OPCION (Luego presione enter): ");
        printf("\n\t1-Comparacion de estructuras\n");
        printf("\t2-Mostrar estructuras\n");
        printf("\t3-Salir\n");
            scanf("%d",&opt);

            getchar();

            switch(opt){
            case 1: // COMPARAR ESTRUCTURAS
             system("clear");
                initializeAll(&tabla,&rac,&ral,&rs);
                readFile(&tabla,&rac,&ral,&rs);
            system("clear");
                printTabla(tabla);
           //     system("pause");


                break;
            case 2: // MOSTRAR ESTRUCTURAS
                do{
                   system("clear");
                        printf("\n\t\t\t\t     \n\n"
                       "\t___________________________________________________________________________________\n\n"
                       "\t\t\tMostrar Estructuras:  \n\n"
                       "\t\t\t< 1 > Rebalse Abierto Lineal (RAL) \n\n"
                       "\t\t\t< 2 > Rebalse Abierto Cuadratico (RAC) \n\n"
                       "\t\t\t< 3 > Rebalse Separado (RS) \n\n"
                       "\t\t\t< 4 > Volver al menu principar \n\n"
                       "\t___________________________________________________________________________________\n");

                 printf("\n- OPCION (Luego presione enter): ");
                scanf("%d", &optE);

                getchar();
                switch(optE){
                    case 1: //MOSTRAR RAL
                          system("clear");
                            printf("\n\n\n\tESTRUCTURA: REBALSE ABIERTO LINEAL\n\n");
                            printRAL(ral);
                        break;
                    case 2: //MOSTRAR RAC

                        system("clear");
                            printf("\n\n\n\tESTRUCTURA: REBALSE ABIERTO CUADRATICO\n\n");
                            printRAC(rac);

                        break;
                    case 3: //MOSTRAR RS
                         system("clear");
                            printf("\n\n\n\tESTRUCTURA: REBALSE SEPARADO; %i \n\n", rs.cant );
                       //     system("pause");

                        break;
                    case 4: //SALIR
                        break;
                    }
                }while(optE!=4);

                break;
            case 3: //SALIR
             system("clear");
                exit(0);
                break;

            }

    }
    while(opt!=3);
 system("clear");
    return 0;
}
