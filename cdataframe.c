//
// Created by Aube on 29/03/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cdataframe.h"
#include "list.h"
#include "column.h"

#define MAX_LINE_LENGTH 1024
#include <unistd.h>

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


int longest_col(CDATAFRAME* cdf){
    int max=0;
    LNODE* tmp = cdf->head;
    int nb_col = cdataframe_size(cdf);
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
        delete_column(&(tmp->data));
        tmp = tmp->next;
    }
    delete_column(&(tmp->data));
    lst_delete_list((list *) *cdf);
    free(*cdf);
    *cdf= NULL;
}

// à tester -> ne fonctionnne pas
void delete_column_by_name(CDATAFRAME **cdf, char *col_name){
    int deleted = 0;
    LNODE* tmp = (*cdf)->head;
    int size = cdataframe_size(cdf);
    for(int i =0; i < size && !deleted ; i++){
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
            case(FLOAT):{
                float nb = 1;
                for(int j=0; j< nbr_val; j++){;
                    insert_value(tmp ->data, &nb);
                    nb++;
                }
                break;
                }
            case(DOUBLE):{
                double nb = 1;
                for(int j=0; j< nbr_val; j++){;
                    insert_value(tmp ->data, &nb);
                    nb++;
                }
                break;
            }
            case(STRUCTURE):{
                break;
            }
            default:{ // for int and unit types
                for(int j=0; j< nbr_val; j++){;
                    insert_value(tmp ->data, &j);
                }
                break;
            }
        }
        tmp = tmp->next;
    }
}

