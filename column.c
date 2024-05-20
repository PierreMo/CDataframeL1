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
            COL_TYPE** new =realloc(col->data, (col->max_size + REALLOC_SIZE) * sizeof(void *));
            if (new == NULL) {
                return 0;
            }
            col->data = new;
            col->max_size += REALLOC_SIZE;
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
            case TYPE_DATE: {
                col->data[col->size] = (DATE*) malloc(sizeof(DATE *));
                *((DATE *) col->data[col->size]) = *((DATE*) value);
                break;
            }
        }
    }
    else{
        col->data[col->size] = NULL;
    }
    col->size++;
    if(col->valid_index == 1){
        col->valid_index = -1;
    }
    return 1;
}

void delete_column(COLUMN** col){
    for(int i=0; i<(*col)->size;i++){
        free((*col)->data[i]);
    }
    if ((*col)->index != NULL){
        free((*col)->index);
    }
    free((*col)->data);
    free((*col)->title);
    free(*col);
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
            snprintf(str, size, "%c", *((char*)col->data[i]));
            break;
        }
        case FLOAT:{
            snprintf(str, size, "%.2f", *( (float*)col->data[i]) );
            break;
        }
        case DOUBLE:{
            snprintf(str, size, "%.2lf", *((double*)col->data[i]));
            break;
        }
        case STRING:{
            snprintf(str, size, "%s", ((char*)col->data[i]));
            break;
        }
        case TYPE_DATE:{
            char date[size], buffer[size];

            snprintf(date, size, "%d", ((DATE*)col->data[i])->month);

            strcat(date, "/");
            snprintf(buffer, size, "%d", ((DATE*)col->data[i])->day);
            strcat(date, buffer);
            strcat(date, "/");
            snprintf(buffer, size, "%d", ((DATE*)col->data[i])->year);
            strcat(date, buffer);

            snprintf(str, size, "%s", date);
            break;
        }
    }
}

void delete_value(COLUMN *col, int index) {
    if (col->size!=0){
        void *temp= col->data[index];
        for (int i = index; i < col->size; i++) {
            col->data[i] = col->data[i + 1];
        }
        free(temp);
        col->size--;
    }
}

void change_value(COLUMN *col, void *value, int index) {
    if (value != NULL) {
        switch (col->column_type) {
            case UINT: {
                *((unsigned int *) col->data[index]) = *((unsigned int *) value);
                break;
            }
            case INT: {
                *( (int*) col->data[index]) = (int)*((int*) value); //convert
                break;
            }
            case CHAR: {
                *((char *) col->data[index]) = *((char *) value);
                break;
            }
            case FLOAT: {
                *((float *) col->data[index]) = *((float *) value);
                break;
            }
            case DOUBLE: {
                *((double *) col->data[index]) = *((double *) value);
                break;
            }
            case STRING: {
                char* str = (char*) value;
                int str_size = strlen(str);
                // memory allocation of the size of the string +1 to add '\0'
                col->data[col->size] = malloc((str_size +1)*sizeof(char));
                strcpy((char *) col->data[index], str);
                break;
            }
            case TYPE_DATE: {
                *((DATE *) col->data[index]) = *((DATE *) value);
                break;
            }
        }
    }
}

void print_col(COLUMN* col){
    char str[REALLOC_SIZE];//buffer
    printf("%s\n", col->title);
    for(int i=0; i<col->size;i++){
        if(col->data[i]==NULL){
            printf("[%d] NULL\n",i);
        }
        else{
            convert_value(col, i,str, REALLOC_SIZE);
            printf("[%d] %s\n",i, str);
        }
    }
}


