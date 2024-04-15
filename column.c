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

void delete_column(COLUMN **col){
    free(*col);
}

void print_col(COLUMN* col){
    printf("%s\n", col->title);
    for(int i=0; i<col->ls; i++){
        printf("[%d] %d\n", i,col->tab[i]);
    }
}

int occurrence(COLUMN* col, int value){
    int occ=0;
    for(int i=0; i<col->ls; i++){
        if(col->tab[i]==value){
            occ++;
        }
    }
    return occ;
}

int value_at_index(COLUMN* col, int index){
    return col->tab[index];
}

int sup(COLUMN* col, int value){
    int cpt=0;
    for(int i=0; i<col->ls; i++){
        if(col->tab[i]>value){
            cpt++;
        }
    }
    return cpt;
}

int inf(COLUMN* col, int value){
    int cpt=0;
    for(int i=0; i<col->ls; i++){
        if(col->tab[i]<value){
            cpt++;
        }
    }
    return cpt;
}

int equal(COLUMN* col, int value){
    int cpt=0;
    for(int i=0; i<col->ls; i++){
        if(col->tab[i]==value){
            cpt++;
        }
    }
    return cpt;
}




