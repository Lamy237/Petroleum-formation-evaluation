/*
reservoir.h
-----------

By Albert Lamy Christian (19BPE1026)

Role: Declaration of the structure 'Reservoir'
      Prototypes of the functions used to manipulate the structure

Creation: November 11, 2021.
*/

#ifndef RESERVOIR_H_INCLUDED
#define RESERVOIR_H_INCLUDED


    #define SIZE_CHAR 20

    typedef struct Reservoir Reservoir;
    struct Reservoir
    {
        // Input data
        char type[SIZE_CHAR];
        double area[3];
        double thickness[3];
        double porosity[3];
        double waterSaturation[3];
        double fvf[3]; // Formation volume factor

        // Output data
        double result1[3]; // OOIP or GOIP
        double result2[3]; // STOOIP or STGOIP

        double percentageDiff[3]; // Percentage difference in result2
    };

    void set_reservoir(Reservoir *reservoir, char type[], double area, double thickness, double porosity, double waterSaturation, double fvf);
    void print(Reservoir *reservoir, double percentageError);


#endif // RESERVOIR_H_INCLUDED
