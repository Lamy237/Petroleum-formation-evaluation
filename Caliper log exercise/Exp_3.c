/*
EXPERIMENT 3 (PFE lab)
------------------------------

By Albert Lamy Christian (19BPE1026)

Objective: Measurement of required cement volume.

Date of submission: September 16, 2021.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double mudcake_thickness(double bit_dia, double hole_dia);
double borehole_vol(double hole_dia, int start_depth, int end_depth);
double cement_vol(double hole_dia, double casing_dia, int start_depth, int end_depth);


int main(int argc, char *argv[])
{
    puts("=== MUDCAKE THICKNESS ===\n");
    printf("Mudcake thickness in the interval 2980 m to 3035 m, hmc = %.2lf inches\n", mudcake_thickness(8.5, 7.5));
    printf("\nMudcake thickness in the interval 3082 m to 3145 m, hmc = %.2lf inches\n\n", mudcake_thickness(8.5, 8));

    puts("\n=== BOREHOLE VOLUME ===\n");
    printf("Approximate borehole volume in the interval 2900 m to 3250 m, Vh = %.2lf litres\n\n", borehole_vol(8.85, 2900, 3250));

    puts("\n=== CEMENT VOLUME ===\n");
    printf("Cement volume required to complete the borehole between 2900 m and 3250 m, Vcement = %.2lf litres\n", cement_vol(8.85, 7, 2900, 3250));

    return EXIT_SUCCESS;
}


double mudcake_thickness(double bit_dia, double hole_dia)
{
    return (bit_dia - hole_dia) / 2;
}


double borehole_vol(double hole_dia, int start_depth, int end_depth)
{
    if(start_depth > end_depth || start_depth < 0 || end_depth < 0)
        return -1;

    // Borehole volume in litres/m
    double volume = pow(hole_dia, 2)/2 + 0.012;

    if(end_depth != 0)
    {
        // Borehole volume in litres
        volume *= (end_depth - start_depth);
    }

    return volume;
}


double cement_vol(double hole_dia, double casing_dia, int start_depth, int end_depth)
{
    if(start_depth > end_depth || start_depth < 0 || end_depth < 0)
        return -1;

    // Cement volume in litres/m
    double volume = 0.5 * (pow(hole_dia, 2) - pow(casing_dia, 2)) + 0.01;

    if(end_depth != 0)
    {
        // Cement volume in litres
        volume *= (end_depth - start_depth);
    }

    return volume;
}

