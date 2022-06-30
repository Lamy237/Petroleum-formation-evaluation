/*
functions.h
-----------

By Albert Lamy Christian (19BPE1026)

Role: Prototypes of other functions used in the program

Creation: November 11, 2021.
*/

#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED


    #define MAX 60

    void split_fxn(double number, int maxDigits);
    void add_spaces_after(char string[]);
    double meters_to_feet(double number);

    void free_buffer();
    int read_string(char myString[]);
    long read_long();


#endif // FUNCTIONS_H_INCLUDED
