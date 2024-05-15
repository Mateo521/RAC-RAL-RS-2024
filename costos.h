#ifndef COSTOS_H_INCLUDED
#define COSTOS_H_INCLUDED

typedef struct{
    float maxAltas;      //Costo maximo
    float acAltas;        //Costo acumulado
    float MedioAltas;  //Costo medio
    int cantAltas;    //Cantidad de altas

    float maxBajas;
    float acBajas;
    float MedioBajas;
    int cantBajas;

    float maxEvocarE; //E= exitoso
    float acEvocarE;
    float MedioEvocarE;
    int cantEvocarE;

    float maxEvocarF; //F = Fracaso
    float acEvocarF;
    float MedioEvocarF;
    int cantEvocarF;
}costos;

typedef struct {
    costos rac;
    costos ral;
    costos rs;
}TablaCostos;


void resetTabla(TablaCostos *tabla){

    //RAC
    tabla->rac.maxAltas = 0.0;
    tabla->rac.acAltas = 0.0;
    tabla->rac.MedioAltas = 0.0;
    tabla->rac.cantAltas = 0;

    tabla->rac.maxBajas = 0.0;
    tabla->rac.acBajas = 0.0;
    tabla->rac.MedioBajas = 0.0;
    tabla->rac.cantBajas = 0;

    tabla->rac.maxEvocarE = 0.0;
    tabla->rac.acEvocarE = 0.0;
    tabla->rac.MedioEvocarE = 0.0;
    tabla->rac.cantEvocarE = 0;

    tabla->rac.maxEvocarF = 0.0;
    tabla->rac.acEvocarF = 0.0;
    tabla->rac.MedioEvocarF = 0.0;
    tabla->rac.cantEvocarF = 0;

    //RAL
    tabla->ral.maxAltas = 0.0;
    tabla->ral.acAltas = 0.0;
    tabla->ral.MedioAltas = 0.0;
    tabla->ral.cantAltas = 0;

    tabla->ral.maxBajas = 0.0;
    tabla->ral.acBajas = 0.0;
    tabla->ral.MedioBajas = 0.0;
    tabla->ral.cantBajas = 0;

    tabla->ral.maxEvocarE = 0.0;
    tabla->ral.acEvocarE = 0.0;
    tabla->ral.MedioEvocarE = 0.0;
    tabla->ral.cantEvocarE = 0;

    tabla->ral.maxEvocarF = 0.0;
    tabla->ral.acEvocarF = 0.0;
    tabla->ral.MedioEvocarF = 0.0;
    tabla->ral.cantEvocarF = 0;

    //RS
    tabla->rs.maxAltas = 0.0;
    tabla->rs.acAltas = 0.0;
    tabla->rs.MedioAltas = 0.0;
    tabla->rs.cantAltas = 0;

    tabla->rs.maxBajas = 0.0;
    tabla->rs.acBajas = 0.0;
    tabla->rs.MedioBajas = 0.0;
    tabla->rs.cantBajas = 0;

    tabla->rs.maxEvocarE = 0.0;
    tabla->rs.acEvocarE = 0.0;
    tabla->rs.MedioEvocarE = 0.0;
    tabla->rs.cantEvocarE = 0;

    tabla->rs.maxEvocarF = 0.0;
    tabla->rs.acEvocarF = 0.0;
    tabla->rs.MedioEvocarF = 0.0;
    tabla->rs.cantEvocarF = 0;

}
void printTabla(TablaCostos tabla) {
     printf("\n\n\t\t\t  ________________________________________________________________________\n"
        "\t\t\t |                           |              |              |              |\n"
        "\t\t\t |                           |     RAL      |    RAC       |     RS       |\n"
        "\t\t\t |___________________________|______________|______________|______________|\n"
        "\t\t\t | Evocar exitoso            |              |              |              |\n"
        "\t\t\t |    Cantidad               |     %d      |     %d      |     %d      |\n"
        "\t\t\t |    Costo Acumulado        |     %.2f   |     %.2f   |     %.2f    |\n"
        "\t\t\t |    Costo Maximo           |     %.2f     |     %.2f     |     %.2f     |\n"
        "\t\t\t |    Costo Promedio         |     %.2f     |     %.2f     |     %.2f     |\n"
        "\t\t\t |___________________________|______________|______________|______________|\n"
        "\t\t\t | Evocar fracaso            |              |              |              |\n"
        "\t\t\t |    Cantidad               |     %d      |     %d      |     %d      |\n"
        "\t\t\t |    Costo Acumulado        |     %.2f   |     %.2f   |     %.2f    |\n"
        "\t\t\t |    Costo Maximo           |     %.2f     |     %.2f    |     %.2f     |\n"
        "\t\t\t |    Costo Promedio         |     %.2f     |     %.2f     |     %.2f     |\n"
        "\t\t\t |___________________________|______________|______________|______________|\n\n",

        tabla.ral.cantEvocarE, tabla.rac.cantEvocarE, tabla.rs.cantEvocarE,
        tabla.ral.acEvocarE, tabla.rac.acEvocarE, tabla.rs.acEvocarE,
        tabla.ral.maxEvocarE, tabla.rac.maxEvocarE, tabla.rs.maxEvocarE,
        tabla.ral.MedioEvocarE, tabla.rac.MedioEvocarE, tabla.rs.MedioEvocarE,
        tabla.ral.cantEvocarF, tabla.rac.cantEvocarF, tabla.rs.cantEvocarF,
        tabla.ral.acEvocarF, tabla.rac.acEvocarF, tabla.rs.acEvocarF,
        tabla.ral.maxEvocarF, tabla.rac.maxEvocarF, tabla.rs.maxEvocarF,
        tabla.ral.MedioEvocarF, tabla.rac.MedioEvocarF, tabla.rs.MedioEvocarF);
}

#endif // COSTOS_H_INCLUDED