void display_titles(CDATAFRAME* cdf, int size){
    if (size==0)
        size = cdataframe_size(cdf);
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
        nb_col = cdataframe_size(cdf);
    }
    display_titles(cdf, nb_col);
    //display values and index
    printf("\n");
    char str[REALLOC_SIZE];//buffer
    for(int i = 0; i < nb_lines; i++) {
        LNODE * tmp = cdf->head;
        for(int j = 0;j < nb_col; j++) {
            if(i < ((COLUMN*)tmp->data)->size){
                convert_value((COLUMN *) tmp->data, i, str, REALLOC_SIZE);
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

void display_sorted_cdf(CDATAFRAME* cdf, int nb_lines, int nb_col){

    // if the user want to display all the dataframe
    if (nb_lines==0){
        //the number of lines to print is the logical size of longest column
        nb_lines = longest_col(cdf);
    }
    if (nb_col==0){
        nb_col = cdataframe_size(cdf);
    }
    display_titles(cdf, nb_col);

    LNODE * tmp = cdf->head;
    int column;
    int size = cdataframe_size(cdf);
    int index=0;
    printf("In function of which column do you want to display the dataframe?");
    do{
        int choice_col;
        printf("Enter the index of the column:");
        choice_col = valid_input(0,nb_col);
        index = check_index((COLUMN*)tmp->data);
    }while(index != 1);

    column = valid_input(0, size-1);
    //display values and index
    printf("\n");
    char str[REALLOC_SIZE];//buffer
    for(int i = 0; i < nb_lines; i++) {
        LNODE * tmp = cdf->head;
        for(int j = 0;j < nb_col; j++) {
            if(i < ((COLUMN*)tmp->data)->size){
                convert_value((COLUMN *) tmp->data, i, str, REALLOC_SIZE);
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
        printf("How many columns do you want in the Dataframe? (max %d)", REALLOC_SIZE);
        phys_size = valid_input(1, REALLOC_SIZE);
        choose_type(cdftype, phys_size);
        cdf = create_cdataframe(cdftype, phys_size);
    }
    return cdf;
}

void fill_cdataframe(CDATAFRAME* cdf){
    LNODE* tmp = cdf->head;
    int size = cdataframe_size(cdf);
    while(size>0){
        int nbr_val;
        printf("How many value do you want in the column %s :", ((COLUMN*) tmp->data)->title);
        nbr_val = valid_input(1, REALLOC_SIZE);
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
    int size = cdataframe_size(cdf);
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
    printf("%s ", cdf->head->data->title);
    int size = cdataframe_size(cdf);
    while (tmp != NULL){
        printf("%s ", tmp->data->title);

        if((tmp->data)->size>= index){
            printf("%d ", tmp->data->size);
            delete_value(((COLUMN*)tmp->data), index);
        }
        tmp = tmp->next;
    }
}

int add_column(CDATAFRAME* cdf, char* title){
    int size = cdataframe_size(cdf);
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
            nbr_val = valid_input(1, REALLOC_SIZE);
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
            nbr_val = valid_input(1, REALLOC_SIZE);
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
            display_titles(cdf,0);printf("\n");
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
            nbr_val = valid_input(1, REALLOC_SIZE);
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
    int size = REALLOC_SIZE;
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
    LNODE *tmp = cdf->head;
    int size = cdataframe_size(cdf);
    char str1[REALLOC_SIZE], str2[REALLOC_SIZE];//buffer
    int cpt = 0;
    convert_chosen_value(type, str2, value);
    for (int i = 0; i < size; i++) {
        if (((COLUMN *) tmp->data)->column_type == type) {
            for (int j = 0; j < ((COLUMN *) tmp->data)->size; j++) {
                convert_value((COLUMN *) tmp->data, j, str1, REALLOC_SIZE);
                printf("2 strings :%s, %s", str1, str2);
                if (strcmp(str1, str2) == 0) {
                    cpt++;
                }
            }
        }
        tmp = tmp->next;
    }
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
                if (strcmp(str1, str2)> 0) {
                    cpt++;
                }
            }
        }
        tmp = tmp->next;
    }
    return cpt;
}


int is_sorted_column(CDATAFRAME* cdf){
    LNODE *tmp = cdf->head;
    int size = cdataframe_size(cdf);
    int sorted = 0;
    // check if there is a sorted list
    for(int i = 0; i<size; i++){
        if (check_type((COLUMN *) tmp->data)== 1){
            sorted++;
        }
    }
    return sorted;
}

void access_replace(CDATAFRAME* cdf){
    display_dataframe(cdf,0,0);
    int column, row;
    int size = cdataframe_size(cdf);
    printf("Enter the index of the column:");
    column = valid_input(0, size-1);
    // find the chosen column
    LNODE *tmp = cdf->head;
    for(int i=0; i<column; i++){
        tmp = tmp -> next;
    }
    char str[REALLOC_SIZE];
    printf("Enter the index of the row:");
    row = valid_input(0,((COLUMN *) tmp->data)->size);
    convert_value((COLUMN *) tmp->data,row, str, REALLOC_SIZE);
    printf("The value at this position is %s.",str);
    int answer;
    do {
        printf("Do you want to replace it? 1 for yes 0 for no: ");
        scanf("%d", &answer);
        if(answer==1){
            // search the type in the list
            char* types[] = {"UINT", "INT", "CHAR", "FLOAT", "DOUBLE", "STRING", "STRUCTURE"};
            int i = 2;
            while(((COLUMN *) tmp->data)->column_type != i){
                i++;
            }
            void *value;
            printf("\nEnter the value of type %s to put instead: ", types[i-1]);
            input_value(((COLUMN *) tmp->data)->column_type, &value);
            //delete_value(((COLUMN *)tmp->data), row);
            printf("ok");
            change_value((COLUMN *)tmp->data, value, row);
        }
    }while(answer!=1 && answer != 0);
}

int smaller(CDATAFRAME* cdf, ENUM_TYPE type, void* value){
    LNODE *tmp = cdf->head;
    int size = cdataframe_size(cdf);
    char str1[REALLOC_SIZE], str2[REALLOC_SIZE];//buffer
    int cpt = 0;
    convert_chosen_value((ENUM_TYPE)type, str2, &value);
    for (int i = 0; i < size; i++) {
        if (((COLUMN *) tmp->data)->column_type == type) {
            for (int j = 0; j < ((COLUMN *) tmp->data)->size; j++) {
                convert_value((COLUMN *) tmp->data, j, str1, REALLOC_SIZE);
                // strcmp > 0 => str1 < str2 (value)
                if (strcmp(str1, str2)< 0) {
                    cpt++;
                }
            }
        }
        tmp = tmp->next;
    }
    return cpt;
}

void* input_str_to_typed(ENUM_TYPE type_col, char *choice){
    switch(type_col){
        case UINT:{
            char *endptr;
            long int value = strtol(choice, &endptr, 10);
            if (endptr == choice) {
                printf("Conversion error, problem in data supposed to be uint\n");
                return NULL;
            } else {
                int* res= malloc(sizeof(unsigned int));
                *res = (unsigned int)value;
                //printf("uint: %d\n", *res);
                return res;
            }
            break;
        }
        case INT:{
            char *endptr;
            long int value = strtol(choice, &endptr, 10);
            if (endptr == choice) {
                printf("Conversion error, problem in data supposed to be int\n");
                return NULL;
            } else {
                int* res= malloc(sizeof(int));
                *res = (int)value;
                //printf("int: %d\n", *res);
                return res;
            }
            break;
        }
        case CHAR:{
            char* res = malloc(sizeof(char));
            *res = choice[0];
            //printf("char: %c\n", *res);
            return res;
        }
        case FLOAT:{
            char *endptr;
            float value = strtof(choice, &endptr);
            if (endptr == choice) {
                printf("Conversion error, problem in data supposed to be float\n");
                return NULL;
            } else {
                float* res = malloc(sizeof(float));
                *res = value;
                //printf("float: %f\n", *res);
                return res;
            }
        }
        case DOUBLE:{
            char *endptr;
            double value = strtod(choice, &endptr);
            if (endptr == choice) {
                printf("Conversion error, problem in data supposed to be double\n");
                return NULL;
            } else {
                double* res = malloc(sizeof(double));
                *res = value;
                //printf("double: %lf\n", *res);
                return res;
            }
        }
        case STRING:{
            char* res = strdup(choice);
            //printf("string: %s\n", res);
            return res;
        }
        case STRUCTURE:
            // pass this one
            break;
    }
}


void remove_newline(char* text){
    size_t len = strlen(text);
    if(len>0 && text[len-1]=='\n'){
        text[len-1]='\0';
    }
}

CDATAFRAME* load_from_csv(char *file_name){
    // creating a proper path to the file
    char path[REALLOC_SIZE] = "../csv_data/";
    strcat(path, file_name);
    strcat(path, ".csv");

    FILE* csv_file;
    char line[MAX_LINE_LENGTH];
    char *token ; // pointer to go through the sub-chaine obtained
    char* limit = ",";
    short unsigned int size=0;
    //----------------------- ouverture du fichier de donnÃ©es CSV ------------------------------

    csv_file = fopen( path, "rt") ;
    if (csv_file==NULL)
    {
        perror("Can't open file!\n");
        return NULL;
    }
    //----------------------- Reading the data from the CSV file ------------------------------

    // Reading the first line -> types of the column
    ENUM_TYPE* types = malloc(REALLOC_SIZE*sizeof(ENUM_TYPE));

    fgets( line, MAX_LINE_LENGTH, csv_file); // getting the line
    if (line==NULL)perror("Empty file"); //if it's empty

    token = strtok(line, limit); // Initial call to strtok
    while (token != NULL) {
        size++;
        char *endptr;
        long int value = strtol(token, &endptr, 10);
        if (endptr == token) {
            printf("Conversion error, types not properly defined, can't load file\n");
            return NULL;
        } else {
            types[size - 1] = (ENUM_TYPE)value+1;
        }
        token = strtok(NULL, limit);
    }

    // Reading the titles of the columns and creating the dataframe
    CDATAFRAME * cdf = (CDATAFRAME *) lst_create_list();
    fgets( line, MAX_LINE_LENGTH, csv_file); // getting the line
    token = strtok(line, limit); // Initial call to strtok
    for(int i = 0; i<size; i++){
        char *title = strdup(token);
        remove_newline(title);
        COLUMN* col = (COLUMN *) create_column(types[i], title);
        lnode* ptr_col = lst_create_lnode(col);
        lst_insert_tail((list *) cdf, ptr_col);
        token = strtok(NULL, limit);
    }

    int works;
    while (fgets(line, MAX_LINE_LENGTH, csv_file)) {
        line[strcspn(line, "\n")] = 0;
        token = strtok(line, limit);
        LNODE* temp = cdf->head;
        for(int i = 0; i<size; i++){
            void* val = input_str_to_typed(temp->data->column_type, token);
            if(val==NULL){
                perror("import failed: no memory?");
                delete_cdataframe(&cdf);
                return NULL;
            } else{
                works = insert_value(temp->data, val);
                free(val);
                if (!works){
                    perror("import failed: fail to add in column");
                    delete_cdataframe(&cdf);
                    return NULL;
                }
            }
            token = strtok(NULL, limit);
            temp = temp->next;
        }
    }

    if(cdf==NULL)
        printf("marche pas");

    fclose(csv_file);
    return cdf;
}


void save_into_csv(CDATAFRAME *cdf, char *file_name){
    // creating a proper path to the file
    char path[REALLOC_SIZE] = "../csv_data/";
    strcat(path, file_name);
    strcat(path, ".csv");

    FILE *csv_file;
    csv_file = fopen(path, "w+"); // open
    if (csv_file==NULL){
        printf("Fail to open the file");
        return;
    }
    int size = cdataframe_size(cdf);
    LNODE* tmp;



    // writing the types
    tmp = cdf->head;
    for(int i =0; i<size-1; i++){
        fprintf(csv_file, "%d,", tmp->data->column_type-1);
        tmp=tmp->next;
    }
    fprintf(csv_file, "%d\n", tmp->data->column_type-1);

    // writing the names of columns
    tmp = cdf->head;
    for(int i =0; i<size-1; i++){
        fprintf(csv_file, "%s,", tmp->data->title);
        tmp=tmp->next;
    }
    fprintf(csv_file, "%s\n", tmp->data->title);

    printf("reached middle\n");

    // writing the data
    int depth = longest_col(cdf);
    char val[REALLOC_SIZE];
    for (int j =0; j<depth;j++){
        printf("depth : %d\n", j);
        tmp = cdf->head;
        for(int i =0; i<size-1; i++){
            printf("col : %d\n", i);
            convert_value((COLUMN*)tmp->data, j, val, REALLOC_SIZE);
            fprintf(csv_file, "%s,", val);
            tmp=tmp->next;
        }
        convert_value((COLUMN*)tmp->data, j, val, REALLOC_SIZE);
        fprintf(csv_file, "%s\n", val);
    }


    fclose(csv_file); // close
}











