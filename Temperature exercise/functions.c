/*
functions.c
------------

By Albert Lamy Christian (19BPE1026)

Role: # Definition of the functions used for various computations

      - fahrenheit_to_celsius() : Converts the temperature from °F to °C
      - celsius_to_fahrenheit() : Converts the temperature from °C to °F


      # Definition of the functions used to embellish the output

      - split_fxn() : Displays a fixed number of digits from a decimal number
      - add_spaces_after() : Adds a defined amount of whitespace after a string
      - display_header() : Displays the header before printing the hashtable

Date of submission: November 19, 2021.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"
#include "hashtables.h" // for the preprocessor MAX


double fahrenheit_to_celsius(double temperature)
{
    temperature = (temperature - 32) * 5/9;
    return temperature;
}


double celsius_to_fahrenheit(double temperature)
{
    temperature = (temperature * 9/5) + 32;
    return temperature;
}


void split_fxn(double number, int maxDigits)
{
    char fmt[10] = {0};
    int integral = 0, fractional = 0;

    int integralPart = number;  // Get (truncate) the integral part of the number

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

    for(int i=len; i<MAX-1; i++)
    {
        fputs(" ", stdout);
    }
}


void display_header()
{
    fputs("\nProcess", stdout);
    add_spaces_after("Process");

    puts("Depth_(m)\tTemp_(deg F)\tT_(hours)\t(t+T)/T");
    puts("-------------------------------------------------------------------------");
}

