//
// Created by Aube on 29/03/2024.
//

#ifndef CDATAFRAMEL1_COLUMN_H
#define CDATAFRAMEL1_COLUMN_H
#define REALOC_SIZE 256
#define ASC 0
#define DESC 1

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
    // index valid
    // 0 : no index
    // -1 : invalid index
    // 1 : valid index
    int valid_index;
    // direction de tri Ascendant ou Déscendant
    // 0 : ASC
    // 1 : DESC
    int sort_dir;
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
* @brief: Free the space allocated by a column
* @param1: Pointer to the column
*/
void delete_column(COLUMN **col);

/**
* @brief: Convert a value into a string
* @param1: Pointer to the column
* @param2: Position of the value in the data array
* @param3: The string in which the value will be written
* @param4: Maximum size of the string
*/
void convert_value(COLUMN *col, unsigned long long int i, char *str, int size);

/**
* @brief: Display the content of a column
* @param: Pointer to the column to display
*/
void print_col(COLUMN* col);

/**
* @brief: Sort a column according to a given order
* @param1: Pointer to the column to sort
* @param2: Sort type (ASC or DESC)
*/
void sort(COLUMN* col, int sort_dir);

/**
* @brief: Display the content of a sorted column
* @param1: Pointer to a column
*/
void print_col_by_index(COLUMN *col);

/**
* @brief : Free allocated memory
* @param1 : Pointer to a column
*@param2 : intege
*/
void delete_value(COLUMN *col, int index);




#endif //CDATAFRAMEL1_COLUMN_H
