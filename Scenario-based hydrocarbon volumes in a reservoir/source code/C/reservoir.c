/*
reservoir.c
-----------

By Albert Lamy Christian (19BPE1026)

Role: Definition of the functions used to manipulate the structure 'Reservoir'

Creation: November 11, 2021.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"
#include "reservoir.h"


static void init_reservoir(Reservoir *reservoir)
{
    reservoir->type[0] = '\0';

    for(int i=0; i<3; i++)
    {
        reservoir->area[i] = 0;
        reservoir->thickness[i] = 0;
        reservoir->porosity[i] = 0;
        reservoir->waterSaturation[i] = 0;
        reservoir->fvf[i] = 0;
        reservoir->result1[i] = 0;
        reservoir->result2[i] = 0;
        reservoir->percentageDiff[i] = 0;
    }
}


static unsigned int set_constant(Reservoir *reservoir)
{
    if(strncmp(reservoir->type, "oil", SIZE_CHAR) == 0)
        return 7758;
    else
        return 43560;
}


/* This function computes the hydrocarbon volumes if there is an error of ±percentageError in all the parameters */

static void compute_scenario_all(Reservoir *reservoir, double percentageError)
{
    unsigned int constant = set_constant(reservoir);

    percentageError /= 100;

    // Compute possibility 1 and 2 for each of the parameters
    reservoir->area[1] = reservoir->area[0] - (reservoir->area[0] * percentageError);
    reservoir->area[2] = reservoir->area[0] + (reservoir->area[0] * percentageError);

    reservoir->thickness[1] = reservoir->thickness[0] - (reservoir->thickness[0] * percentageError);
    reservoir->thickness[2] = reservoir->thickness[0] + (reservoir->thickness[0] * percentageError);

    reservoir->porosity[1] = reservoir->porosity[0] - (reservoir->porosity[0] * percentageError);
    reservoir->porosity[2] = reservoir->porosity[0] + (reservoir->porosity[0] * percentageError);

    reservoir->waterSaturation[1] = reservoir->waterSaturation[0] - (reservoir->waterSaturation[0] * percentageError);
    reservoir->waterSaturation[2] = reservoir->waterSaturation[0] + (reservoir->waterSaturation[0] * percentageError);

    reservoir->fvf[1] = reservoir->fvf[0] - (reservoir->fvf[0] * percentageError);
    reservoir->fvf[2] = reservoir->fvf[0] + (reservoir->fvf[0] * percentageError);

    // Calculate the hydrocarbon volumes
    reservoir->result1[1] = constant * reservoir->area[1] * reservoir->thickness[1] * (reservoir->porosity[1] / 100) * (1 - (reservoir->waterSaturation[1] / 100));
    reservoir->result1[2] = constant * reservoir->area[2] * reservoir->thickness[2] * (reservoir->porosity[2] / 100) * (1 - (reservoir->waterSaturation[2] / 100));

    // To get the result in millions (MMbbl or MMscf)
    reservoir->result1[1] /= 1000000;
    reservoir->result1[2] /= 1000000;

    reservoir->result2[1] = reservoir->result1[1] / reservoir->fvf[1];
    reservoir->result2[2] = reservoir->result1[2] / reservoir->fvf[2];

    // Compute the percentage difference
    reservoir->percentageDiff[1] = ((reservoir->result2[1] * 100) / reservoir->result2[0]) - 100;
    reservoir->percentageDiff[2] = ((reservoir->result2[2] * 100) / reservoir->result2[0]) - 100;
}


/* This function computes the hydrocarbon volumes if there is an error of ±percentageError in the passed parameters */

