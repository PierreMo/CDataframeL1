//
// Created by Aube on 29/03/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include "column.h"



COLUMN *create_column(char* title){
    COLUMN *column = malloc (sizeof(COLUMN));
    column->tab = NULL;
    column->title = title;
    column->ls = 0;
    column->ps = 0;
    return column;
}

int insert_value(COLUMN* col, int val){
    int success = 0;
    if(col->ls == col->ps){
        if(col->ps==0){
            col->tab = (int*)malloc(REALOC_SIZE * sizeof(int));
        }else{
            int* new;
            new = realloc(col->tab,REALOC_SIZE * sizeof(int));
            if (new != NULL){
                free(col->tab);
                col->tab = new;
                success = 1;
            }
        }
    }
    if(col->tab != NULL || success){
        col->tab[col->ls] = val;
        col-> ls = col->ls+1;
        return 1;
    }
    return 0;
}

void delete_value(COLUMN *col, int index){
    int i=0;
    for(i=index; i<col->ls;i++){
        col->tab[i] = col->tab[i+1];
    }
    col->ls--;
}

int value_at_index(COLUMN* col, int index){
    return col->tab[index];
}







