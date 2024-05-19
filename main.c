#include <stdio.h>
#include <string.h>

#include "column.h"
#include "cdataframe.h"
#include "sort.h"
#include "list.h"


int main() {
    int choice;
    CDATAFRAME *cdf = NULL;
    ENUM_TYPE cdftype[] = {};
    do {
        printf("\n--- Principal Menu ---\n");
        printf("\n1. Filling\n2. Basic Displaying\n3. Usual Operations \n4. Analysis and Statistics\n5. Amazing sort and display\n6. Save and load (CSV)\n0. Exit\n");
        choice = valid_input(0, 6);
        // must create a cdf before any action
        if (choice != 1 && choice!=6 && cdf == NULL) {
            choice = -1;
        }
        switch (choice) {

            case -1: {
                perror("You must create or load a dataframe first!\n");
                break;
            }
            case 1: {
                printf("1.Creation of an empty CDataframe \n2. Filling in the CDataframe with an input \n3. Hard filling of the CDataframe\n4.Go back to the principal menu\n");
                choice = valid_input(1, 4);
                if ((choice == 1 || choice == 3) && cdf != NULL) {
                    choice = -1;
                }
                switch (choice) {
                    case -1: {
                        perror("You have already created a dataframe!\n");
                        break;
                    }
                    case 1://Creation of an empty CDataframe
                    {
                        int phys_size;
                        printf("How many columns do you want in the Dataframe? (max %d)", REALLOC_SIZE);
                        phys_size = valid_input(1, REALLOC_SIZE);
                        choose_type(cdftype, phys_size);
                        cdf = create_cdataframe(cdftype, phys_size);
                        break;
                    }
                    case 2: // Filling in the CDataframe with an input
                    {
                        //check if the dataframe has allocated memory
                        cdf = is_cdataframe(cdf, cdftype);
                        fill_cdataframe(cdf);
                        break;
                    }
                    case 3: // Hard filling of the CDataframe
                    {
                        cdf = is_cdataframe(cdf, cdftype);
                        hard_fill_dataframe(cdf, cdftype);
                        break;
                    }
                    case(4):{ // Go back to the previous menu
                        break;
                    }
                }
                break;
            }
            case 2: {
                printf("\n1. Display the entire CDataframe \n2. Display a part of the CDataframe rows according to a chosen limit\n3. Display a part of the columns of the CDataframe according to a limit supplied by the user\n4.Go back to the principal menu\n");
                choice = valid_input(1, 4);
                switch (choice) {
                    case 1: // Display the entire CDataframe
                    {
                        display_dataframe(cdf, 0, 0);
                        break;
                    }
                    case 2: // Display a part of the CDataframe rows according to a chosen limit
                    {
                        int nb_lines;
                        printf("How many lines do you want to display?");
                        nb_lines = valid_input(1, longest_col(cdf));
                        display_dataframe(cdf, nb_lines, 0);
                        break;
                    }
                    case 3: // Display a part of the columns of the CDataframe according to a limit supplied by the user
                    {
                        int nb_col;
                        printf("How many columns do you want to display?");
                        nb_col = valid_input(1, longest_col(cdf));
                        display_dataframe(cdf, 0, nb_col);
                        break;
                    }
                    case 4: { // Go back to the previous menu
                        break;
                    }
                }
                break;
            }
            case 3: {
                printf("1. Add a row of values at the end of the CDataframe\n2. Delete a row of values from the CDataframe\n3. Add a column to the CDataframe"
                       " \n4. Delete a column from the CDataframe\n5. Rename the title of a column in the CDataframe \n6. Check the existence of a value (search) in the CDataframe"
                       "\n7. Access/replace the value in a CDataframe cell using its row and column number\n8. Display column names\n9. Go back to the principal menu\n");
                choice = valid_input(1, 9);
                switch (choice) {
                    case 1: // Add a row of values to the CDataframe
                    {
                        add_line_dataframe(cdf);
                        break;
                    }
                    case 2: // Delete a row of values from the CDataframe
                    {
                        printf("Enter the index of the row to remove");
                        delete_line_cdataframe(cdf, valid_input(0, longest_col(cdf)-1));
                        break;
                    }
                    case 3: // Add a column to the CDataframe
                    {
                        int result;
                        char* title = (char*)malloc(REALLOC_SIZE * sizeof(char));
                        choose_title_not_inside(cdf, title);
                        result = add_column(cdf, title);
                        if(result){
                            printf("Column successfully added.\n");
                        }else{
                            printf("Can't add a column: no more place in memory.\n");
                        }
                        break;
                    }
                    case 4: // Delete a column from the CDataframe
                    {
                        char* title = (char*)malloc(100*sizeof(char));
                        int index_col_title;

                        printf("Which column do you want to delete?\n");
                        display_titles(cdf,0);printf("\n");
                        choose_title_inside(cdf,title);
                        delete_column_by_name(&cdf, title);
                        printf("Column deleted");
                        break;
                    }
                    case 5: // Rename the title of a column in the CDataframe
                    {
                        display_dataframe(cdf, 0, 0);
                        rename_col_dataframe(cdf);
                        break;
                    }
                    case 6:{
                        char str[REALLOC_SIZE];
                        void* value= NULL;
                        ENUM_TYPE cdftype_2[] = {};
                        COORD* tab = NULL;
                        choose_type(cdftype_2, 1);
                        // fill tab of coord
                        if (cdftype_2[0]!= 7 ){
                            input_value(cdftype_2[0], &value);
                            tab = search_value_index(cdf, cdftype_2[0], value, tab);
                            convert_chosen_value(cdftype_2[0], str, value);
                        }
                        else{
                            char value[REALLOC_SIZE];
                            input_value(cdftype_2[0], &value);
                            tab = search_value_index(cdf, cdftype_2[0], value, tab);
                            printf("OK");
                        }
                        // display result
                        if (tab!=NULL){
                            printf("OK");
                            for(int i=0; i< tab->ls; i++){
                                printf("(%d;%d)", tab[i].col, tab[i].line);
                            }
                        }
                        else{
                            printf("%s is not in the dataframe.", value);
                        }
                        break;
                    }
                    case 7: // Access/replace the value in a Ccdf cell using its row and column number
                    {
                        access_replace(cdf);
                        break;
                    }
                    case 8: // Display column names
                    {
                        display_titles(cdf, 0);
                        break;
                    }
                    case 9:{ // Go back to the previous menu
                        break;
                    }
                }
                break;
            }
            case 4: {
                printf("1. Display the number of rows\n2. Display the number of columns\n3. Display the number of cells equal to a chosen value"
                       " \n4. Display the number of cells containing a value greater than a chosen value\n5. Display the number of cells containing a value less than a chosen value \n6. Go back to the principal menu\n");
                choice = valid_input(1, 6);
                switch (choice) {
                    case 1: // Display the number of rows
                    {
                        int col_size = longest_col(cdf);
                        if(col_size>1){
                            printf("There are %d rows in the dataframe.\n",col_size );
                        }
                        else{
                            printf("There is 1 row in the dataframe.\n");
                        }
                        break;
                    }
                    case 2: // Display the number of columns
                    {
                        int cdf_size =  cdataframe_size(cdf);
                        if(cdf_size>1){
                            printf("There are %d columns in the dataframe.\n", cdf_size);
                        }
                        else{
                            printf("There is 1 column in the dataframe.\n");
                        }

                        break;
                    }
                    case 3: // Display the number of cells equal to x (x given as parameter)
                    {
                        void* value;
                        char str[REALLOC_SIZE];
                        int res;
                        ENUM_TYPE cdftype_1[] = {};
                        choose_type(cdftype_1, 1);
                        if(cdftype_1[0]!=7){// not a type string
                            input_value(cdftype_1[0], &value);
                            res = equal(cdf,cdftype_1[0],value);
                            convert_chosen_value(cdftype_1[0], str, value);
                        }
                        else{
                            char value[REALLOC_SIZE];
                            input_value(cdftype_1[0], &value);
                            res = equal(cdf,cdftype_1[0],value);
                            strcpy(str, value);
                        }
                        // display res
                        if (res) {
                            if(res>1){
                                printf("There are %d cells with the value %d.\n", res, str);
                            }
                            else{
                                printf("There is 1 cell with the value %d.\n", str);
                            }

                        } else {
                            printf("%d is not in the dataframe.", str);
                        }
                        break;
                    }
                    case 4: // Display the number of cells containing a value greater than a chosen value
                    {
                        void* value;
                        int res;
                        char str[REALLOC_SIZE];
                        ENUM_TYPE cdftype_1[] = {};
                        lnode* tmp = cdf->head;
                        for(int i =0; i< cdataframe_size(cdf); i++){
                            if(is_sorted_column(cdf)==1) { // sorted col
                                if (((COLUMN *) tmp->data)->column_type == cdftype_1[0]) {
                                    search_value_in_column((COLUMN *) tmp->data, value);
                                }
                            }
                            else{
                                if (((COLUMN *) tmp->data)->column_type == cdftype_1[0]) {
                                    if (cdftype_1[0] != 7) { // not type string
                                        res = greater(cdf, cdftype_1[0], value);
                                        convert_chosen_value(cdftype_1[0], str, &value);
                                    } else {
                                        res = equal(cdf, cdftype_1[0], value);
                                        strcpy(str, value);
                                    }
                                }
                            }
                            tmp = tmp->next;
                        }
                        if (res){
                            if(res>1){
                                printf("There are %d cells with greater values than %s.\n", res,str);
                            }else{
                                printf("There is 1 cell with a greater value than %s.\n",str);
                            }
                        }
                        else {
                            printf("There is no value greater than %s in the dataframe.", str);
                        }
                        break;
                    }
                    case 5: // Display the number of cells containing a value less than a chosen value
                    {
                        void* value;
                        int res;
                        char str[REALLOC_SIZE];
                        ENUM_TYPE cdftype_1[] = {};
                        if(cdftype_1[0]!=7){// not a type string
                            input_value(cdftype_1[0], &value);
                            res = smaller(cdf,cdftype_1[0],value);
                            convert_chosen_value(cdftype_1[0], str, value);
                        }
                        else{
                            char value[REALLOC_SIZE];
                            input_value(cdftype_1[0], &value);
                            res = equal(cdf,cdftype_1[0],value);
                            strcpy(str, value);
                        }
                        if (res){
                            if(res>1){
                                printf("There are %d cells with smaller values than %d.\n", res,str);
                            }else{
                                printf("There is 1 cell with a smaller value than %d.\n",str);
                            }
                        }
                        else {
                            printf("There is no value smaller than %d in the dataframe.", str);
                        }
                        break;
                    }
                    case(6):{// Go back to the previous menu
                        break;
                    }
                }
                break;
            }
            case(5):{ // sort cdf and display sorted dataframe
                printf("1. Sort a column by ascending order\n2. Sort a column by decreasing order\n"
                       "3. Display the sorted dataframe\n4. Go back to the principal menu\n");
                choice = valid_input(1, 4);
                if (choice ==3 && is_sorted_column(cdf)==0 ) { // cannot display by index if there is no sorted column
                    choice = -1;
                }
                switch(choice){
                    case(-1):{
                        printf("You must sort a column of your dataframe first !");
                        break;
                    }
                    case(1):{
                        int index, i=0;
                        printf("Which column do you want to sort?\n");
                        display_titles(cdf,0);
                        printf("Input its index :");
                        index = valid_input(0, cdataframe_size(cdf)-1);
                        lnode*tmp = cdf->head;
                        while(i!=index){
                            tmp = tmp->next;
                            i++;
                        }
                        sort((COLUMN*)tmp->data, 0);
                        printf("Your sorted column :\n");
                        print_col_by_index((COLUMN*)tmp->data);
                        break;
                    }
                    case(2):{
                        int index, i=0;
                        printf("Which column do you want to sort?\n");
                        display_titles(cdf,0);
                        printf("Input its index :");
                        index = valid_input(0, cdataframe_size(cdf)-1);
                        lnode*tmp = cdf->head;
                        while(i!=index){
                            tmp = tmp->next;
                            i++;
                        }
                        sort((COLUMN*)tmp->data, 1);
                        printf("Your sorted column :\n");
                        print_col_by_index((COLUMN*)tmp->data);
                        break;
                    }
                    case(3):{ // display sorted dataframe
                        int choice;
                        printf("Do you want to display all the dataframe or choose a limit of column and lines?\n");
                        printf("Choose 1 to display all the dataframe and 0 else.");
                        choice = valid_input(0,1);
                        if (choice){
                            display_sorted_cdf(cdf, 0, 0);
                        }
                        else{
                            int nb_col, nb_lines;
                            // choose columns
                            printf("How many columns do you want to display?");
                            nb_col = valid_input(0, cdataframe_size(cdf)-1);
                            // choose lines
                            printf("How many lines do you want to display?");
                            nb_lines = valid_input(0, longest_col(cdf));

                            display_sorted_cdf(cdf, nb_lines, nb_col);
                            break;
                        }

                    }
                    case(4):{// Go back to the previous menu
                        break;
                    }
                }
                break;
            }
            case(6):{// Loading and saving in CSV files
                printf("1. Load from a file (CSV)\n2. Save in a CSV file\n3. Exit\n");
                choice = valid_input(1, 3);

                if (choice != 1 && cdf == NULL) {
                    choice = -1;
                }

                switch(choice){
                    case -1: {
                        perror("You must create or load a dataframe first!\n");
                        break;
                    }
                    case(1):{ //Loading from a file
                        if(cdf!=NULL) { // already have a dataframe
                            printf("This will delete your current dataframe. Are you sure? 1. yes 2. no\n");
                            int answ = valid_input(1, 2);
                            if (answ) {
                                delete_cdataframe(&cdf);
                            } else{
                                break;
                            }
                        }

                        char name[REALLOC_SIZE];
                        printf("What is the name of your file?");
                        scanf("%s", name);
                        cdf = load_from_csv(name);
                        break;
                    }
                    case(2):{
                        char name[REALLOC_SIZE];
                        printf("You want to save under what name?");
                        scanf("%s", name);
                        save_into_csv(cdf, name);
                        break;
                    }
                    case(3):{
                        break;
                    }
                }
                break;
            }
        }
    }
    while (choice != 0);

    if (cdf!=NULL){
        delete_cdataframe(&cdf);
    }
    return 0;
}