static void compute_scenario_focused(Reservoir *reservoir, char param[], double percentageError)
{
    unsigned int constant = set_constant(reservoir);

    percentageError /= 100;

    // Modify the specified parameter
    if(strncmp(param, "area", SIZE_CHAR) == 0)
    {
        reservoir->area[1] = reservoir->area[0] - (reservoir->area[0] * percentageError);
        reservoir->area[2] = reservoir->area[0] + (reservoir->area[0] * percentageError);
    }
    else if(strncmp(param, "thickness", SIZE_CHAR) == 0)
    {
        reservoir->thickness[1] = reservoir->thickness[0] - (reservoir->thickness[0] * percentageError);
        reservoir->thickness[2] = reservoir->thickness[0] + (reservoir->thickness[0] * percentageError);
    }
    else if(strncmp(param, "porosity", SIZE_CHAR) == 0)
    {
        reservoir->porosity[1] = reservoir->porosity[0] - (reservoir->porosity[0] * percentageError);
        reservoir->porosity[2] = reservoir->porosity[0] + (reservoir->porosity[0] * percentageError);
    }
    else if(strncmp(param, "water saturation", SIZE_CHAR) == 0)
    {
        reservoir->waterSaturation[1] = reservoir->waterSaturation[0] - (reservoir->waterSaturation[0] * percentageError);
        reservoir->waterSaturation[2] = reservoir->waterSaturation[0] + (reservoir->waterSaturation[0] * percentageError);
    }
    else if(strncmp(param, "fvf", SIZE_CHAR) == 0)
    {
        reservoir->fvf[1] = reservoir->fvf[0] - (reservoir->fvf[0] * percentageError);
        reservoir->fvf[2] = reservoir->fvf[0] + (reservoir->fvf[0] * percentageError);
    }

    // Calculate the hydrocarbon volumes
    reservoir->result1[1] = constant * reservoir->area[1] * reservoir->thickness[1] * (reservoir->porosity[1] / 100) * (1 - (reservoir->waterSaturation[1] / 100));
    reservoir->result1[2] = constant * reservoir->area[2] * reservoir->thickness[2] * (reservoir->porosity[2] / 100) * (1 - (reservoir->waterSaturation[2] / 100));

    // To get the result in millions (MMbbl or MMscf)
    reservoir->result1[1] /= 1000000;
    reservoir->result1[2] /= 1000000;

    reservoir->result2[1] = reservoir->result1[1] / reservoir->fvf[1];
    reservoir->result2[2] = reservoir->result1[2] / reservoir->fvf[2];

   // Compute the percentage difference
    reservoir->percentageDiff[1] = ((reservoir->result2[1] * 100) / reservoir->result2[0]) - 100;
    reservoir->percentageDiff[2] = ((reservoir->result2[2] * 100) / reservoir->result2[0]) - 100;
}


/* This function displays all the values ​​of the passed parameter on the same line */

static void display_param(Reservoir *reservoir, char param[])
{
    int maxDigits = 8;

    if(strncmp(param, "area", SIZE_CHAR) == 0)
    {
        add_spaces_after("Area, acres");

        for(int i=0; i<3; i++)
            split_fxn(reservoir->area[i], maxDigits);

    }
    else if(strncmp(param, "thickness", SIZE_CHAR) == 0)
    {
        add_spaces_after("Thickness, ft");

        for(int i=0; i<3; i++)
            split_fxn(reservoir->thickness[i], maxDigits);

    }
    else if(strncmp(param, "porosity", SIZE_CHAR) == 0)
    {
        add_spaces_after("Porosity, %");

        for(int i=0; i<3; i++)
            split_fxn(reservoir->porosity[i], maxDigits);

    }
    else if(strncmp(param, "water saturation", SIZE_CHAR) == 0)
    {
        add_spaces_after("water saturation, %");

        for(int i=0; i<3; i++)
            split_fxn(reservoir->waterSaturation[i], maxDigits);

    }
    else if(strncmp(param, "fvf", SIZE_CHAR) == 0)
    {
        if(strncmp(reservoir->type, "oil", SIZE_CHAR) == 0)
            add_spaces_after("Oil formation volume factor, bbl/STB");
        else
            add_spaces_after("Gas formation volume factor, cu.ft/STB");

        for(int i=0; i<3; i++)
            split_fxn(reservoir->fvf[i], maxDigits);

    }
    else if(strncmp(param, "result1", SIZE_CHAR) == 0)
    {
        if(strncmp(reservoir->type, "oil", SIZE_CHAR) == 0)
            add_spaces_after("Oil originally in place, MMbbl");
        else
            add_spaces_after("Gas originally in place, MMscf");

        for(int i=0; i<3; i++)
            split_fxn(reservoir->result1[i], maxDigits);

    }
    else if(strncmp(param, "result2", SIZE_CHAR) == 0)
    {
        if(strncmp(reservoir->type, "oil", SIZE_CHAR) == 0)
            add_spaces_after("Stock tank oil originally in place, MMbbl");
        else
            add_spaces_after("Stock tank gas originally in place, MMscf");

        for(int i=0; i<3; i++)
            split_fxn(reservoir->result2[i], maxDigits);

    }
    else if(strncmp(param, "percentage diff", SIZE_CHAR) == 0)
    {
        add_spaces_after("Percentage relative difference, %");

        for(int i=0; i<3; i++)
        {
            if(reservoir->percentageDiff[i] > 0)
            {
                fputs("+", stdout);
                split_fxn(reservoir->percentageDiff[i], maxDigits - 1);
            }
            else
            {
                split_fxn(reservoir->percentageDiff[i], maxDigits);
            }
        }
    }

    puts("");
}


