/*
hashtables.c
-------------

By Albert Lamy Christian (19BPE1026)

Role: Definition of the functions used to manage the hashtable

Date of submission: November 19, 2021.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtables.h"
#include "functions.h"


static unsigned long hash(char logName[])
{
    unsigned long hashValue = 0;

    for(int i=0; logName[i] != '\0'; i++)
    {
        hashValue += logName[i];
        // hashValue *= logName[i];
    }

    return hashValue % TABLE_SIZE;
}


static DataItem *create_item(char logName[], double depth, double temperature, double recoveryTime)
{
    DataItem *item = malloc(sizeof(*item));

    if(item == NULL)
    {
        puts("Unable to create the item due to memory allocation failure");
        exit(EXIT_FAILURE);
    }

    // Initialize the item
    snprintf(item->logName, MAX, "%s", logName);
    item->depth = depth;
    item->temperature = temperature;
    item->recoveryTime = recoveryTime;
    item->result = 0;
    item->next = NULL;

    return item;
}


static Logs *create_list()
{
    Logs *list = malloc(sizeof(*list));

    if(list == NULL)
    {
        puts("Logs list not created due to failed memory allocation");
        exit(EXIT_FAILURE);
    }

    list->first = NULL;

    return list;
}


void logs_insert(Logs *table[], char logName[], double depth, double temperature, double recoveryTime)
{
    unsigned long position = hash(logName);
    DataItem *newItem = create_item(logName, depth, temperature, recoveryTime);

    // Insert the new item in the hashtable (via external chaining)
    if(table[position] == NULL)
    {
        // If the index is free, create a new list and insert the item at the beginning
        Logs *list = create_list();
        list->first = newItem;
        table[position] = list;
    }
    else
    {
        // Otherwise insert the item at the end of the existing list
        DataItem *current = table[position]->first;

        while(current->next != NULL)
        {
            current = current->next;
        }

        current->next = newItem;
    }
}


// Returns 1 if removal succeeded, otherwise returns 0
int logs_remove(Logs *table[], char logName[])
{
    unsigned long position = hash(logName);

    if(table[position] == NULL)
        return 0;


    DataItem *toDelete = NULL;

    if(strncmp(table[position]->first->logName, logName, MAX) == 0)
    {
        toDelete = table[position]->first;
        table[position]->first = toDelete->next;
        free(toDelete);

        return 1;
    }
    else
    {
        DataItem *current = table[position]->first;

        while(current->next != NULL)
        {
            if(strncmp(current->next->logName, logName, MAX) == 0)
            {
                DataItem *toDelete = current->next;
                current->next = current->next->next; // Same as toDelete->next
                free(toDelete);

                return 1;
            }
        }
    }

    return 0;
}


void logs_print(Logs *table[])
{
    display_header();

    for(int i=0; i<TABLE_SIZE; i++)
    {
        if(table[i] != NULL)
        {
            DataItem *current = table[i]->first;

            while(current != NULL)
            {
                printf("%s", current->logName);
                add_spaces_after(current->logName);

                split_fxn(current->depth, 7);
                split_fxn(current->temperature, 7);
                split_fxn(current->recoveryTime, 7);
                split_fxn(current->result, 7);
                puts("");

                current = current->next;
            }
        }
    }
}


void logs_free(Logs *table[])
{
    for(int i=0; i<TABLE_SIZE; i++)
    {
        if(table[i] != NULL)
        {
            // Delete all the nodes in the list
            while(table[i]->first != NULL)
            {
                DataItem *toDelete = table[i]->first;
                table[i]->first = table[i]->first->next;
                free(toDelete);
            }

            free(table[i]); // Delete the list
        }
    }
}


// Computes (t + T)/T into the hashtable
void compute_result(Logs *table[], double circulationTime)
{
    for(int i=0; i<TABLE_SIZE; i++)
    {
        if(table[i] != NULL)
        {
            DataItem *current = table[i]->first;

            while(current != NULL)
            {
                current->result = (circulationTime + current->recoveryTime) / current->recoveryTime;
                current = current->next;
            }
        }
    }
}

