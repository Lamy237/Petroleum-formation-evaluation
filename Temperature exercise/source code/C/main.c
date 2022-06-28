/*
main.c
-------

By Albert Lamy Christian (19BPE1026) for EXPERIMENT 6 (PFE lab)

Objective: To calculate bottom hole temperature (BHT) of the formation.

Date of submission: November 19, 2021.
*/

#include <stdio.h>
#include <stdlib.h>

#include "hashtables.h"
#include "functions.h"


int main(int argc, char *argv[])
{
    Logs *table[TABLE_SIZE] = {NULL};

    double circulationTime = 6, formationDepth = 3300;
    double seaFloor = 300, seaFloorTemp = 10;

    // Adding log data
    logs_insert(table, "DIL log", formationDepth, 241, 8.25);
    logs_insert(table, "FDC log", formationDepth, 257, 11);
    logs_insert(table, "SNP log", formationDepth, 266, 13.5);
    logs_insert(table, "Dipmeter", formationDepth, 273, 16.5);

    compute_result(table, circulationTime);
    logs_print(table);

    // Computing the true formation temperature
    // Data taken from the horner plot (Temperature Vs. (t+T)/T), excel file
    double x = 1, slope = -88.11410788, yIntercept = 393.2012448;
    double formationTemp = (slope * x) + yIntercept;

    printf("\n\nThe true formation temperature at %.0f m is %.5f deg_F or %.5f deg_C\n\n", formationDepth, formationTemp, fahrenheit_to_celsius(formationTemp));


    // Computing the mean temperature gradient
    double meanTempGrad_C = (fahrenheit_to_celsius(formationTemp) - seaFloorTemp) / (formationDepth - seaFloor);
    double meanTempGrad_F = (formationTemp - celsius_to_fahrenheit(seaFloorTemp)) / (formationDepth - seaFloor);

    printf("The mean temperature gradient in the well is %.5f deg_F/m or %.5f deg_C/m\n\n", meanTempGrad_F, meanTempGrad_C);


    // Computing the temperature at 3100 m
    double depth = 3100;
    printf("The temperature at %.0f m is %.5f deg_F or %.5f deg_C\n\n", depth, meanTempGrad_F * depth, meanTempGrad_C * depth);

    logs_free(table);

    return EXIT_SUCCESS;
}

