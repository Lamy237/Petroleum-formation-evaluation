/*
functions.c
-----------

By Albert Lamy Christian (19BPE1026)

Role: Definition of other functions used in the program

Creation: November 11, 2021.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"


double meters_to_feet(double number)
{
    return number * 3.281;
}


void split_fxn(double number, int maxDigits)
{
    char fmt[10] = {0};
    int integral = 0, fractional = 0;

    int integralPart = number;  // Get (truncate) the integral part of the number

    // In case the integral part is negative, we decrement maxDigits, as the minus sign will take one space
    if(integralPart < 0)
        maxDigits--;

    // In case the integral part is equal to zero (0), the loop below won't count the digit
    if(integralPart == 0)
        integral = 1;

    // Count the number of digits of the integral part
    while(integralPart != 0)
    {
        integralPart /= 10;
        integral++;
    }

    fractional = maxDigits - integral; // Set the number of digits to be displayed from the decimal part

    // Set the format of the number to be displayed
    // If number = 123.45 and maxDigits = 7, we get %3.4lf So 123.4500 is displayed
    snprintf(fmt, 10, "%%%d.%dlf\t", maxDigits, fractional);
    printf(fmt, number);
}


void add_spaces_after(char string[])
{
    size_t len = strlen(string);

    printf("%s", string);

    for(size_t i=len; i<MAX-1; i++)
    {
        fputs(" ", stdout);
    }
}


/* These functions were created to avoid using scanf */

void free_buffer()
{
    int c = 0;

    while(c != '\n' && c != EOF)
    {
        c = getchar();
    }
}


int read_string(char myString[])
{
    char *position = NULL;

    if(fgets(myString, MAX, stdin) != NULL)
    {
        position = strchr(myString, '\n');

        if(position != NULL)
        {
            *position = '\0';
        }
        else
        {
            free_buffer();
        }

        return 1;
    }
    else
    {
        free_buffer();
        return 0;
    }
}


long read_long()
{
    char numberText[MAX] = {0};

    if(read_string(numberText))
    {
        return strtol(numberText, NULL, 10);
    }
    else
    {
        return 0;
    }
}

