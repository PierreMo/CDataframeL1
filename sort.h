//
// Created by Aube on 04/05/2024.
//

#ifndef CDATAFRAMEL1_SORT_H
#define CDATAFRAMEL1_SORT_H
#include "column.h"

/**
 * @brief: sort a column by insertion
 * @param1: pointer to the column to sort
 */
void sort_insertion_col(COLUMN* col);

/**
 * @brief: swap the position of to pointers in a list
 * @param1: pointer (on a value in the index list)
 * @param2: pointer (on a value in the index list)
 */
void swap(int* p1, int* p2);

/**
 * @brief: partition the column to sort the index list
 * @param1: pointer on the column to sort
 * @param2: integer at the left of the index list
 * @param3: integer at the right of the index list
 * @return: the final position of the pivot
 */
int partition(COLUMN* col, int left, int right);

/**
 * @brief: partition the column to sort the index list -> ascending order
 * @param1: pointer on the column to sort
 * @param2: integer at the left of the index list
 * @param3: integer at the right of the index list
 * @return: the final position of the pivot
 */
int partition_asc(COLUMN* col, int left, int right);

/**
 * @brief: partition the column to sort the index list -> descending order
 * @param1: pointer on the column to sort
 * @param2: integer at the left of the index list
 * @param3: integer at the right of the index list
 * @return: the final position of the pivot
 */
int partition_desc(COLUMN* col, int left, int right);

/**
 * @brief: sort index list according to the linked column by recursive call
 * @param1: pointer on the column
 * @param2: integer at the left of the index list
 * @param3: integer at the right of the index list
 */
void quickSort(COLUMN* col, int left, int right);

/**
* @brief: Sort a column according to a given order
* @param1: Pointer to the column to sort
* @param2: Sort type (ASC or DESC)
*/
void sort(COLUMN* col, int sort_dir);

#endif //CDATAFRAMEL1_SORT_H

