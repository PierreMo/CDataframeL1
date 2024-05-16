//
// Created by Aube on 29/03/2024.
//

#ifndef CDATAFRAMEL1_COLUMN_H
#define CDATAFRAMEL1_COLUMN_H
#define REALLOC_SIZE 256
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

typedef struct{
    int month;
    int day;
    int year;
}DATE;

typedef struct{
    char name[30];
    char firstname[30];
    DATE dateBirth;
}PERSON;

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

/**
* @brief: Remove the index of a column
* @param1: Pointer to the column
*/
void erase_index(COLUMN *col);

/**
* @brief: Check if an index is correct
* @param1: Pointer to the column
* @return: 0: index not existing,
          -1: the index exists but invalid,
           1: the index is correct
*/
int check_index(COLUMN *col);

/**
* @brief: Update the index after an add of value
* @param1: Pointer to the column
*/
void update_index(COLUMN *col);

/**
* @brief: Check if a value exists in a column
* @param1: Pointer to the column
* @param2: Pointer to the value to search for
* @return: -1: column not sorted,
0: value not found
1: value found
*/
int search_value_in_column(COLUMN *col, void *val);

#endif //CDATAFRAMEL1_COLUMN_H
