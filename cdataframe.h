//
// Created by Aube on 29/03/2024.
//

#ifndef CDATAFRAMEL1_CDATAFRAME_H
#define CDATAFRAMEL1_CDATAFRAME_H
#include "column.h"

typedef struct{
    COLUMN** col;
    int ls;
    int ps;
}DATAFRAME;

typedef struct{
    int line;
    int col;
    int ls;
}COORD;

/**
 * Create a dataframe
 * @param1 : Pointer on column
 * @size of the list
 */
DATAFRAME* create_dataframe(int size);
/**
 * Allow the user to choose a title
 * @param1 : Pointer on the title
 */
void choose_title(char* title);

/**
 * Allow the user to fill the dataframe
 * @param1 : dataframe to fill
 */
void fill_dataframe(DATAFRAME* dataframe);

/**
 * Hard fill the dataframe
 * @param1 : dataframe to fill
 */
void hard_fill_dataframe(DATAFRAME* dataframe);

/**
 * Display the dataframe
 * @param1 : pointer on dataframe to display
 * @param2 : integer that give the number of lines to print
 * @param3 : integer that give the number of column to print
 */
void display_dataframe(DATAFRAME* dataframe, int nb_lines, int nb_col);

/**
 * Allow to enter a value between 0 and val
 * @param1 : val lower bound
 * @param2 : val upper bound
 * @return : the chosen value by the user between param1 et 2
 */
int valid_input(int lower_bound, int upper_bound);
/**
 * Find the column with the highest number of value
 * @param1 : pointer on the dataframe
 * @return : integer that is the nb of lines of the dataframe
 */
int longest_col(DATAFRAME* dataframe);

/**
 * Find the column with the smallest number of value
 * @param1 : pointer on the dataframe
 * @return : integer that is the nb of full lines
 */
int smallest_col(DATAFRAME* dataframe);

int input_number();
/**
 * Create a dataframe if the dataframe is NULL
 * @param1 : pointer on the dataframe to check
 */
DATAFRAME* is_dataframe(DATAFRAME* dataframe);

/**
* @brief: Find how many cells are either equal to a given value in the dataframe
* @param1: Pointer to the dataframe
* @param2: integer to compare other values with
* @return: return the number of value equal to @param2
*/
int equal(DATAFRAME* dataframe, int value);

/**
* @brief: Find how many cells are either greater than a given value in the dataframe
* @param1: Pointer to the dataframe
* @param2: integer to compare other values with
* @return: return the number of value greater than @param2
*/
int greater(DATAFRAME* dataframe, int value);
/**
* @brief: Find how many cells are either smaller than a given value in the dataframe
* @param1: Pointer to the dataframe
* @param2: integer to compare other values with
* @return: return the number of value smaller than @param2
*/
int smaller(DATAFRAME* dataframe, int value);


/**
 * @brief: Add a row of values to the dataframe
 * @param1: Pointer to the dataframe
 */
void add_line_dataframe(DATAFRAME* dataframe);

/**
 * @brief: delete a row of values to the dataframe
 * @param1: Pointer to the dataframe
 * @param2: index at which we want delete a row
 */
void delete_line_dataframe(DATAFRAME* dataframe, int index);

/**
 * @brief: add a column to the dataframe
 * @param1: Pointer to the dataframe
 * @param2: title of the new column
 * @return: 1 if the line is added and else 0
*/
int add_column(DATAFRAME* dataframe, char* title);

/**
 * @brief: delete a column to the dataframe
 * @param1: Pointer to the dataframe
 * @param2: index of the column to delete
 * @return: 1 if the line is delete and else 0
*/
int delete_col_dataframe(DATAFRAME* dataframe, int index);

/**
 * @brief: compare two strings
 * @param1: string
 * @param2: the string to compare with param1
 * @return: 1 if it's the same string else 0
 */
int is_string_equal(char* a, char* b);

/**
 * @brief: search an input string in the dataframe
 * @param1: pointer on the dataframe
 * @param2: string
 * @return: the index of the column where the title is already used else -1
 */
int title_in_dataframe(DATAFRAME* dataframe, char* title);

/**
 * @brief: display the title of all columns of the dataframe
 * @param1: pointer on the dataframe
 */
void print_col_names(DATAFRAME* dataframe);

/**
 * @brief: search all the index of a value
 * @param1: pointer on dataframe
 * @param2: integer that is the value to search
 * @param3: list of all coordinates of "value"
 * @return: the tab of coord
 */
COORD* search_value_index(DATAFRAME* dataframe, int value, COORD* tab);

/**
 * @brief:
 * @param1:
 */
void rename_col_dataframe(DATAFRAME* dataframe, int index);

/*
 * @brief: give the value of a given index and ask if you want to replace it
 * @param1: pointer on the dataframe on which we operate
 */
void access_replace(DATAFRAME* dataframe);

#endif //CDATAFRAMEL1_CDATAFRAME_H

