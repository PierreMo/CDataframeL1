//
// Created by Aube on 29/03/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include "cdataframe.h"

void choose_title_not_inside(DATAFRAME* dataframe, char* title){
    do{
    printf("Choose the title of the column:");
    scanf("%s",title);
        if (title_in_dataframe(dataframe, title)!=-1){
            printf("This title is already in the dataframe!\n");
        }
    }while(title_in_dataframe(dataframe, title)!=-1);
}

void choose_title_inside(DATAFRAME* dataframe, char* title){
    do{
        printf("Choose the title of the column:");
        scanf("%s",title);
        if (title_in_dataframe(dataframe, title)==-1){
            printf("This title is not in the dataframe!\n");
        }
    }while(title_in_dataframe(dataframe, title)==-1);
}

DATAFRAME* create_dataframe(int size){
    DATAFRAME* dataframe = (DATAFRAME*)malloc(sizeof(DATAFRAME));
    dataframe->col = (COLUMN*)malloc(size*sizeof(COLUMN));
    dataframe->ps = size;
    dataframe->ls = 0;
    for(int i=0; i<size; i++){
        char* title = (char *)malloc(100*sizeof(char));
        choose_title_not_inside(dataframe, title);
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

int smallest_col(DATAFRAME* dataframe){
    int min = dataframe->col[0]->ls;
    for(int i=1; i<dataframe->ls;i++){
        if (dataframe->col[i]->ls <min){
            min = dataframe->col[i]->ls;
        }
    }
    return min;
}

void display_dataframe(DATAFRAME* dataframe, int nb_lines, int nb_col){
    // if the user want to display all the dataframe
    if (nb_lines==0){
        //the number of lines to print is the logical size of longest column
        nb_lines = longest_col(dataframe);
    }
    if (nb_col==0){
        nb_col = dataframe->ls;
    }
    //display titles
    for(int i = 0; i < nb_col; i++) {
        printf("%s\t", dataframe->col[i]->title);
    }
    printf("\n");
    //display values with index
    for(int i = 0; i < nb_lines; i++) {
        for(int j = 0;j < nb_col; j++) {
            if(i < dataframe->col[j]->ls){
                printf("[%d] %d\t", i, dataframe->col[j]->tab[i]);
            }else{
                printf("[%d] ∅\t", i);
            }
        }
        printf("\n");
    }
    printf("\n");
}

int valid_input(int lower_bound, int upper_bound){
    int choice=0, type;
    do{
        printf("\nChoose a value between %d and %d:",lower_bound, upper_bound);
        type = scanf("%d",&choice);//if the type is int type=1
        if (type != 1 || choice < lower_bound || choice > upper_bound) {
            printf("Invalid input.");
            while (getchar() != '\n'); // to clear out the input buffer
        }
    }while (type!=1||(choice > upper_bound) || (choice<lower_bound));
    return choice;
}

DATAFRAME* is_dataframe(DATAFRAME* dataframe){
    if (dataframe ==NULL){
        printf("Let's first create a dataframe: ");
        int phys_size;
        printf("How many columns do you want in the Dataframe? (max %d)", REALOC_SIZE);
        phys_size = valid_input(1,REALOC_SIZE);
        dataframe = create_dataframe(phys_size);
    }
    return dataframe;
}

int input_number(){
    int choice=0, type;
    do{
        printf("\nChoose a value:");
        type = scanf("%d",&choice);//if the type is int type=1
        if (type != 1) {
            printf("Invalid input.");
            while (getchar() != '\n'); // to clear out the input buffer
        }
    }while (type!=1);
    return choice;

}
int equal(DATAFRAME* dataframe, int value){
    int cpt=0;
    for(int i =0; i<dataframe->ls; i++){
        for(int j=0; j<dataframe->col[i]->ls; j++){
            if(dataframe->col[i]->tab[j]==value){
                cpt++;
            }
        }
    }
    return cpt;
}

int greater(DATAFRAME* dataframe, int value){
    int cpt=0;
    for(int i =0; i<dataframe->ls; i++){
        for(int j=0; j<dataframe->col[i]->ls; j++){
            if(dataframe->col[i]->tab[j]>value){
                cpt++;
            }
        }
    }
    return cpt;
}

int smaller(DATAFRAME* dataframe, int value){
    int cpt=0;
    for(int i =0; i<dataframe->ls; i++){
        for(int j=0; j<dataframe->col[i]->ls; j++){
            if(dataframe->col[i]->tab[j]<value){
                cpt++;
            }
        }
    }
    return cpt;
}

void add_line_dataframe(DATAFRAME* dataframe){
    for(int i= 0;i < dataframe->ls;i++){
        printf("Insert the new value for %s", dataframe->col[i]->title);
        insert_value(dataframe->col[i], input_number());
    }
}

void delete_line_dataframe(DATAFRAME* dataframe, int index){
    for(int i =0; i<dataframe->ls; i++){
        delete_value(dataframe->col[i], index);
    }
}

int add_column(DATAFRAME* dataframe, char* title){
    int success = 0;
    if(dataframe->ls == dataframe->ps){
        COLUMN** new;
        // adding a new block of size REALOC_SIZE to the already existing blocks
        new = realloc(dataframe->col, (dataframe->ps/REALOC_SIZE +1)*REALOC_SIZE * sizeof(COLUMN*));
        if (new != NULL){
            free(dataframe->col);
            dataframe->col = new;
            success = 1;
            dataframe->ps = (dataframe->ps/REALOC_SIZE +1)*REALOC_SIZE;
        }
    }
    if(dataframe->col != NULL || success){
        int nb_val =0;
        dataframe->col[dataframe->ls] = create_column(title);
        printf("How many value do you want in your column?");
        nb_val= valid_input(1,REALOC_SIZE);
        for(int i=0; i<nb_val; i++){
            insert_value(dataframe->col[dataframe->ls],input_number());
        }
        dataframe-> ls++;
        return 1;
    }
    return 0;
}

int is_string_equal(char* a, char* b){
    int i=0;
    while(a[i]!='\0' && b[i]!='\0' && a[i]==b[i]){
        i++;
    }
    if(a[i]== '\0' && b[i]=='\0'){
        return 1;
    }else{
        return 0;
    }
}

int title_in_dataframe(DATAFRAME* dataframe, char* title) {
    for (int i = 0; i < dataframe->ls; i++) {
        if (is_string_equal(title, dataframe->col[i]->title)) {
            return i;
        }
    }
    return -1; //not in dataframe
}

int delete_col_dataframe(DATAFRAME* dataframe, int index){
    free(dataframe->col[index]->title);
    free(dataframe->col[index]->tab);
    free(dataframe->col[index]);
    for(int j=index; j<(dataframe->ls)-1; j++){
        dataframe->col[j] = dataframe->col[j+1];
    }
    dataframe->ls--;
    return 0;
}

void print_col_names(DATAFRAME* dataframe){
    for(int i=0; i<dataframe->ls; i++){
        printf("%s\t", dataframe->col[i]->title);
    }
    printf("\n");
}

COORD* search_value_index(DATAFRAME* dataframe,int value, COORD* tab){
    for(int i =0; i<dataframe->ls; i++){
        for(int j=0; j<dataframe->col[i]->ls; j++){
            if(dataframe->col[i]->tab[j]==value){
                if(tab==NULL){
                    tab = (COORD*)malloc(REALOC_SIZE*sizeof(COORD));
                    tab->ls = 0;
                }
                tab[tab->ls].col = i;
                tab[tab->ls].line = j;
                tab->ls++;
            }
        }
    }
    return tab;
}

void rename_col_dataframe(DATAFRAME* dataframe, int index){
    char* title=(char*)malloc(100*sizeof(char));
    choose_title_not_inside(dataframe, title);
    free(dataframe->col[index]->title);
    dataframe->col[index]->title = title;
}

void access_replace(DATAFRAME* dataframe){
    display_dataframe(dataframe,0,0);
    int column, row;
    printf("Enter the index of the column:");
    column = valid_input(0,dataframe->ls-1);
    printf("Enter the index of the row:");
    row = valid_input(0,dataframe->col[column]->ls-1);
    printf("The value at this position is %d. ",dataframe->col[column]->tab[row]);
    int answer;
    do {
        printf("Do you want to replace it? 1 for yes 0 for no: ");
        scanf("%d", &answer);
        if(answer==1){
            int value;
            printf("\nEnter the value to put instead: ");
            scanf("%d", &value);
            dataframe->col[column]->tab[row] = value;
        }
    }while(answer!=1 && answer != 0);
}




