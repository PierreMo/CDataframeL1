//
// Created by Aube on 29/03/2024.
//

#ifndef CDATAFRAMEL1_CDATAFRAME_H
#define CDATAFRAMEL1_CDATAFRAME_H
#include "column.h"
#include "list.h"
#include "sort.h"

typedef list CDATAFRAME;

typedef struct{
    int line;
    int col;
    int ls;
}COORD;

/**
 * @brief: allow the user to entre a title
 * @param1 : pointer on the title
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
 * @brief: search an input string belong dataframe's titles
 * @param1: pointer on the dataframe
 * @param2: string
 * @return: the index of the column where the title is already used else -1
 */
int title_in_dataframe(CDATAFRAME* cdf, char* title);

/**
 * Find the column with the highest number of value
 * @param1 : pointer on the dataframe
 * @return : integer that is the maximum nb of lines of the dataframe
 */
int longest_col(CDATAFRAME* cdf);

/**
 * @brief : ask to the user the type
 * @param1 : a list to save type
 * @param2 : number of column in the dataframe
 */
void choose_type(ENUM_TYPE* cdftype, int size);

/**
 * brief : allow the user to enter a value (secured input)
 * param1: a type of value
 * param2: pointer that will save user input
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
* @brief: Compute the number of columns in the dataframe
* @param1: Point to the CDataframe
* @return: Number of columns in the CDataframe
*/
int cdataframe_size(CDATAFRAME *cdf);

/**
* @brief: Delete the dataframe
* param1: Pointer to the CDataframe to delete
*/
void delete_cdataframe(CDATAFRAME **cdf);

/**
* @breif: Delete a column by its name
* @param1: Pointer to the CDataframe
* @param2: Pointer on column's name to delete
*/
void delete_column_by_name(CDATAFRAME **cdf, char *col_name);

/**
 * @brief: Hard fill the dataframe
 * @param1 : dataframe to fill
 * @param2: pointer on the list of columns types in the dataframe
 */
void hard_fill_dataframe(CDATAFRAME* cdf, ENUM_TYPE* cdftype);

/**
 * @brief: Display the dataframe
 * @param1 : pointer on dataframe to display
 * @param2: the number of lines to display
 * @param3 : the number of columns to display
 * @note : param2:0 and parm3:0 to display all the dataframe
 */
void display_dataframe(CDATAFRAME* cdf, int nb_lines, int nb_col);

/**
 * @brief: Display the dataframe with at least one sorted column function of a chosen column
 * @param1 : pointer on dataframe to display
 * @param2: the number of lines to display
 * @param3 : the number of columns to display
 * @note : param2:0 and parm3:0 to display all the dataframe
 */
void display_sorted_cdf(CDATAFRAME* cdf, int nb_lines, int nb_col);
/**
 * @brief: Allow to enter a value between two bounds
 * @param1 : val lower bound
 * @param2 : val upper bound
 * @return : the chosen value by the user between param1 et param2
 */
int valid_input(int lower_bound, int upper_bound);

/**
 * @brief: Create a dataframe if the dataframe is NULL
 * @param1 : pointer on the dataframe to check
 * @param2 : list of columns type
 * @return: a dataframe
 */
CDATAFRAME* is_cdataframe(CDATAFRAME* cdf, ENUM_TYPE* cdftype);

/**
 *@brief: Allow the user to fill the dataframe
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
 * @brief: convert a value chosen by the user in type string
 * @param1: type of the value to convert
 * @param2: pointer on the string that will keep the convertion
 * @param3: the chosen value
 */
void convert_chosen_value(ENUM_TYPE type ,char* str2,void* value);

/**
* @brief: Find how many cells are equal to a given value in the dataframe
* @param1: Pointer to the dataframe
* @param2: integer to compare other values with
* @return: return the number of value equal to @param2
*/
int equal(COLUMN * col, ENUM_TYPE type, void* value);

/**
 * @brief: ask a column by name and rename it
 * @param1: pointer on the dataframe
 */
void rename_col_dataframe(CDATAFRAME* cdf);

/**
* @brief: Find how many cells are greater than a given value in the dataframe
* @param1: Pointer to the dataframe
* @param2: type of the value to compare
* @return: return the number of value greater than @param2
*/
int greater(CDATAFRAME* cdf, ENUM_TYPE type, void* value);

/**
 * @brief : check if a there is a sorted column in the data frame
 * @param1: pointer on the dataframe
 * @return : 0 if there is no sorted column, else the number of sorted column
 */
int is_sorted_column(CDATAFRAME* cdf);

/*
 * @brief: give the value of a given index and ask if you want to replace it
 * @param: pointer on dataframe
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

/**
 * @brief : serach a chosen value and display its position(s) on the datafram
 * @param cdf
 * @param type
 * @param value
 * @param tab
 * @return
 */
COORD* search_value_index(CDATAFRAME* cdf,ENUM_TYPE type, void* value, COORD* tab);
/**
 * @brief display the names of the different csv files
 * @param directory
 */
void list_csv_files(const char *directory);


#endif //CDATAFRAMEL1_CDATAFRAME_H