void print_col_by_index(COLUMN* col){
    char str[REALLOC_SIZE];
    int j;
    printf("%s\n", col->title);
    for(int i=0; i<col->size; i++){
        if(col->data[col->index[i]]==NULL){
            printf("[%d] NULL\n",i);
        }
        else{
            convert_value(col, col->index[i],str, REALLOC_SIZE);
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
        col->index = realloc(col->index, (col->max_size + REALLOC_SIZE) * sizeof(void *));
    }
    col->index[col->size-1]=col->size-1;
    col->valid_index = -1;
}

int search_value_in_column(COLUMN *col, void *val){
    if(col->valid_index != 1){ // the column is not sorted
        return -1;
    }
    else{
        int in = 0;
        int m, l = 0, stop;
        int h = col->size - 1;
        switch (col->column_type) {
            case(INT):{
                do {
                    // compute the middle of the list;
                    m = (h + l) /2 ;
                    if(*(int*)val == *(int*)col->data[col->index[m]]) {
                        stop = 1 ;
                        in = 1;
                    }
                    else {
                        if(*(int*)val > *(int*)col->data[col->index[m]]) {
                            l = m + 1; // go to the top half
                        }
                        else{
                            h = m -1 ; // go to the lower half
                        }
                        if(l > h) {
                            stop = 1 ;
                        }
                    }
                }while(stop != 1);
                break;
            }
            case(FLOAT):{
                do {
                    // compute the middle of the list;
                    m = (h + l) /2 ;
                    if(*(float*)val == *(float*)col->data[col->index[m]]) {
                        stop = 1 ;
                        in = 1;
                    }
                    else {
                        if(*(float*)val > *(float*)col->data[col->index[m]]) {
                            l = m + 1; // go to the top half
                        }
                        else{
                            h = m -1 ; // go to the lower half
                        }
                        if(l > h) {
                            stop = 1 ;
                        }
                    }
                }while(stop != 1);
                break;
            }
            case(DOUBLE):{
                do {
                    // compute the middle of the list;
                    m = (h + l) /2 ;
                    if(*(double*)val == *(double*)col->data[col->index[m]]) {
                        stop = 1 ;
                        in = 1;
                    }
                    else {
                        if(*(double*)val > *(double*)col->data[col->index[m]]) {
                            l = m + 1; // go to the top half
                        }
                        else{
                            h = m -1 ; // go to the lower half
                        }
                        if(l > h) {
                            stop = 1 ;
                        }
                    }
                }while(stop != 1);
                break;
            }
            case(UINT):{
                do {
                    // compute the middle of the list;
                    m = (h + l) /2 ;
                    if(*(unsigned int*)val == *(unsigned int*)col->data[col->index[m]]) {
                        stop = 1 ;
                        in = 1;
                    }
                    else {
                        if(*(unsigned int*)val > *(unsigned int*)col->data[col->index[m]]) {
                            l = m + 1; // go to the top half
                        }
                        else{
                            h = m -1 ; // go to the lower half
                        }
                        if(l > h) {
                            stop = 1 ;
                        }
                    }
                }while(stop != 1);
                break;
            }
            case(CHAR):{
                do {
                    // compute the middle of the list;
                    m = (h + l) /2 ;
                    if(*(char **)val == *(char**)col->data[col->index[m]]) {
                        stop = 1 ;
                        in = 1;
                    }
                    else {
                        if(*(char **)val > *(char **)col->data[col->index[m]]) {
                            l = m + 1; // go to the top half
                        }
                        else{
                            h = m -1 ; // go to the lower half
                        }
                        if(l > h) {
                            stop = 1 ;
                        }
                    }
                }while(stop != 1);
                break;
            }
            case(STRING):{
                char str[REALLOC_SIZE];
                do {
                    // compute the middle of the list;
                    m = (h + l) /2 ;
                    convert_value(col, col->index[m], str, REALLOC_SIZE);
                    // strcmp = 0 => val = str
                    if(strcmp(val, str) == 0) {
                        stop = 1 ;
                        in = 1;
                    }
                    else {
                        // strcmp > 0 => val > str
                        if(strcmp(val, str)>0) {
                            l = m + 1; // go to the top half
                        }
                        else{
                            h = m -1 ; // go to the lower half
                        }
                        if(l > h) {
                            stop = 1 ;
                        }
                    }
                }while(stop != 1);
                break;
            }
            case(TYPE_DATE):{
                break;
            }
        }

        return in;
    }
}


int check_type(COLUMN* col){
    ENUM_TYPE type = col->column_type;
    int i = 2;
    while(i<8 && type!=i){
        i++;
    }
    return i-1;
}

int max_str(COLUMN* col){
    char str[REALLOC_SIZE];
    int max = 0;
    for(int i = 0; i<col->size; i++){
        convert_value(col, i, str, REALLOC_SIZE);
        if(max<strlen(str)){
            max = strlen(str);
        }
    }
    return max;
}

int isLeapYear(int year) {
    if (year % 400 == 0)
        return 1;
    if (year % 100 == 0)
        return 0;
    if (year % 4 == 0)
        return 1;
    return 0;
}


int compareDates(DATE* d1, DATE* d2){
    if (d1->year == d2->year && d1->month == d2->month && d1->day == d2->day){
        return 0;
    }
    else{
        if (d1->year > d2->year){
            return 1;
        }
        else{
            if (d1->year < d2->year){
                return -1;
            }
            else{
                if (d1->year == d2->year){
                    if (d1->month == d2->month){
                        if (d1->day > d2-> day){
                            return 1;
                        }
                        else{
                            return -1;
                        }
                    }
                    else{
                        if(d1->month > d2->month){
                            return 1;
                        }
                        else{
                            return -1;
                        }
                    }

                }
            }
        }

    }
}