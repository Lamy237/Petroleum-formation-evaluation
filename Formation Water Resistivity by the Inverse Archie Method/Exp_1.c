/*
EXPERIMENT 1 (PFE lab)
------------------------------

By Albert Lamy Christian (19BPE1026)

Objective: Determination of the Formation Water Resistivity (Rw) by the Inverse Archie Method.

Date of submission: August 26, 2021.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(int argc, char *argv[])
{
    double *porosity = NULL, *rwa = NULL;
    double rt = 20, rw = 0, a = 1, m = 2;
    int number = 0;

    fputs("\nHow many porosity values do you want to enter ? ", stdout);
    scanf("%d", &number);

    porosity = malloc(number * sizeof(double));
    rwa = malloc(number * sizeof(double));

    if(porosity == NULL || rwa == NULL)
    {
        puts("Unable to proceed due to memory allocation failure");
        exit(EXIT_FAILURE);
    }
    puts("");

    // Taking the porosity values
    for(int i=0; i<number; i++)
    {
        printf("porosity %d : ", i+1);
        scanf("%lf", &porosity[i]);
    }

    // Calculating Rwa for each porosity value
    for(int i=0; i<number; i++)
    {
        rwa[i] = (pow(porosity[i], m) * rt) / a;
    }

    rw = rwa[0];

    for(int i=0; i<number; i++)
    {
        if(rwa[i] < rw)
        {
            rw = rwa[i];
        }
    }

    puts("\nThe Apparent Formation Water Resistivity (Rwa) values are : \n");

    for(int i=0; i<number; i++)
    {
        printf("Rwa %d = %.1lf ohm.m\n", i+1, rwa[i]);
    }

    printf("\nThe Formation water resistivity (Rw) is : %.1lf ohm.m\n", rw);

    free(porosity);
    free(rwa);

    return EXIT_SUCCESS;
}
