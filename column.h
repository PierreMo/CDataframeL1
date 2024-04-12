//
// Created by Aube on 29/03/2024.
//

#ifndef CDATAFRAMEL1_COLUMN_H
#define CDATAFRAMEL1_COLUMN_H
#define REALOC_SIZE 256

#include <stdlib.h>

typedef struct{
    char* title;
    int* tab; //= (int*)malloc(REALOC_SIZE * sizeof(int));
    int ls;//logical size
    int ps; //physical size
    // REALOC_SIZE;
}COLUMN;


/**
* Create a column
* @param1 : Column title
* @return : Pointer to created column
*/
COLUMN *create_column(char* title);

/**
* @brief : Add a new value to a column
* @param1 : Pointer to a column
* @param2 : The value to be added
* @return : 1 if the value is added 0 otherwise
*/
int insert_value(COLUMN* col, int value);

/**
* @brief : Free allocated memory
* @param1 : Pointer to a column
*/
void delete_column(COLUMN **col);

/**
* @brief: Print a column content
* @param1: Pointer to a column
*/
void print_col(COLUMN* col);

/**
* @brief: Count the occurrence of a value
* @param1: Pointer to a column
* @param2: integer
* @return: return the occurrence
*/
int occurrence(COLUMN* col, int value);

/**
* @brief: Find the value on a given index
* @param1: Pointer to a column
* @param2: integer
* @return: return the value
*/
int value_at_index(COLUMN* col, int index);

/**
* @brief: Find how many value are higher than a given one
* @param1: Pointer to a column
* @param2: integer
* @return: return the number of higher value
*/
int sup(COLUMN* col, int value);

/**
* @brief: Find how many value are smaller than a given one
* @param1: Pointer to a column
* @param2: integer
* @return: return the number of smaller value
*/
int inf(COLUMN* col, int value);

/**
* @brief: Find how many value are equal to a given one
* @param1: Pointer to a column
* @param2: integer
* @return: return the number of values equal to param2
*/
int equal(COLUMN* col, int value);

#endif //CDATAFRAMEL1_COLUMN_H
