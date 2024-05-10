//
// Created by Aube on 04/05/2024.
//

#include "sort.h"
#include "stdio.h"
#include <string.h>

void swap(int* p1, int* p2){
    int temp;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

int partition(COLUMN* col, int left, int right){
    int i;
    if (col->sort_dir == ASC){ // ascending order
        switch(col->column_type) {
            case (UINT): {
                unsigned int pivot = *((unsigned int*) col->data[col->index[right]]);
                i = (left - 1);
                for (int j = left; j <= right-1; j++) {
                    if (*((unsigned int *) col->data[col->index[j]]) < pivot){
                        i++;
                        swap(&col->index[i], &col->index[j]);
                    }
                }
                swap(&col->index[i + 1], &col->index[right]);
                break;
            }
            case (INT): {
                int pivot = *((int *) col->data[col->index[right]]);
                i = (left - 1);
                for (int j = left; j <= right-1; j++) {
                    if (*((int *) col->data[col->index[j]]) < pivot){
                        i++;
                        swap((int *) &col->index[i], (int *) &col->index[j]);
                    }
                }
                swap((int *) &col->index[i + 1], (int *) &col->index[right]);
                break;
            }
            case (FLOAT): {
                float pivot = *((float *) col->data[col->index[right]]);
                i = (left - 1);
                for (int j = left; j <= right-1; j++) {
                    if (*((float *) col->data[col->index[j]]) < pivot){
                        i++;
                        swap((int *) &col->index[i], (int *) &col->index[j]);
                    }
                }
                swap((int *) &col->index[i + 1], (int *) &col->index[right]);
                break;
            }
            case (DOUBLE): {
                double pivot = *((double *) col->data[col->index[right]]);
                i = (left - 1);
                for (int j = left; j <= right-1; j++) {
                    if (*((double *) col->data[col->index[j]]) < pivot){
                        i++;
                        swap((int *) &col->index[i], (int *) &col->index[j]);
                    }
                }
                swap((int *) &col->index[i + 1], (int *) &col->index[right]);
                break;
            }
            case (CHAR): {
                char pivot = *((char *) col->data[col->index[right]]);
                i = (left - 1);
                for (int j = left; j <= right-1; j++) {
                    if (*((char *) col->data[col->index[j]]) < pivot){
                        i++;
                        swap((int *) &col->index[i], (int *) &col->index[j]);
                    }
                }
                swap((int *) &col->index[i + 1], (int *) &col->index[right]);
                break;
            }
            case (STRING): {
                char pivot[REALOC_SIZE], str[REALOC_SIZE];
                convert_value(col,col->index[right], pivot, REALOC_SIZE);
                i = (left - 1);
                for (int j = left; j <= right-1; j++) {
                    convert_value(col,col->index[j], str, REALOC_SIZE);
                    // strcmp > 0 => str < pivot
                    if (strcmp(str,pivot)>0){
                        i++;
                        swap(&col->index[i], &col->index[j]);
                    }
                }
                swap(&col->index[i + 1], &col->index[right]);
                break;
            }
        }
    }
    else{// decreasing order
        switch(col->column_type) {
            case (INT): {
                int pivot = *((int *) col->data[col->index[right]]);
                i = (left - 1);
                for (int j = left; j <= right; j++) {
                    if (*((int *) col->data[col->index[j]]) > pivot) {
                        i++;
                        swap(&col->index[i], &col->index[j]);
                    }
                }
                swap(&col->index[i + 1], &col->index[right]);
                break;
            }
            case (FLOAT): {
                float pivot = *((float *) col->data[col->index[right]]);
                i = (left - 1);
                for (int j = left; j <= right; j++) {
                    if (*((float *) col->data[col->index[j]]) > pivot) {
                        i++;
                        swap(&col->index[i], &col->index[j]);
                    }
                }
                swap(&col->index[i + 1], &col->index[right]);
                break;
            }
            case (UINT): {
                unsigned int pivot = *((unsigned int*) col->data[col->index[right]]);
                i = (left - 1);
                for (int j = left; j <= right; j++) {
                    if (*((unsigned int*) col->data[col->index[j]]) > pivot) {
                        i++;
                        swap(&col->index[i], &col->index[j]);
                    }
                }
                swap(&col->index[i + 1], &col->index[right]);
                break;
            }
            case (DOUBLE): {
                double pivot = *((double *) col->data[col->index[right]]);
                i = (left - 1);
                for (int j = left; j <= right; j++) {
                    if (*((double *) col->data[col->index[j]]) > pivot) {
                        i++;
                        swap(&col->index[i], &col->index[j]);
                    }
                }
                swap(&col->index[i + 1], &col->index[right]);
                break;
            }
            case (CHAR): {
                char pivot = *((char *) col->data[col->index[right]]);
                i = (left - 1);
                for (int j = left; j <= right; j++) {
                    if (*((char *) col->data[col->index[j]]) > pivot){
                        i++;
                        swap(&col->index[i], &col->index[j]);
                    }
                }
                swap(&col->index[i + 1], &col->index[right]);
                break;
            }
            case (STRING): {
                char pivot[REALOC_SIZE], str[REALOC_SIZE];
                convert_value(col,col->index[right], pivot, REALOC_SIZE);
                i = (left - 1);
                for (int j = left; j <= right; j++) {
                    convert_value(col,col->index[j], str, REALOC_SIZE);
                    // strcmp < 0 => str > pivot
                    if (strcmp(str,pivot)<0){
                        i++;
                        swap(&col->index[i], &col->index[j]);
                    }
                }
                swap(&col->index[i + 1], &col->index[right]);
                break;
            }
        }
    }
    return (i + 1);
}


void quickSort(COLUMN* col, int left, int right){
    if (left < right) {
        int pi = partition(col, left, right);
        // recursion recall
        quickSort(col, left, pi - 1);
        quickSort(col, pi + 1, right);
    }
}

void sort_insertion_col(COLUMN* col){
    int j;
    unsigned long long int tmp_index;
    if (col->sort_dir == ASC){
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
                    while (j >= 0 && *((char **)col->data[col->index[j]])>*((char **)col->data[tmp_index])){
                        col->index[j + 1] = col->index[j];
                        j--;
                    }
                    break;
                }
                case(STRING):{
                    char str1[REALOC_SIZE], str2[REALOC_SIZE];
                    convert_value(col, col->index[j], str1, REALOC_SIZE);
                    convert_value(col, col->index[tmp_index], str2, REALOC_SIZE);
                    // strcmp <0 : str1>str2, strcmp>0 : str1<str2, else equal
                    while (j >= 0 && strcmp(str1,str2)<0) {
                        col->index[j + 1] = col->index[j];
                        j--;
                        if (j>=0){
                            convert_value(col, col->index[j], str1, REALOC_SIZE);
                        }
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
                    break;
                }
                case (FLOAT): {
                    while (j >= 0 && *((float *) col->data[col->index[j]]) < *((float *) col->data[tmp_index])) {
                        col->index[j + 1] = col->index[j];
                        j--;
                    }
                    break;
                }
                case (UINT): {
                    while (j >= 0 && *((unsigned *) col->data[col->index[j]]) < *((unsigned *) col->data[tmp_index])) {
                        col->index[j + 1] = col->index[j];
                        j--;
                    }
                    break;
                }
                case (DOUBLE): {
                    while (j >= 0 && *((double *) col->data[col->index[j]]) < *((double *) col->data[tmp_index])) {
                        col->index[j + 1] = col->index[j];
                        j--;
                    }
                    break;
                }
                case(CHAR):{
                    while (j >= 0 && *((char **)col->data[col->index[j]]) < *((char **)col->data[tmp_index])){
                        col->index[j + 1] = col->index[j];
                        j--;
                    }
                    break;
                }
                case (STRING): {
                    char str1[REALOC_SIZE], str2[REALOC_SIZE];
                    convert_value(col, col->index[j], str1, REALOC_SIZE);
                    convert_value(col, col->index[tmp_index], str2, REALOC_SIZE);
                    // strcmp <0 : str1>str2, strcmp>0 : str1<str2, else equal
                    while (j >= 0 && strcmp(str1, str2) > 0) {
                        col->index[j + 1] = col->index[j];
                        j--;
                        if (j>=0){
                            convert_value(col, col->index[j], str1, REALOC_SIZE);
                        }
                    }
                    break;
                }
                case(STRUCTURE):{
                    break;
                }
            }
            col->index[j + 1] = tmp_index;
        }
    }
}

void sort(COLUMN* col, int sort_dir){
    switch(check_index(col)){
        case(0):{ //not sorted
            //initialize index list
            col->index = (unsigned long long int*) malloc (col->max_size *sizeof(unsigned long long int));
            for(int i=0; i<col->size; i++) {
                col->index[i]=i;
            }
            col->sort_dir = sort_dir;
            quickSort(col, 0, col->size - 1);
            break;
        }
        case(-1):{ // almost sorted
            col->sort_dir = sort_dir;
            sort_insertion_col(col);
            break;
        }
        case(1):{ // sorted
            printf("The column %s is already sorted.", col->title);
            break;
        }
    }
    col->valid_index = 1;
}