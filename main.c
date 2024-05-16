#include <stdio.h>

#include "column.h"
#include "cdataframe.h"
#include "sort.h"
#include "list.h"


int main() {

    int choice;
    CDATAFRAME *cdf = NULL;
    ENUM_TYPE cdftype[] = {};
    do {
        printf("\n-- Principal menu --\n");
        printf("\n1. Filling\n2. Displaying\n3. Usual operations \n4. Analysis and statistics\n0. Exit\n");
        choice = valid_input(0, 5);
        // must create a cdf before any action
        if (choice != 1 && cdf == NULL) {
            choice = -1;
        }
        switch (choice) {

            case -1: {
                printf("You must create a dataframe first!\n");
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
                        printf("You have already created a dataframe!\n");
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
                    case 4: {
                        break;
                    }
                }
                break;
            }
            case 3: {
                printf("1. Add a row of values at the end of the CDataframe\n2. Delete a row of values from the CDataframe\n3. Add a column to the CDataframe"
                       " \n4. Delete a column from the CDataframe\n5. Rename the title of a column in the CDataframe \n6.Check the existence of a value (search) in the CDataframe"
                       "\n7. Access/replace the value in a CDataframe cell using its row and column number\n8. Display column names\n9.Go back to the principal menu\n");
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
                        delete_line_cdataframe(cdf, valid_input(0, longest_col(cdf)));
                        break;
                    }
                    case 3: // Add a column to the CDataframe
                    {
                        // debug ----------------------
                        for(int i=0; i<3; i++){
                            printf("\t-- %d",cdftype[i]);
                        }
                        printf("\n");
                        //-
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
                    case 6: // Check the existence of a value (search) in the CDataframe
                    {
                        int res;
                        ENUM_TYPE cdftype_2[] = {};
                        choose_type(cdftype_2, 1);
                        void* value;
                        input_value(cdftype_2[0], &value);
                        res = equal(cdf,cdftype_2[0],value);
                        if (res){
                            printf("There are %d cells with this value.\n", res);
                        }
                        else {
                            printf("There is no cells with this value in the dataframe.");
                        }
                        break;
                    }
                    case 7: // Access/replace the value in a Ccdf cell using its row and column number
                    {
                        //access_replace(cdf);
                        break;
                    }
                    case 8: // Display column names
                    {
                        //print_col_names(cdf);
                        break;
                    }
                    case 9:{
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
                        printf("There are %d rows in the dataframe.\n", longest_col(cdf));
                        break;
                    }
                    case 2: // Display the number of columns
                    {
                        printf("There are %d columns in the dataframe.\n", cdataframe_size(cdf));
                        break;
                    }
                    case 3: // Display the number of cells equal to x (x given as parameter)
                    {
                        void* value;
                        int res;
                        ENUM_TYPE cdftype_1[] = {};
                        choose_type(cdftype_1, 1);
                        printf("chosen type: %d", cdftype_1[0]);
                        input_value(cdftype_1[0], &value);
                        printf("type after input_val %d\n", cdftype_1[0]);
                        res = equal(cdf,cdftype_1[0],value);
                        printf("\nres:%d", res);
                        if (res) {
                            printf("There are %d cells with the value %d.\n", res, value);
                        } else {
                            printf("%d is not in the dataframe.", value);
                        }
                        break;
                    }
                    case 4: // Display the number of cells containing a value greater than a chosen value
                    {
                        int value;
                        //value = input_number();
                        //printf("There are %d cells with greater values than %d.\n", greater(cdf, value),value);
                        break;
                    }
                    case 5: // Display the number of cells containing a value less than a chosen value
                    {
                        int value;
                        //value = input_number();
                        //printf("There are %d cells with smaller values than %d.\n", smaller(cdf, value), value);
                        break;
                    }
                    case 6: {
                        break;
                    }

                }
                break;
            }
        }
    }
    while (choice != 0);
    /*
    if (cdf!=NULL){
        delete_cdataframe(&cdf);
    }*/

