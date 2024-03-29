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
    int ls;
    int ps; // REALOC_SIZE;
}COLUMN;


/**
* Create a column
* @param1 : Column title
* @return : Pointer to created column
*/
COLUMN *create_colum(char* title);

/**
* @brief : Add a new value to a column
* @param1 : Pointer to a column
* @param2 : The value to be added
* @return : 1 if the value is added 0 otherwise
*/
int insert_value(COLUMN* col, int value);



#endif //CDATAFRAMEL1_COLUMN_H
