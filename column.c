//
// Created by Aube on 29/03/2024.
//
#include <stdio.h>
#include <stdlib.h>

#include "column.h"


/*

COLUMN *create_colum(char* title){
    COLUMN *column;
    column->tab = NULL;
    column->title = title;
    return column;
}

int insert_value(COLUMN* col, int val){
    int success = 0;
    if(col->ls == col->ps){
        if(col->ps==0){
            col->tab = (int*)malloc(REALOC_SIZE * sizeof(int));
        }else{
            success = realloc(col->tab,REALOC_SIZE * sizeof(int));
        }
    }
    if(col->tab != NULL || success){
        col->tab[col->ls] = val;
        col-> ls = ls+1;
        return 1;
    }
    return 0;
}


*/




