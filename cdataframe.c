//
// Created by Aube on 29/03/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include "cdataframe.h"

void choose_title(char* title){
    printf("Choose the title of the column:");
    scanf("%s",title);
}

DATAFRAME* create_dataframe(int size){
    DATAFRAME* dataframe = (DATAFRAME*)malloc(sizeof(DATAFRAME));

    dataframe->col = (COLUMN*)malloc(size*sizeof(COLUMN));
    dataframe->ps = size;
    dataframe->ls = 0;
    for(int i=0; i<size; i++){
        char* title = (char *)malloc(size*sizeof(char));
        choose_title(title);
        dataframe->col[i] = create_column(title);
        dataframe->ls ++;
    }
    return dataframe;
}

void fill_dataframe(DATAFRAME* dataframe){
    for(int i = 0; i < dataframe->ls; i++){
        int nbr_val;
        printf("How many value do you want in the %s column", dataframe->col[i]->title);
        scanf("%d", &nbr_val);
        for(int j=0; j< nbr_val; j++){
            int value;
            printf("\nEnter the value to insert: ");
            scanf("%d", &value);
            insert_value(dataframe->col[i],value);
        }
    }
}

void hard_fill_dataframe(DATAFRAME * dataframe){
    for(int i = 0; i < dataframe->ls; i++){
        int nbr_val = 5;
        for(int j=0; j< nbr_val; j++){;
            insert_value(dataframe->col[i],j);
        }
    }
}
/*
int still_in_frame(DATAFRAME* dataframe;int i){
    int bool = 0;
    for(int j = 0; j < dataframe->ls; j++){

    }
}
*/
int longest_col(DATAFRAME* dataframe){
    int max=0;
    for(int i=0; i<dataframe->ls;i++){
        if (dataframe->col[i]->ls> max){
            max = dataframe->col[i]->ls;
        }
    }
    return max;
}
void display_dataframe(DATAFRAME* dataframe){
    for(int i = 0; i < dataframe->ls; i++) {
        printf("%s\t", dataframe->col[i]->title);
    }
    printf("\n");
    for(int i = 0; i < longest_col(dataframe); i++) {
        for(int j = 0;j < dataframe->ls; j++) {
            printf("[%d] %d\t", i, dataframe->col[j]->tab[i]);

        }
        printf("\n");
    }
        //print_col(dataframe->col[i]);
}

int valid_input(int val){
    int choice =0;
    do{
        printf("\nChoose a value : ");
        scanf("%d",&choice);
    }while ((choice > val) || (choice<1));
    return choice;
}

void is_dataframe(DATAFRAME* dataframe){
    if (dataframe ==NULL){
        printf("Let's first create a dataframe: ");
        int phys_size;
        printf("How many columns do you want in the Dataframe? (max %d)", REALOC_SIZE);
        phys_size = valid_input(REALOC_SIZE);
        dataframe = create_dataframe(phys_size);
    }
}