/*
    //TEST with number ok
    COLUMN *mycol = create_column(INT, "My column");
    int a = 1, b = 2,c = 5, d = 7, e = 4;
    insert_value(mycol, &b);
    insert_value(mycol, &c);
    insert_value(mycol, &a);
    insert_value(mycol, &d);
    // should NULL always be at the end of the list?
    //insert_value(mycol, NULL);
    mycol->valid_index = 0;
    printf("not sorted (YES:-1) ? : %d\n", search_value_in_column(mycol, &d));
    printf("Column content before sorting : \n");
    print_col(mycol);
    sort(mycol, ASC);
    // if the direction of sorting change then valid_index = -1 ?
    printf("\n");;
    printf("Column content after sorting : \n");
    print_col_by_index(mycol);

    insert_value(mycol,&e);
    update_index(mycol);
    sort(mycol, ASC);
    printf("\n");
    printf("Column content after an add + sorting : \n");
    print_col_by_index(mycol);

    int r = 100;
    printf("\nfound 7 in col (YES : 1) ? : %d\n", search_value_in_column(mycol, &d));
    printf("not found 100 in col (NO: 0) ? : %d", search_value_in_column(mycol, &r));

    delete_column(&mycol);
    */

    /*
    //TEST WITH STRING
    COLUMN *mycol = create_column(STRING, "My column");
    char a[]= "Bravo", b[] = "Tango", c[] = "Zulu", d[] = "Lima", e[]="Yuzu";

    //COLUMN *mycol = create_column(CHAR, "My column");
    //char a = 'A', b = 'Z', c= 'Y', d = 'E', e='L';
    insert_value(mycol, b);
    insert_value(mycol, c);
    insert_value(mycol, a);
    insert_value(mycol, d);
    mycol->valid_index = 0;
    printf("Column content before sorting : \n");
    print_col(mycol);
    sort(mycol, DESC);
    // if the direction of sorting change then valid_index = -1 ?
    printf("\n");

    printf("Column content after sorting : \n");
    print_col_by_index(mycol);

    insert_value(mycol,e);
    update_index(mycol);
    sort(mycol, DESC);
    //for(int i=0; i<mycol->size;i++){
        //printf("%d\n",mycol->index[i]);
    //}
    printf("\n");
    printf("Column content after an add + sorting : \n");
    print_col_by_index(mycol);

    printf("\ntest search value\n");
    char r[] ="OK" ;
    printf("'Bravo' in col (YES : 1) ? : %d\n", search_value_in_column(mycol, &a));
    printf("'OK' in col (NO: 0) ? : %d", search_value_in_column(mycol, &r));
    delete_column(&mycol);*/
    
    /*printf("%s\n", mycol->title);
    for (int i = 0; i < mycol->size; i++) {
        printf("-%c-\n", *((char *)mycol->data[i])); //convert back
    }
    printf("--------");
    COLUMN *mycol1 = create_column(INT, "New column");
    for(int i = 0 ; i < 10 ; i++){
        insert_value(mycol1, &i);
    }
    printf("\n%s\n", mycol1->title);
    for(int i = 0 ; i < 10; i++){
        printf("%d\t", *((int *)(mycol1->data[i])));
    }*/

        /*
    ENUM_TYPE cdftype [] = {INT,INT,INT};
    CDATAFRAME *cdf = create_cdataframe(cdftype, 3);
    LNODE * tmp = (LNODE *) cdf->head;
    for (int i=0; i<3; i++){
        printf("%s\n", ((COLUMN*)tmp->data)->title);
        tmp = tmp->next;
    }
    hard_fill_dataframe(cdf);
    LNODE * tmp1 = (LNODE *) cdf->head;
    //print_col((COLUMN *) ((COLUMN *) tmp1->data));
    printf("\n--- Dataframe --- \n");
    display_dataframe(cdf);
    char t[] ="a";
    delete_column_by_name(cdf, t);
    display_dataframe(cdf);
    delete_cdataframe(&cdf);*/

    return 0;
}