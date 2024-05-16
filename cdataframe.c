//
// Created by Aube on 29/03/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cdataframe.h"
#include "list.h"
#include "column.h"

void choose_title(char* title){
    printf("Choose the title of the column: ");
    scanf("%s",title);
}
/*
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
}*/

void choose_title_not_inside(CDATAFRAME* cdf, char* title){
    do{
        printf("Choose the title of the column:");
        scanf("%s",title);
        if (title_in_dataframe(cdf, title)!=-1){
            printf("This title is already in the dataframe!\n");
        }
    }while(title_in_dataframe(cdf, title)!=-1);
}

void choose_title_inside(CDATAFRAME* cdf, char* title){
    do{
        printf("Choose the title of the column:");
        scanf("%s",title);
        if (title_in_dataframe(cdf, title)==-1){
            printf("This title is not in the dataframe!\n");
        }
    }while(title_in_dataframe(cdf, title)==-1);
}

int title_in_dataframe(CDATAFRAME* cdf, char* title) {
    LNODE* tmp = cdf->head;
    int size = cdataframe_size(cdf);
    for (int i = 0; i < size; i++){
        // if strings equal strcmp = 0
        if (strcmp(title, ((COLUMN*)tmp->data)->title) == 0) {
            return i;
        }
        tmp = tmp->next;
    }
    return -1; //not in dataframe
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

void choose_type(ENUM_TYPE* cdftype, int size){
    char* types[] = {"1. UINT", "2. INT", "3. CHAR", "4. FLOAT", "5. DOUBLE", "6. STRING", "7. STRUCTURE"};
    printf("All the types available are:\n ");
    for(int i=0; i<7; i++){
        printf("%s\n",types[i]);
    }
    printf("To choose a type you must entre it's number. You can choose a type per column.\n");
    for (int i= 0; i<size; i++){
        printf("For column %d ", i+1);
        cdftype[i]= valid_input(1,7)+1;// +1 to avoid NULLVAL at 1 in enum_type
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

void input_value(ENUM_TYPE type_col, void *choice){
    int type;
    switch(type_col){
        case UINT:{
            unsigned int *val = (unsigned int *)choice;
            do{
                printf("\nChoose a value:");
                type = scanf("%d",val);//if the type is unsigned int type=1
                if (type != 1) {
                    printf("Invalid input.");
                    while (getchar() != '\n'); // to clear out the input buffer
                }
            }while (type!=1);
            break;
        }
        case INT:{
            int *val = (int *)choice;
            do{
                printf("\nChoose a value:");
                type = scanf("%d",val);//if the type is int type=1
                if (type != 1) {
                    printf("Invalid input.");
                    while (getchar() != '\n'); // to clear out the input buffer
                }
            }while (type!=1);
            break;
        }
        case CHAR:{
            char *val = (char *)choice;
            do{
                printf("\nChoose a value:");
                type = scanf(" %c",val);//if the type is char type=1
                if (type != 1) {
                    printf("Invalid input.");
                    while (getchar() != '\n'); // to clear out the input buffer
                }
            }while (type!=1);
            break;
        }
        case FLOAT:{
            float *val = (float *)choice;
            do{
                printf("\nChoose a value:");
                type = scanf("%f",val);//if the type is float type=1
                if (type != 1) {
                    printf("Invalid input.");
                    while (getchar() != '\n'); // to clear out the input buffer
                }
            }while (type!=1);
            break;
        }
        case DOUBLE:{
            double *val = (double *)choice;
            do{
                printf("\nChoose a value:");
                type = scanf("%lf",val);//if the type is double type=1
                if (type != 1) {
                    printf("Invalid input.");
                    while (getchar() != '\n'); // to clear out the input buffer
                }
            }while (type!=1);
            break;
        }
        case STRING:{
            char *val = (char *)choice;
            do{
                printf("\nChoose a value:");
                type = scanf(" %s",val);//if the type is a string type=1
                if (type != 1) {
                    printf("Invalid input.");
                    while (getchar() != '\n'); // to clear out the input buffer
                }
            }while (type!=1);
            break;
        }
        case STRUCTURE:
            break;
    }
}

CDATAFRAME *create_cdataframe(ENUM_TYPE *cdftype, int size){
    CDATAFRAME * cdf = (CDATAFRAME *) lst_create_list();
    for(int i = 0; i<size; i++){
        char* title = (char *)malloc(100*sizeof(char));
        if(i!=0){
            choose_title_not_inside(cdf, title);
        }
        else{
            choose_title(title);
        }
        COLUMN* col = (COLUMN *) create_column(cdftype[i], title);
        lnode* ptr_col = lst_create_lnode(col);
        lst_insert_tail((list *) cdf, ptr_col);
    }
    return cdf;
}

int cdataframe_size(CDATAFRAME *cdf){
    int size = 0;
    LNODE* tmp_lnode = cdf->head;
    while(tmp_lnode->next != NULL){
        tmp_lnode = tmp_lnode->next;
        size++;
    }
    size++;// to count the last node of the list
    return size;
}

// a retester
void delete_cdataframe(CDATAFRAME **cdf){
    LNODE* tmp = (*cdf)->head;
    while(tmp->next != NULL){
        delete_column(tmp->data);// pb
        tmp = tmp->next;
    }
    delete_column(tmp->data);
    lst_delete_list((list *) *cdf);
    free(tmp);
}

// à tester
void delete_column_by_name(CDATAFRAME **cdf, char *col_name){
    int deleted = 0;
    LNODE* tmp = (*cdf)->head;
    int size = cdataframe_size(*cdf);
    for(int i =0; i < size && !deleted ; i++){
        // strcmp return 0 if col_name correspond to a column name in cdf
        if( strcmp(((COLUMN*)tmp->data)->title, col_name) == 0){
            delete_column((COLUMN **) &(tmp->data));
            lst_delete_lnode((list*)*cdf,(lnode*)tmp);
            deleted = 1;
        }
        tmp = tmp->next;
    }
    if(deleted){
        if(size==1){
            printf("The column %s has been deleted.\n", col_name);
            *cdf = NULL;
            printf("The dataframe has been correctly deleted.");
        } else{
            printf("The column %s has been deleted.\n", col_name);
        }

    }
    else{
        printf("There is no column named %s.\n", col_name);
    }
}

void hard_fill_dataframe(CDATAFRAME * cdf, ENUM_TYPE* cdftype){
    LNODE* tmp = cdf->head;
    int size = cdataframe_size(cdf);
    int nbr_val = 5;
    for(int i = 0; i < size; i++){
        switch (cdftype[i]) {
            case(CHAR):{
                char val = 'A';
                for(int j=0; j< nbr_val; j++){;
                    insert_value(tmp ->data, &val);
                    val++;
                }
                break;
            }
            case(STRING):{
                char* val[]= {"Mega", "Giga", "Tera", "Kilo", "Octet"};
                for(int j=0; j< nbr_val; j++){;
                    insert_value(tmp ->data, val[j]);
                }
                break;
            }
            case(STRUCTURE):{
                break;
            }
            default:{ // for numbers types
                for(int j=0; j< nbr_val; j++){;
                    insert_value(tmp ->data, &j);
                }
                break;
            }
        }
        tmp = tmp->next;
    }
}

void display_titles(CDATAFRAME* cdf){
    int size = cdataframe_size(cdf);
    LNODE * tmp = (LNODE *) cdf->head;
    for (int i=0; i<size; i++){
        printf("%s\t", ((COLUMN*)tmp->data)->title);
        tmp = tmp->next;
    }
}
void display_dataframe(CDATAFRAME* cdf, int nb_lines, int nb_col){
    // if the user want to display all the dataframe
    if (nb_lines==0){
        //the number of lines to print is the logical size of longest column
        nb_lines = longest_col(cdf);
    }
    if (nb_col==0){
        nb_col = lenght_cdf(cdf);
    }
    display_titles(cdf);
    //display values and index
    printf("\n");
    char str[REALOC_SIZE];//buffer
    for(int i = 0; i < nb_lines; i++) {
        LNODE * tmp = cdf->head;
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
            printf("\nEnter the value to insert: ");
            void* choice;
            input_value(((COLUMN*) tmp->data)->column_type, &choice);
            insert_value(tmp->data,&choice);
        }
        size--;
        tmp = tmp->next;
    }
}

int check_type(COLUMN* col){
    ENUM_TYPE type = col->column_type;
    int i = 2;
    while(i<7 && type!=i){
        i++;
    }
    return i-1;
}

void add_line_dataframe(CDATAFRAME* cdf){
    char* types[] = {"UINT", "INT", "CHAR", "FLOAT", "DOUBLE", "STRING", "STRUCTURE"};
    LNODE* tmp = cdf->head;
    int size = lenght_cdf(cdf);
    for(int i= 0;i < size ;i++){
        printf("Insert the new value for the column %s (of type %s) ", ((COLUMN*)tmp->data)->title, types[check_type(((COLUMN*)tmp->data))-1]);
        void* choice;
        input_value(((COLUMN*) tmp->data)->column_type, &choice);
        insert_value(tmp->data,&choice);
        tmp = tmp->next;
    }

}

void delete_line_cdataframe(CDATAFRAME* cdf, int index){
    LNODE* tmp = cdf->head;
    int size = cdataframe_size(cdf);
    for(int i =0; i<size; i++){
        if(((COLUMN*)tmp->data)->size>= i){
            delete_value(((COLUMN*)tmp->data), index);
        }
        tmp = tmp->next;
    }
}

int add_column(CDATAFRAME* cdf, char* title){
    int size = lenght_cdf(cdf);
    ENUM_TYPE cdftype[] = {};
    int success = 0;
    choose_type(cdftype, 1);

    // creation of the new column
    COLUMN* col = (COLUMN *) create_column(cdftype[0], title);
    lnode* ptr_col = lst_create_lnode(col);

    // insert the column in the dataframe
    printf("Where do you want to insert your column ? Input the value corresponding to your choice.");
    printf("\n1. At the end of the dataframe\n2. At the beginning of the dataframe\n3. After a chosen column");
    int choice = valid_input(1,3);
    switch (choice) {
        case(1):{ // insert at the tail
            lst_insert_tail((list *) cdf, ptr_col);
            int nbr_val;
            LNODE *tmp = cdf->tail;
            printf("How many value do you want in your column: ");
            nbr_val = valid_input(1, REALOC_SIZE);
            for(int j=0; j< nbr_val; j++){
                printf("\nEnter the value to insert: ");
                void* val;
                input_value(((COLUMN*) tmp->data)->column_type, &val);
                insert_value(tmp->data,&val);
            }
            return 1;
        }
        case(2):{ // insert at the head
            lst_insert_head((list *) cdf, ptr_col);
            int nbr_val;
            LNODE *tmp = cdf->head;
            printf("How many value do you want in your column:");
            nbr_val = valid_input(1, REALOC_SIZE);
            for(int j=0; j< nbr_val; j++){
                printf("\nEnter the value to insert: ");
                void* val;
                input_value(((COLUMN*) tmp->data)->column_type, &val);
                insert_value(tmp->data,&val);
            }
            return 1;
        }
        case(3):{ // insert at a chosen position
            printf("After which column do you want to insert your new column? \n");
            display_titles(cdf);
            char* title_in = (char*)malloc(100*sizeof(char));
            choose_title_inside(cdf,title_in);
            LNODE *tmp = cdf->head;
            int i = 0;
            while(i <size && success == 0){
                if(strcmp(((COLUMN*)tmp->data)->title, title_in) ==0 ){
                    lst_insert_after((list *) cdf, ptr_col, (lnode *) tmp);
                    success = 1;
                }
                tmp = tmp->next;
                i++;
            }
            // fill column
            int nbr_val;
            printf("How many value do you want in your column:");
            nbr_val = valid_input(1, REALOC_SIZE);
            for(int j=0; j< nbr_val; j++){
                printf("\nEnter the value to insert: ");
                void* val;
                input_value(((COLUMN*) tmp->data)->column_type, &val);
                insert_value(tmp->data,&val);
            }
            free(title_in);
            return 1;
        }
    }
    return 0;
}

void convert_chosen_value(ENUM_TYPE type, char* str, void* value){
    int size = REALOC_SIZE;
    switch (type) {
        case UINT:{
            snprintf(str, size, "%d", *((unsigned int*)value));
            break;
        }
        case INT:{
            snprintf(str, size, "%d", *((int*)value));
            break;
        }
        case CHAR:{
            snprintf(str, size, "%c", *((char*)value));
            break;
        }
        case FLOAT:{
            snprintf(str, size, "%f", *((float*)value));
            break;
        }
        case DOUBLE:{
            snprintf(str, size, "%f", *((double*)value));
            break;
        }
        case STRING:{
            snprintf(str, size, "%s", ((char*)value));
            break;
        }
        case STRUCTURE:{
            // here we have to do a switch for the different structures
            break;
        }
    }
}

int equal(CDATAFRAME* cdf, ENUM_TYPE type, void* value) {
    printf("Bien rentré");
    printf("%s",cdf->head->data->title);
    LNODE* tmp = cdf->head;
    printf("1");
    int size = cdataframe_size(cdf);
    printf("2");
    char str1[REALLOC_SIZE], str2[REALLOC_SIZE];//buffer
    printf("3");
    int cpt = 0;
    convert_chosen_value(type, str2, value);
    for (int i = 0; i < size; i++) {
        if (((COLUMN *) tmp->data)->column_type == type) {
            for (int j = 0; j < ((COLUMN *) tmp->data)->size; j++) {
                convert_value((COLUMN *) tmp->data, j, str1, REALOC_SIZE);
                printf("2 strings :%s, %s", str1, str2);
                if (strcmp(str1, str2) == 0) {
                    cpt++;
                }
            }
        }
        tmp = tmp->next;
    }
    printf("après la boucle");
    return cpt;
}

void rename_col_dataframe(CDATAFRAME * cdf){
    printf("Which column do you want to rename?\n");
    char* ancient_title=(char*)malloc(REALLOC_SIZE*sizeof(char));
    choose_title_inside(cdf, ancient_title);

    printf("What is the new title?\n");
    char* new_title=(char*)malloc(REALLOC_SIZE*sizeof(char));
    choose_title_not_inside(cdf, new_title);

    int renamed = 0;
    LNODE* tmp = cdf->head;
    int size = cdataframe_size(cdf);
    for(int i =0; i < size && !renamed ; i++){
        // strcmp return 0 if col_name correspond to a column name in cdf
        if( strcmp(((COLUMN*)tmp->data)->title, ancient_title) == 0){
            free(((COLUMN*)tmp->data)->title);
            ((COLUMN*)tmp->data)->title = new_title;
            renamed=1;
        }
        tmp = tmp->next;
    }

    printf("Column successfuly renamed (～￣▽￣)～");
}

int greater(CDATAFRAME* cdf, ENUM_TYPE type, void* value){
    LNODE *tmp = cdf->head;
    int size = cdataframe_size(cdf);
    char str1[REALLOC_SIZE], str2[REALLOC_SIZE];//buffer
    int cpt = 0;
    convert_chosen_value((ENUM_TYPE)type, str2, &value);
    for (int i = 0; i < size; i++) {
        if (((COLUMN *) tmp->data)->column_type == type) {
            for (int j = 0; j < ((COLUMN *) tmp->data)->size; j++) {
                convert_value((COLUMN *) tmp->data, j, str1, REALLOC_SIZE);
                // strcmp > 0 => str1 > str2 (value)
                if (strcmp(str1, str2)< 0) {
                    cpt++;
                }
            }
        }
        tmp = tmp->next;
    }
    return cpt;
}

void access_replace(CDATAFRAME* cdf){
    display_dataframe(cdf,0,0);
    int column, row;
    int size = cdataframe_size(cdf);
    printf("Enter the index of the column:");
    column = valid_input(0, size);
    // find the chosen column
    LNODE *tmp = cdf->head;
    for(int i=0; i<column; i++){
        tmp = tmp -> next;
    }
    char str[REALLOC_SIZE];
    printf("Enter the index of the row:");
    row = valid_input(0,((COLUMN *) tmp->data)->size);
    convert_value((COLUMN *) tmp->data,row, str, REALLOC_SIZE);
    printf("The value at this position is %s. ",str);
    int answer;
    do {
        printf("Do you want to replace it? 1 for yes 0 for no: ");
        scanf("%d", &answer);
        if(answer==1){
            // search the type in the list
            char* types[] = {"1. UINT", "2. INT", "3. CHAR", "4. FLOAT", "5. DOUBLE", "6. STRING", "7. STRUCTURE"};
            printf("All the types available are:\n ");
            int i = 1;
            while(((COLUMN *) tmp->data)->column_type != i){
                i++;
            }
            void *value;
            printf("\nEnter the value of type %s to put instead: ", types[i-1]);
            input_value(((COLUMN *) tmp->data)->column_type, value);
            insert_value(((COLUMN *) tmp->data)->data[row],value);
        }
    }while(answer!=1 && answer != 0);
}



/*
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

