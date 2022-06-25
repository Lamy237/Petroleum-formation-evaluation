/*
EXPERIMENT 4 (PFE lab)
------------------------------

By Albert Lamy Christian (19BPE1026)

Objective: To calculate Resistivity of a given drilling fluid at Formation temperature.

Date of submission: October 10, 2021.
*/

#include <stdio.h>
#include <stdlib.h>


double fahrenheit_to_celsius(double temperature);


int main(int argc, char *argv[])
{
    double r1 = 1.2, r2 = 0, t1 = 75, t2 = 160;

    r2 = r1 * (t1 + 6.77) / (t2 + 6.77);

    printf("\nThe resistivity of drilling mud at formation temperature (Tf): %.4lf ohm-m\n", r2);

    //Converting the the temperatures into degree Celsius
    t1 = fahrenheit_to_celsius(t1);
    t2 = fahrenheit_to_celsius(t2);

    r2 = r1 * (t1 + 21.5) / (t2 + 21.5);

    printf("\nThe resistivity of drilling mud at formation temperature (Tf): %.4lf ohm-m\n", r2);

    return EXIT_SUCCESS;
}


double fahrenheit_to_celsius(double temperature)
{
    temperature = (temperature - 32) * 5/9;
    return temperature;
}