/* Function to display a header before printing the reservoir data */

static void display_header()
{
    add_spaces_after("Parameter");
    puts("Base case\tPossibility1\tPossibility2");
    puts("-----------------------------------------------------------------------------------------------------");
}


void set_reservoir(Reservoir *reservoir, char type[], double area, double thickness, double porosity, double waterSaturation, double fvf)
{
    init_reservoir(reservoir);

    snprintf(reservoir->type, SIZE_CHAR, "%s", type);
    strlwr(reservoir->type);

    // Verify that the passed reservoir type is valid
    if(strncmp(reservoir->type, "oil", SIZE_CHAR) != 0 && strncmp(reservoir->type, "gas", SIZE_CHAR) != 0)
    {
        printf("Unknown reservoir type '%s'. Valid options are : {oil, gas}\n", reservoir->type);
        exit(EXIT_FAILURE);
    }

    unsigned int constant = set_constant(reservoir);
    thickness = meters_to_feet(thickness);

    for(int i=0; i<3; i++)
    {
        // Initialize all the indexes of each parameter to the same value
        // This will facilitate things when modifying only one of the parameters using 'compute_scenario_focused()'
        reservoir->area[i] = area;
        reservoir->thickness[i] = thickness;
        reservoir->porosity[i] = porosity;
        reservoir->waterSaturation[i] = waterSaturation;
        reservoir->fvf[i] = fvf;

        // Calculate the hydrocarbon volumes depending on the type of the reservoir
        // constant = 7758 for oil reservoir | constant = 43560 for gas reservoir
        reservoir->result1[i] = constant * reservoir->area[i] * reservoir->thickness[i] * (reservoir->porosity[i] / 100) * (1 - (reservoir->waterSaturation[i] / 100));
        reservoir->result1[i] /= 1000000;
        reservoir->result2[i] = reservoir->result1[i] / reservoir->fvf[i];
    }
}


/* Function to display the reservoir data (parameters and calculated reserves) */

void print(Reservoir *reservoir, double percentageError)
{
    int dataToModify = 0;

    puts("\nSelect the data to be modified");
    puts("1. Area");
    puts("2. Thickness");
    puts("3. Porosity");
    puts("4. Water Saturation");
    puts("5. Formation volume factor");
    puts("6. All of them");

    do
    {
        fputs("\nEnter your choice : ", stdout);
        dataToModify = read_long();

        if(dataToModify < 1 || dataToModify > 6)
            puts("Invalid input, kindly read the instructions and try again");
    }while(dataToModify < 1 || dataToModify > 6);

    puts("");

    switch(dataToModify)
    {
    case 1:
        compute_scenario_focused(reservoir, "area", percentageError);
        break;
    case 2:
        compute_scenario_focused(reservoir, "thickness", percentageError);
        break;
    case 3:
        compute_scenario_focused(reservoir, "porosity", percentageError);
        break;
    case 4:
        compute_scenario_focused(reservoir, "water saturation", percentageError);
        break;
    case 5:
        compute_scenario_focused(reservoir, "fvf", percentageError);
        break;
    case 6:
        compute_scenario_all(reservoir, percentageError);
        break;
    }

    display_header();
    display_param(reservoir, "area");
    display_param(reservoir, "thickness");
    display_param(reservoir, "porosity");
    display_param(reservoir, "water saturation");
    display_param(reservoir, "fvf");
    display_param(reservoir, "result1");
    display_param(reservoir, "result2");
    display_param(reservoir, "percentage diff");
    puts("\n");
}

