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


/*
    int success = 0;
    if(col->size == col->max_size){
        if(col->max_size==0){
            col->data = (int*)malloc(REALOC_SIZE * sizeof(int));
        }else{
            int* new;
            new = realloc(col->data,REALOC_SIZE * sizeof(int));
            if (new != NULL){
                free(col->data);
                col->data = new;
                success = 1;
            }
        }
    }
    if(col->data != NULL && success){
        col->data[col->size] = val;
        col-> size = col->size+1;
        return 1;
    }
    return 0;
}
*/
void delete_value(COLUMN *col, int index){
    int i=0;
    for(i=index; i<col->size;i++){
        col->data[i] = col->data[i+1];
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

void sort(COLUMN* col, int sort_dir){
    int j;
    int compare;
    char str1[REALOC_SIZE], str2[REALOC_SIZE];
    unsigned long long int tmp_index;
    col->index = (unsigned long long int*) malloc (col->size *sizeof(unsigned long long int));
    if(col->valid_index == -1){//partially sorted
        for(int i=0; i<col->size; i++) { //initialize index list
            col->index[i]=i;
        }
        if (sort_dir == ASC){
            for(int i=1; i<col->size; i++) {
                tmp_index = col->index[i];
                j = i - 1;
                //convert_value(col, j, str1, REALOC_SIZE);
                //convert_value(col, tmp_index, str1, REALOC_SIZE);
                // strcmp <0 : str1>str2, strcmp>0 : str1<str2, else equal
                //remplacer *(..) par strcmp(str1,str2)<0
                while (j >= 0 && *((int*)col->data[col->index[j]])>*((int*)col->data[tmp_index])) {
                    col->index[j + 1] = col->index[j];
                    j--;
                }
                col->index[j + 1] = tmp_index;

            }
        }
        else{
            for(int i=1; i<col->size; i++) {
                tmp_index = col->index[i];
                j = i - 1;
                //convert_value(col, i, str1, REALOC_SIZE);
                //convert_value(col, tmp_index, str1, REALOC_SIZE);
                // compare <0 : str1>str2, compare>0 : str1<str2, else equal
                //compare = strcmp(str1,str2);
                while (j >= 0 && *((int*)col->data[col->index[j]])<*((int*)col->data[tmp_index])) {
                    col->index[j + 1] = col->index[j];
                    j--;
                }
                col->index[j + 1] = tmp_index;

            }
        }
    }
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

