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
        column->title = (char*) malloc(sizeof(char*));
        column->title = title;
        column->size = 0;
        column->max_size = 0;
        column->column_type = type;
        column->index = NULL;
        column->valid_index = 0;
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
                char* str = (char*) value;
                int str_size = strlen(str);
                // memory allocation of the size of the string +1 to add '\0'
                col->data[col->size] = malloc((str_size +1)*sizeof(char));
                strcpy((char *) col->data[col->size], str);
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
        free((*col)->index);
    }
    free((*col)->data);
    free((*col)->title);
    *col=NULL;
}

void convert_value(COLUMN* col, unsigned long long int i, char* str, int size){
    if(i >= col->size){
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
            snprintf(str, size, "%s", ((char*)col->data[i]));
            break;
        }
        case STRUCTURE:{
            // here we have to do a switch for the different structures
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
    printf("%s\n", col->title);
    for(int i=0; i<col->size;i++){
        if(col->data[i]==NULL){
            printf("[%d] NULL\n",i);
        }
        else{
            convert_value(col, i,str, REALOC_SIZE);
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

void print_col_by_index(COLUMN* col){
    char str[REALOC_SIZE];
    int j;
    printf("%s\n", col->title);
    for(int i=0; i<col->size; i++){
        j=0;
        // to display the sorted col according to the index order
        while(col->index[i]!=j) {
            j++;
        }
        if(col->data[j]==NULL){
            printf("[%d] NULL\n",i);
        }
        else{
            convert_value(col, j,str, REALOC_SIZE);
            printf("[%d] %s\n", i, str);
        }
    }
}

void erase_index(COLUMN* col){
    for(int i=0; i<col->size; i++){
        free((unsigned long long int*)col->index[i]);
    }
    col->index = NULL;
    col->valid_index = 0;
}

int check_index(COLUMN* col){
    if(col->valid_index == 0){ //no index
        return 0;
    }
    else{
        //invalid index (index but not sorted)
        if(col->valid_index ==-1){
            return -1;
        }
        else{ // valid index
            return 1;
        }
    }
}

void update_index(COLUMN* col){
    if (col->index[col->size-1] == col->index[col->max_size]) {
        col->index = realloc(col->index, (col->max_size + REALOC_SIZE) * sizeof(void *));
    }
    col->index[col->size-1]=col->size-1;
    col->valid_index = -1;
}

int search_value_in_column(COLUMN *col, void *val){
    int pos;
    if(col == NULL || col->valid_index != 1){ // the column is not sorted
        return -1;
    }
    else{
        switch (col->column_type) {
            case(INT):{
                int m, l = 0, stop;
                int h = col->size - 1;
                do {
                    // compute the middle of the list;
                    m = (h + l) /2 ;
                    if(val == col->data[m]) {
                        stop =1 ; pos = m;
                    }
                    else {
                        if((int*)val > (int*)col->data[col->index[m]]) {
                            l = m + 1; // go to the top half
                        }
                        else{
                            h = m -1 ; // go to the lower half
                        }
                        if(l > h) {
                            stop =1 ; pos = -1;}
                    }
                }while(stop != 1);
                break;
            }
        }
        if(pos == -1){ // value not found
            return 0;
        }
        else{ // value found
            return 1;
        }
    }
}