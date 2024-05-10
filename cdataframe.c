//
// Created by Aube on 29/03/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cdataframe.h"
#include "list.h"
#include "column.h"

void choose_title(char* title, int nb){
    printf("Choose the title of column %d:", nb);
    scanf("%s",title);
}

void choose_type(ENUM_TYPE* cdftype, int size){
    char* types[] = {"1. UINT", "2. INT", "3. CHAR", "4. FLOAT", "5. DOUBLE", "6. STRING", "7. STRUCTURE"};
    printf("All the types available are:\n ");
    for(int i=0; i<7; i++){
        printf("%s\n",types[i]);
    }
    printf("To choose a type you must entre it's number. You can choose a type per column.\n");
    for (int i= 0; i<size; i++){
        printf("For column %d ", i+1);
        cdftype[i]= valid_input(1,8);
    }
}

int lenght_cdf(CDATAFRAME* cdf){
    int size=0;
    LNODE* tmp = cdf->head;
    while (tmp->next != NULL){
        size++;
        tmp = tmp->next;
    }
    size++;
    return size;
}

int longest_col(CDATAFRAME* cdf){
    int max=0;
    LNODE* tmp = cdf->head;
    int nb_col = lenght_cdf(cdf);
    for(int i=0; i<nb_col;i++){
        if (((COLUMN*)tmp->data)->size> max){
            max = ((COLUMN*)tmp->data)->size;
        }
        tmp = tmp->next;
    }
    return max;
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

CDATAFRAME *create_cdataframe(ENUM_TYPE *cdftype, int size){
    CDATAFRAME * cdf = (CDATAFRAME *) lst_create_list();
    for(int i = 0; i<size; i++){
        char* title = (char *)malloc(100*sizeof(char));
        choose_title(title, i+1);
        COLUMN* col = (COLUMN *) create_column(cdftype[i], title);
        lnode* ptr_col = lst_create_lnode(col);
        lst_insert_tail((list *) cdf, ptr_col);

    }
    return cdf;
}

int get_cdataframe_cols_size(CDATAFRAME *cdf){
    int size = 0;
    LNODE* tmp_lnode = cdf->head;
    while(tmp_lnode->next != NULL){
        tmp_lnode = tmp_lnode->next;
        size++;
    }
    size++;// to count the last node of the list
    return size;
}

void delete_cdataframe(CDATAFRAME **cdf){
    LNODE* tmp_lnode = (*cdf)->head;
    int count = 0;
    int size = get_cdataframe_cols_size(*cdf);
    while(count <= size){
        delete_column(tmp_lnode->data);
        tmp_lnode = tmp_lnode->next;
        count++;
    }
    lst_delete_list((list *) *cdf);
}

void delete_column_by_name(CDATAFRAME *cdf, char *col_name){
    int deleted = 0;
    LNODE* tmp = cdf->head;
    int size = get_cdataframe_cols_size(cdf);
    for(int i =0; i < size ; i++){
        // strcmp return 0 if col_name correspond to a column name in cdf
        if( strcmp(((COLUMN*)tmp->data)->title, col_name) == 0){
            delete_column((COLUMN **) &(tmp->data));
            lst_delete_lnode((list*)cdf,(lnode*)tmp);
            deleted = 1;
        }
        tmp = tmp->next;
    }
    if(deleted){
        printf("The column %s has been deleted.\n", col_name);
    }
    else{
        printf("There is no column named %s.\n", col_name);
    }
}

// faire un switch en fct des types(les metre en parametre)
void hard_fill_dataframe(CDATAFRAME * cdf){
    LNODE* tmp = cdf->head;
    int size = get_cdataframe_cols_size(cdf);
    for(int i = 0; i < size; i++){
        int nbr_val = 5;
        for(int j=0; j< nbr_val; j++){;
            insert_value(tmp ->data, &j);
        }
        tmp = tmp->next;
    }
}

void display_dataframe(CDATAFRAME* cdf){

    //display titles
    int size = get_cdataframe_cols_size(cdf);
    LNODE * tmp = (LNODE *) cdf->head;
    for (int i=0; i<size; i++){
        printf("%s\t", ((COLUMN*)tmp->data)->title);
        tmp = tmp->next;
    }
    //display values and index
    printf("\n");
    int nb_col = lenght_cdf(cdf);
    int nb_lines = longest_col(cdf);
    printf("%d",nb_lines);
    char str[REALOC_SIZE];//buffer
    for(int i = 0; i < nb_lines; i++) {
        tmp = cdf->head;
        for(int j = 0;j < nb_col; j++) {
            if(i < ((COLUMN*)tmp->data)->size ){
                convert_value((COLUMN *) tmp->data, i, str, REALOC_SIZE);
                printf("[%d] %s\t",i, str);
            }else{
                printf("[%d] /\t", i);
            }
            tmp = tmp->next;
        }
        printf("\n");
    }
    printf("\n");
}

CDATAFRAME* is_cdataframe(CDATAFRAME* cdf, ENUM_TYPE* cdftype){
    if (cdf ==NULL){
        int phys_size;
        printf("Let's first create a dataframe. ");
        printf("How many columns do you want in the Dataframe? (max %d)", REALOC_SIZE);
        phys_size = valid_input(1, REALOC_SIZE);
        choose_type(cdftype, phys_size);
        cdf = create_cdataframe(cdftype, phys_size);
    }
    return cdf;
}

void fill_cdataframe(CDATAFRAME* cdf){
    LNODE* tmp = cdf->head;
    int size = lenght_cdf(cdf);
    while(size>0){
        int nbr_val;
        printf("How many value do you want in the column %s :", ((COLUMN*) tmp->data)->title);
        nbr_val = valid_input(1, REALOC_SIZE);
        for(int j=0; j< nbr_val; j++){
            int value;
            printf("\nEnter the value to insert: ");
            scanf("%d", &value);
            insert_value(tmp->data,&value);
        }
        size--;
        tmp = tmp->next;
    }
}

/*
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



int still_in_frame(DATAFRAME* dataframe;int i){
    int bool = 0;
    for(int j = 0; j < dataframe->ls; j++){

    }
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

*/

