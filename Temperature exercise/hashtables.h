/*
hashtables.c
-------------

By Albert Lamy Christian (19BPE1026)

Role: Definition of the preprocessor constants used in the program
      Definition of the structures used to create the hashtable
      Definition of the functions used to manage the hashtable

Date of submission: November 19, 2021.
*/

#ifndef HASHTABLES_H_INCLUDED
#define HASHTABLES_H_INCLUDED


    #define TABLE_SIZE 10
    #define MAX 20

    typedef struct DataItem DataItem;
    struct DataItem
    {
        // Input data
        char logName[MAX];
        double depth;
        double temperature;
        double recoveryTime; // T

        // Output data
        // result = (t + T) / T, where t = mud circulation time
        double result;

        DataItem *next;
    };

    typedef struct Logs Logs;
    struct Logs
    {
        DataItem *first;
    };

    void logs_insert(Logs *table[], char logName[], double depth, double temperature, double recoveryTime);
    void logs_print(Logs *table[]);
    void logs_free(Logs *table[]);
    int logs_remove(Logs *table[], char logName[]);
    void compute_result(Logs *table[], double circulationTime);


#endif // HASHTABLES_H_INCLUDED
