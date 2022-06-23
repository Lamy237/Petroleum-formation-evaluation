/*
EXPERIMENT 2 (PFE lab)
------------------------------

By Albert Lamy Christian (19BPE1026)

Objective: To calculate Hydrocarbon Volumes in a Reservoir.

Date of submission: September 09, 2021.
*/

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    double area = 0, thickness = 0, porosity = 0, water_saturation = 0, formation_vol_fact = 0;
    int reservoir_type = 0;

    do
    {
        fputs("\nReservoir type (1 for oil reservoir / 2 for gas reservoir) : ", stdout);
        scanf("%d", &reservoir_type);

        if(reservoir_type != 1 && reservoir_type != 2)
            puts("Choice not registered, kindly read the instructions and try again");
    }while(reservoir_type != 1 && reservoir_type != 2);

    fputs("\nArea of the field (acres): ", stdout);
    scanf("%lf", &area);
    fputs("Thickness of the reservoir (ft): ", stdout);
    scanf("%lf", &thickness);
    fputs("Porosity of the formation (%): ", stdout);
    scanf("%lf", &porosity);
    fputs("Water saturation (%): ", stdout);
    scanf("%lf", &water_saturation);
    printf("%s formation volume factor: ", (reservoir_type == 1) ? "Oil": "Gas");
    scanf("%lf", &formation_vol_fact);

    printf("\n\n===== %s Reservoir =====\n\n", (reservoir_type == 1) ? "Oil": "Gas");

    if(reservoir_type == 1)
    {
        double ooip = 7758 * area * thickness * (porosity/100) * (1 - (water_saturation/100));
        double stooip = ooip / formation_vol_fact;
        printf("Oil originally in place (OIP) : %.2lf bbl\n", ooip);
        printf("Stock tank oil originally in place (STOOIP) : %.2lf bbl\n\n", stooip);
    }
    else
    {
        double goip = 43560 * area * thickness * (porosity/100) * (1 - (water_saturation/100));
        double stgoip = goip / formation_vol_fact;
        printf("Gas originally in place (GOIP) : %.2lf cu.ft\n", goip);
        printf("Stock tank gas originally in place (STGOIP) : %.2lf cu.ft\n\n", stgoip);
    }

    return EXIT_SUCCESS;
}
