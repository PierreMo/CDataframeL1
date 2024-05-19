//
// Created by Aube on 29/03/2024.
//

#ifndef CDATAFRAMEL1_CDATAFRAME_H
#define CDATAFRAMEL1_CDATAFRAME_H
#include "column.h"
#include "list.h"

typedef list CDATAFRAME;

/**
 *
 * @param title
 */
void choose_title(char* title);

/**
 * @breif: Allow the user to choose a title not already in the dataframe
 * @param1 : pointer on dataframe
 * @param2 : Pointer on the title
 */
void choose_title_not_inside(CDATAFRAME* cdf, char* title);

/**
 * @brief: Allow the user to choose a title in the dataframe
 * @param1 : pointer on dataframe
 * @param2 : Pointer on the title
 */
void choose_title_inside(CDATAFRAME* cdf, char* title);

/**
 * @brief: search an input string in the dataframe
 * @param1: pointer on the dataframe
 * @param2: string
 * @return: the index of the column where the title is already used else -1
 */
int title_in_dataframe(CDATAFRAME* cdf, char* title);


/**
 * Find the column with the highest number of value
 * @param1 : pointer on the dataframe
 * @return : integer that is the nb of lines of the dataframe
 */
int longest_col(CDATAFRAME* cdf);

/**
 * @brief : ask the user the type of each column
 * @param1 : a list to save columns type
 * @param2 : number of column in the dataframe
 */
void choose_type(ENUM_TYPE* cdftype, int size);

/**
 * brief : allow the user to enter a value
 * param1: a column of the dataframe
 * param2: the value chosen by the user
 */
void input_value(ENUM_TYPE type_col, void* choice);

/**
 * brief : print titles of dataframe columns according to a chosen limit, 0 for the whole
 * @param1 : pointer on the dataframe
 * @param2: limit
 */
void display_titles(CDATAFRAME* cdf, int size);

/**
* brief : Create a dataframe
 * param1: list of types of column in the dataframe
 * param2: size of the dataframe
 * return : the dataframe
*/
CDATAFRAME *create_cdataframe(ENUM_TYPE *cdftype, int size);

/**
* @brief: Number of columns
* @param1: Point to the CDataframe
* @return: Number of columns in the CDataframe
*/
int cdataframe_size(CDATAFRAME *cdf);

/**
* @brief: Column deletion
* param1: Pointer to the CDataframe to delete
*/
void delete_cdataframe(CDATAFRAME **cdf);

/**
* @breif: Delete column by name
* @param1: Pointer to the CDataframe
* @param2: Column name
*/
void delete_column_by_name(CDATAFRAME **cdf, char *col_name);

/**
 * Hard fill the dataframe
 * @param1 : dataframe to fill
 */
void hard_fill_dataframe(CDATAFRAME* cdf, ENUM_TYPE* cdftype);

/**
 * Display the dataframe
 * @param1 : pointer on dataframe to display
 */
void display_dataframe(CDATAFRAME* cdf, int nb_lines, int nb_col);

/**
 * Display the dataframe
 * @param1 : pointer on dataframe to display
 */
void display_sorted_cdf(CDATAFRAME* cdf, int nb_lines, int nb_col);
/**
 * Allow to enter a value between 0 and val
 * @param1 : val lower bound
 * @param2 : val upper bound
 * @return : the chosen value by the user between param1 et 2
 */
int valid_input(int lower_bound, int upper_bound);

/**
 * Create a dataframe if the dataframe is NULL
 * @param1 : pointer on the dataframe to check
 * @param2 : list of columns type
 */
CDATAFRAME* is_cdataframe(CDATAFRAME* cdf, ENUM_TYPE* cdftype);

/**
 * Allow the user to fill the dataframe
 * @param1 : dataframe to fill
 */
void fill_cdataframe(CDATAFRAME* cdf);

/**
 * @brief: Add a row of values to the dataframe
 * @param1: Pointer to the dataframe
 */
void add_line_dataframe(CDATAFRAME* cdf);

/**
 * @brief: delete a column of the dataframe
 * @param1: Pointer to the dataframe
 * @param2: index of the column to delete
 * @return: 1 if the line is delete and else 0
*/
int delete_col_cdataframe(CDATAFRAME* cdf, int index);

/**
 * @brief: delete a row of values to the dataframe
 * @param1: Pointer to the dataframe
 * @param2: index at which we want delete a row
 */
void delete_line_cdataframe(CDATAFRAME* cdf, int index);

/**
 * @brief: add a column to the dataframe
 * @param1: Pointer to the dataframe
 * @param2: title of the new column
 * @return: 1 if the line is added and else 0
*/
int add_column(CDATAFRAME* cdf, char* title);

/**
 * @brief
 * @param str2
 * @param value
 */
void convert_chosen_value(ENUM_TYPE ,char* str2,void* value);

/**
* @brief: Find how many cells are either equal to a given value in the dataframe
* @param1: Pointer to the dataframe
* @param2: integer to compare other values with
* @return: return the number of value equal to @param2
*/
int equal(CDATAFRAME* cdf, ENUM_TYPE type, void* value);


/**
 * @brief: ask a column by name and rename it
 * @param1: a Cdataframe
 */
void rename_col_dataframe(CDATAFRAME* cdf);

/**
* @brief: Find how many cells are either greater than a given value in the dataframe
* @param1: Pointer to the dataframe
* @param2: type of the value to compare
* @return: return the number of value greater than @param2
*/
int greater(CDATAFRAME* cdf, ENUM_TYPE type, void* value);
/**
 * @brief : check if a there is a sorted column in the data frame
 * @param1: dataframe
 * @return : 0 if there is no sorted column, else the number of sorted column
 */
int is_sorted_column(CDATAFRAME* cdf);
/*
 * @brief: give the value of a given index and ask if you want to replace it
 * @param1: pointer on the dataframe on which we operate
 */
void access_replace(CDATAFRAME* cdf);

/**
* @brief: Find how many cells are either smaller than a given value in the dataframe
* @param1: Pointer to the dataframe
* @param2: integer to compare other values with
* @return: return the number of value smaller than @param2
*/
int smaller(CDATAFRAME* cdf, ENUM_TYPE type, void* value);


/**
* @brief: Transform a string into other types
* @param1: type of data
* @param2: string containing the desired data
* @return: return the pointer to the desired data
*/
void* input_str_to_typed(ENUM_TYPE type_col, char *choice);

/**
* @brief: Create a CDataframe from csvfile
* @param1: CSV filename
* @param2: Array of types
* @param3: Size of array in param2
*/
CDATAFRAME* load_from_csv(char *file_name);

/**
* @brief: Export into a csvfile
* @param1: Pointer to the CDataframe
* @param2: csv filename where export file, if the file exists it will be overwritten
*/
void save_into_csv(CDATAFRAME *cdf, char *file_name);

/**
* @brief: Remove \n at end if char* if it exist
* @param1: char* to modify
*/
void remove_newline(char*);




#endif //CDATAFRAMEL1_CDATAFRAME_H

