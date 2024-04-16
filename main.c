#include <stdio.h>
#include <stdlib.h>

#include "column.h"
#include "cdataframe.h"


int main() {
    /*
    COLUMN *mycol = create_column("My column");
    insert_value(mycol, 52);
    insert_value(mycol, 44);
    insert_value(mycol, 15);
    print_col(mycol);
    delete_column(&mycol);
    */
    int choice = 0;
    DATAFRAME *dataframe = NULL;
    do {
        printf("-- Principal menu --\n");
        printf("\n1. Filling\n2. Displaying\n3. Usual operations \n4. Analysis and statistics\n5. Exit\n");
        choice = valid_input(1, 5);
        if (choice != 1 && dataframe == NULL) {
            choice = 0;
        }
        switch (choice) {
            case 0: {
                printf("You must create a dataframe first!\n");
                break;
            }
            case 1: {
                printf("1.Creation of an empty CDataframe \n2. Filling in the CDataframe with an input \n3. Hard filling of the CDataframe\n4.Go back to the principal menu\n");
                choice = valid_input(1, 4);
                switch (choice) {
                    case 1://Creation of an empty CDataframe
                    {
                        int phys_size;
                        printf("How many columns do you want in the Dataframe? (max %d)", REALOC_SIZE);
                        phys_size = valid_input(1, REALOC_SIZE);
                        dataframe = create_dataframe(phys_size);
                        break;
                    }
                    case 2: // Filling in the CDataframe with an input
                    {
                        is_dataframe(dataframe);//check if the dataframe has allocated memory
                        fill_dataframe(dataframe);
                        break;
                    }
                    case 3: // Hard filling of the CDataframe
                    {
                        is_dataframe(dataframe);
                        hard_fill_dataframe(dataframe);
                        break;
                    }
                    case 4: {
                        break;
                    }
                }
                break;
            }
            case 2: {
                printf("1. Display the entire CDataframe \n2. Display a part of the CDataframe rows according to a chosen limit\n3. Display a part of the columns of the CDataframe according to a limit supplied by the user\n4.Go back to the principal menu\n");
                choice = valid_input(1, 4);
                switch (choice) {
                    case 1: // Display the entire CDataframe
                    {
                        display_dataframe(dataframe, 0, 0);
                        break;
                    }
                    case 2: // Display a part of the CDataframe rows according to a chosen limit
                    {
                        int nb_lines = 0;
                        printf("How many lines do you want to display?");
                        nb_lines = valid_input(1, longest_col(dataframe));
                        display_dataframe(dataframe, nb_lines, 0);
                        break;
                    }
                    case 3: // Display a part of the columns of the CDataframe according to a limit supplied by the user
                    {
                        int nb_col = 0;
                        printf("How many columns do you want to display?");
                        nb_col = valid_input(1, longest_col(dataframe));
                        display_dataframe(dataframe, 0, nb_col);
                        break;
                    }
                    case 4: {
                        break;
                    }
                }
                break;
            }
            case 3: {
                printf("1. Add a row of values to the CDataframe\n2. Delete a row of values from the CDataframe\n3. Add a column to the CDataframe"
                       " \n4. Delete a column from the CDataframe\n5. Rename the title of a column in the CDataframe \n6. • Check the existence of a value (search) in the CDataframe"
                       "\n7. Access/replace the value in a CDataframe cell using its row and column number\n8. Display column names\n9.Go back to the principal menu\n");
                choice = valid_input(1, 9);
                switch (choice) {
                    case 1: // Add a row of values to the CDataframe
                    {
                        add_line_dataframe(dataframe);
                        break;
                    }
                    case 2: // Delete a row of values from the CDataframe
                    {
                        printf("Enter the index of the row to remove");
                        delete_line_dataframe(dataframe, valid_input(0, smallest_col(dataframe)));
                        break;
                    }
                    case 3: // Add a column to the CDataframe
                    {
                        int result;
                        char* title;
                        choose_title(title);
                        result = add_column(dataframe, title);
                        if(result){
                            printf("Column successfully added\n");
                        }else{
                            printf("Can't add a column: no more place in memory\n");
                        }
                        break;
                    }
                    case 4: // Delete a column from the CDataframe
                    {
                        //delete_col_dataframe();
                        break;
                    }
                    case 5: // Rename the title of a column in the CDataframe
                    {
                        //action
                        break;
                    }
                    case 6: // Check the existence of a value (search) in the CDataframe
                    {
                        //action
                        break;
                    }
                    case 7: // Access/replace the value in a CDataframe cell using its row and column number
                    {
                        //action
                        break;
                    }
                    case 8: // Display column names
                    {
                        //print_col_names(dataframe);
                        break;
                    }
                    case 9: {
                        break;
                    }
                }
                break;
            }
            case 4: {
                printf("1. Display the number of rows\n2. Display the number of columns\n3. Display the number of cells equal to a chosen value"
                       " \n4. Display the number of cells containing a value greater than a chosen value\n5. Display the number of cells containing a value less than a chosen value \n6.Go back to the principal menu\n");
                choice = valid_input(1, 6);
                switch (choice) {
                    case 1: // Display the number of rows
                    {
                        //action
                        break;
                    }
                    case 2: // Display the number of columns
                    {
                        //action
                        break;
                    }
                    case 3: // Display the number of cells equal to x (x given as parameter)
                    {
<<<<<<< HEAD
                        int value = 0, cpt = 0;
                        value = input_number();
                        if (cpt = equal(dataframe, value)) {// return 1 if value is in the dataframe
                            printf("There are %d cells with the value %d.\n", cpt, value);
                        } else {
                            printf("The value %d is not in the dataframe.");
                        }
=======
                        //action
>>>>>>> parent of a274db9 (Verif the type of the input)
                        break;
                    }
                    case 4: // Display the number of cells containing a value greater than a chosen value
                    {
                        int value = 0;
                        value = input_number();
                        printf("There are %d cells with greater values than %d.\n", greater(dataframe, value),
                               value);
                        break;
                    }
                    case 5: // Display the number of cells containing a value less than a chosen value
                    {
                        int value = 0;
                        value = input_number();
                        printf("There are %d cells with smaller values than %d.\n", smaller(dataframe, value),
                               value);
                        break;
                    }
                    case 6: {
                        break;
                    }

                }
                break;

                }
        }
    }while (choice != 5);
    return 0;
}