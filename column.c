//
// Created by Aube on 29/03/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "column.h"



COLUMN *create_column(ENUM_TYPE type,char* title){
    COLUMN *column = malloc (sizeof(COLUMN));
    if(column!=NULL) {
        column->data = NULL;
        column->title = title;
        column->size = 0;
        column->max_size = 0;
        column->column_type = type;
        column->index = NULL;
    }
    return column;
}

int insert_value(COLUMN *col, void *value) {
    if (value != NULL) {
        if (col->size == col->max_size) {
            col->data = realloc(col->data, (col->max_size + REALOC_SIZE) * sizeof(void *));
            if (col->data == NULL) {
                return 0;
            }
            col->max_size += REALOC_SIZE;
        }
        switch (col->column_type) {
            case INT: {
                col->data[col->size] = (int *) malloc(sizeof(int));
                *((int *) col->data[col->size]) = *((int *) value); //convert
                break;
            }
            case CHAR: {
                col->data[col->size] = (char *) malloc(sizeof(char));
                *((char *) col->data[col->size]) = *((char *) value);
                break;
            }
            case UINT: {
                col->data[col->size] = (unsigned int *) malloc(sizeof(unsigned int));
                *((unsigned int *) col->data[col->size]) = *((unsigned int *) value);
                break;
            }
            case FLOAT: {
                col->data[col->size] = (float *) malloc(sizeof(float));
                *((float *) col->data[col->size]) = *((float *) value);
                break;
            }
            case DOUBLE: {
                col->data[col->size] = (double *) malloc(sizeof(double));
                *((double *) col->data[col->size]) = *((double *) value);
                break;
            }
            case STRING: {
                col->data[col->size] = (char **) malloc(sizeof(char *));
                *((char **) col->data[col->size]) = *((char **) value);
                break;
            }
            case STRUCTURE: {
                col->data[col->size] = (void **) malloc(sizeof(void *));
                *((void **) col->data[col->size]) = *((void **) value);
                break;
            }
        }
    }
    else{
        col->data[col->size] = NULL;
    }
    col->size++;
    return 1;
}

void delete_column(COLUMN** col){
    for(int i=0; i<(*col)->size;i++){
        free((*col)->data[i]);
    }
    free((*col)->data);
    free((*col)->title);
    free((*col)->index);
    *col=NULL;
}

void convert_value(COLUMN* col, unsigned long long int i, char* str, int size){
    if(i>=col->size){
        printf("This index is out of the list\n");
        return;
    }
    switch(col->column_type){
        case UINT:{
            snprintf(str, size, "%d", *((unsigned int*)col->data[i]));
            break;
        }
        case INT:{
            snprintf(str, size, "%d", *((int*)col->data[i]));
            break;
        }
        case CHAR:{
            snprintf(str, size, "%c", *((int*)col->data[i]));
            break;
        }
        case DOUBLE:{
            snprintf(str, size, "%f", *((double*)col->data[i]));
            break;
        }
        case STRING:{
            snprintf(str, size, "%s", *((char**)col->data[i]));
            break;
        }
        case STRUCTURE:{
            //snprintf(str, size, "%s", *((void**)col->data[i]));
            break;
        }
    }
}

void delete_value(COLUMN *col, int index) {
    int i = 0;
    for (i = index; i < col->size; i++) {
        col->data[i] = col->data[i + 1];
    }
    col->size--;
}

void print_col(COLUMN* col){
    char str[REALOC_SIZE];//buffer
    for(int i=0; i<col->size;i++){
        if(col->data[i]==NULL){
            printf("[%d] NULL\n",i);
        }
        else{
            convert_value(col, i,str, col->size);
            printf("[%d] %s\n",i, str);
        }
    }
}

