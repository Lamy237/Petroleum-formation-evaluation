/*
EXPERIMENT 5 (PFE lab)
------------------------------

By Albert Lamy Christian (19BPE1026)

Objective: To determine Formation Temperature (Tf).

Date of submission: October 10, 2021.
*/

#include <stdio.h>
#include <stdlib.h>


double fahrenheit_to_celsius(double temperature);


int main (int argc, char *argv[])
{
     double surface_temp = 0, bottom_hole_temp = 0, total_depth = 0, formation_depth = 0;
     double geothermal_grad = 0, formation_temp = 0;

     fputs("\nSurface temperature (deg_F): ", stdout);
     scanf("%lf", &surface_temp);
     fputs("Bottom hole temperature (deg_F): ", stdout);
     scanf("%lf", &bottom_hole_temp);
     fputs("Total depth (ft): ", stdout);
     scanf("%lf", &total_depth);
     fputs("Formation depth (ft): ", stdout);
     scanf("%lf", &formation_depth);

     geothermal_grad = (bottom_hole_temp - surface_temp) / total_depth;

     formation_temp = (geothermal_grad * formation_depth) + surface_temp;

     printf("\nThe formation temperature (Tf) is %.1f degree Fahrenheit or %.1f degree Celsius.\n", formation_temp, fahrenheit_to_celsius(formation_temp));

    return EXIT_SUCCESS;
}


double fahrenheit_to_celsius(double temperature)
{
    temperature = (temperature - 32) * 5/9;
    return temperature;
}

