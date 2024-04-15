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
 * @param1 : val upper bound
 */
int valid_input(int val);
/**
 * Find the column with the highest number of value
 * @param1 : pointer on the dataframe
 * @return : integer that is the nb of lines of the dataframe
 */
int longest_col(DATAFRAME* dataframe);

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




#endif //CDATAFRAMEL1_CDATAFRAME_H