void swap(int* p1, int* p2){
    int temp;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

int partition(COLUMN* col, int left, int rigth){
    int i;
    switch(col->column_type){
        case(INT):{
            int pivot = *((int*)col->data[col->index[rigth]]);

            // Index of smaller element and Indicate
            // the right position of pivot found so far
            i = (left - 1);

            for (int j = left; j <= rigth; j++) {
                // If current element is smaller than the pivot
                if (*((int*)col->data[col->index[j]]) < pivot) {
                    // Increment index of smaller element
                    i++;
                    swap(&col->index[i], &col->index[j]);
                }
            }
            swap(&col->index[i + 1], &col->index[rigth]);
        }
    }

    return (i + 1);
}

void quickSort(COLUMN* col, int left, int rigth){
    switch(col->column_type){
        case(INT):{
            // when low is less than high
            if (left < rigth) {
                // pi is the partition return index of pivot
                int pi = partition(col, left, rigth);

                // Recursion Call
                // smaller element than pivot goes left and
                // higher element goes right
                quickSort(col, left, pi - 1);
                quickSort(col, pi + 1, rigth);
            }
        }
    }

}

void sort_insertion_col(COLUMN* col, int sort_dir){
    int j;
    int compare;
    char str1[REALOC_SIZE], str2[REALOC_SIZE];
    unsigned long long int tmp_index;
    if (sort_dir == ASC){
        for(int i=1; i<col->size; i++) {
            tmp_index = col->index[i];
            j = i - 1;
            switch(col->column_type){
                case(INT):{
                    while (j >= 0 && *((int*)col->data[col->index[j]])>*((int*)col->data[tmp_index])) {
                        col->index[j + 1] = col->index[j];
                        j--;
                    }
                    break;
                }
                case(FLOAT):{
                    while (j >= 0 && *((float*)col->data[col->index[j]])>*((float*)col->data[tmp_index])) {
                        col->index[j + 1] = col->index[j];
                        j--;
                    }
                    break;
                }
                case(UINT):{
                    while (j >= 0 && *((unsigned *)col->data[col->index[j]])>*((unsigned *)col->data[tmp_index])) {
                        col->index[j + 1] = col->index[j];
                        j--;
                    }
                    break;
                }
                case(DOUBLE):{
                    while (j >= 0 && *((double *)col->data[col->index[j]])>*((double *)col->data[tmp_index])) {
                        col->index[j + 1] = col->index[j];
                        j--;
                    }
                    break;
                }
                case(CHAR):{
                    convert_value(col, j, str1, REALOC_SIZE);
                    convert_value(col, tmp_index, str1, REALOC_SIZE);
                    // strcmp <0 : str1>str2, strcmp>0 : str1<str2, else equal
                    while (j >= 0 && * str1>str2) {
                        col->index[j + 1] = col->index[j];
                        j--;
                        convert_value(col, j, str1, REALOC_SIZE);
                    }
                    break;
                }
            }
            col->index[j + 1] = tmp_index;
        }
    }
    else {
        for (int i = 1; i < col->size; i++) {
            tmp_index = col->index[i];
            j = i - 1;
            switch (col->column_type) {
                case (INT): {
                    while (j >= 0 && *((int *) col->data[col->index[j]]) < *((int *) col->data[tmp_index])) {
                        col->index[j + 1] = col->index[j];
                        j--;
                    }
                }
                case (FLOAT): {
                    while (j >= 0 && *((float *) col->data[col->index[j]]) < *((float *) col->data[tmp_index])) {
                        col->index[j + 1] = col->index[j];
                        j--;
                    }
                }
                case (UINT): {
                    while (j >= 0 && *((unsigned *) col->data[col->index[j]]) < *((unsigned *) col->data[tmp_index])) {
                        col->index[j + 1] = col->index[j];
                        j--;
                    }
                }
                case (DOUBLE): {
                    while (j >= 0 && *((double *) col->data[col->index[j]]) < *((double *) col->data[tmp_index])) {
                        col->index[j + 1] = col->index[j];
                        j--;
                    }
                }
                case (CHAR): {
                    convert_value(col, j, str1, REALOC_SIZE);
                    convert_value(col, tmp_index, str1, REALOC_SIZE);
                    // strcmp <0 : str1>str2, strcmp>0 : str1<str2, else equal
                    while (j >= 0 && *str1 < str2) {
                        col->index[j + 1] = col->index[j];
                        j--;
                        convert_value(col, j, str1, REALOC_SIZE);
                    }
                }
                    col->index[j + 1] = tmp_index;
            }

        }
    }
}

void sort(COLUMN* col, int sort_dir){
    if (col->valid_index !=1){
        if(col->valid_index == -1){//partially sorted
            sort_insertion_col(col, sort_dir);
        }
        else{ //not sorted
            col->index = (unsigned long long int*) malloc (col->size *sizeof(unsigned long long int));
            for(int i=0; i<col->size; i++) { //initialize index list
                col->index[i]=i;
            }
            if(sort_dir == ASC){
                quickSort(col, 0, col->size);
            }
            else{
                quickSort(col, col->size, 0);
            }

        }
    }

    col->valid_index = 1;
}

void print_col_by_index(COLUMN* col){
    char str[REALOC_SIZE];
    int j;
    for(int i=0; i<col->size; i++){
        j=0;
        while(col->index[j]!=i) {
            j++;
        }
        if(col->data[j]==NULL){
            printf("[%d] NULL\n",i);
        }
        else{
            convert_value(col, j,str, col->size);
            printf("[%d] %s\n", i, str);
        }
    }
}

