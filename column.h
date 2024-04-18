//
// Created by Aube on 29/03/2024.
//

#ifndef CDATAFRAMEL1_COLUMN_H
#define CDATAFRAMEL1_COLUMN_H
#define REALOC_SIZE 256

#include <stdlib.h>

enum enum_type{
    NULLVAL = 1, UINT, INT, CHAR, FLOAT, DOUBLE, STRING, STRUCTURE
};
typedef enum enum_type ENUM_TYPE;

union column_type{
    unsigned int uint_value;
    signed int int_value;
    char char_value;
    float float_value;
    double double_value;
    char* string_value;
    void* struct_value;
};
typedef union column_type COL_TYPE ;

struct column {
    char *title;
    unsigned int size; //logical size
    unsigned int max_size; //physical size
    ENUM_TYPE column_type;
    COL_TYPE** data; // array of pointers to stored data
    unsigned long long int *index; // array of integers
};
typedef struct column COLUMN;

/**
* Create a column
* @param1 : Column type
* @param2 : Column title
* @return : Pointer to created column
*/
COLUMN *create_column(ENUM_TYPE type, char* title);

/**
* @brief : Add a new value to a column
* @param1 : Pointer to a column
* @param2 : Pointer on the value to be added
* @return : 1 if the value is added 0 otherwise
*/
int insert_value(COLUMN* col, void* value);

/**
* @brief : Free allocated memory
* @param1 : Pointer to a column
*@param2 : intege
*/
void delete_value(COLUMN *col, int index);



#endif //CDATAFRAMEL1_COLUMN_H
