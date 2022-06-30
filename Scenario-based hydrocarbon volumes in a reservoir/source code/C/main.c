/*
main.c
------

By Albert Lamy Christian (19BPE1026) for EXPERIMENT 7 (PFE lab)

Objective: To calculate scenario-based Hydrocarbon Volumes in a Reservoir.

Date of submission: November 16, 2021.
*/

#include <stdio.h>
#include <stdlib.h>

#include "reservoir.h"


int main(int argc, char*argv[])
{
    Reservoir resOil;

    set_reservoir(&resOil, "oil", 4900, 20, 20, 15, 1.65);
    print(&resOil, 20);

    // Repeat the process for each case and for the gas reservoir

    return EXIT_SUCCESS;
}

