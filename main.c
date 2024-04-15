#include <stdio.h>
#include <stdlib.h>

#include "column.h"
#include "cdataframe.h"


int main(){
    /*
    COLUMN *mycol = create_column("My column");
    insert_value(mycol, 52);
    insert_value(mycol, 44);
    insert_value(mycol, 15);
    print_col(mycol);
    delete_column(&mycol);
    */
    int choice = 0;
    DATAFRAME* dataframe=NULL;
    do {
        printf("1. Filling\n2. Displaying\n3. Usual operations \n4. Analysis and statistics\n5. Exit\n");
        choice = valid_input(5);
        switch (choice) {
            case 1: {
                printf("1.Creation of an empty CDataframe \n2. Filling in the CDataframe with an input \n3. Hard filling of the CDataframe\n");
                choice = valid_input(3);
                switch (choice) {
                    case 1://Creation of an empty CDataframe
                    {
                        int phys_size;
                        printf("How many columns do you want in the Dataframe? (max %d)", REALOC_SIZE);
                        phys_size = valid_input(REALOC_SIZE);
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
                        dataframe = is_dataframe(dataframe);
                        hard_fill_dataframe(dataframe);
                        break;
                    }

                }
                break;
            }
            case 2: {
                printf("1.Display the entire CDataframe \n2.Display a part of the CDataframe rows according to a chosen limit\n3. Display a part of the columns of the CDataframe according to a limit supplied by the user\n");
                choice = valid_input(3);
                switch (choice) {
                    case 1: // Display the entire CDataframe
                    {
                        display_dataframe(dataframe, 0,0);
                        break;
                    }
                    case 2: // Display a part of the CDataframe rows according to a chosen limit
                    {
                        int nb_lines = 0;
                        printf("How many lines do you want to display?");
                        nb_lines = valid_input(longest_col(dataframe));
                        display_dataframe(dataframe, nb_lines, 0);
                        break;
                    }
                    case 3: // Display a part of the columns of the CDataframe according to a limit supplied by the user
                    {
                        int nb_col = 0;
                        printf("How many columns do you want to display?");
                        nb_col = valid_input(longest_col(dataframe));
                        display_dataframe(dataframe, 0, nb_col);
                        break;
                    }

                }
                break;
            }
            case 3: {
                printf("1. Add a row of values to the CDataframe\n2. Delete a row of values from the CDataframe\n3. Add a column to the CDataframe"
                       " \n4. Delete a column from the CDataframe\n5. Rename the title of a column in the CDataframe \n6. • Check the existence of a value (search) in the CDataframe"
                       "\n7. Access/replace the value in a CDataframe cell using its row and column number\n8. Display column names");
                choice = valid_input(8);
                switch (choice) {
                    case 1: // Add a row of values to the CDataframe
                    {
                        //action
                        break;
                    }
                    case 2: // Delete a row of values from the CDataframe
                    {
                        //action
                        break;
                    }
                    case 3: // Delete a row of values from the CDataframese 3:
                    {
                        //action
                        break;
                    }
                    case 4: // Delete a column from the CDataframe
                    {
                        //action
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
                        //action
                        break;
                    }
                }
                break;
            }
            case 4: {
                printf("1. Display the number of rows\n2. Display the number of columns\n3. Display the number of cells equal to a chosen value"
                       " \n4. Display the number of cells containing a value greater than a chosen value\n5. Display the number of cells containing a value less than a chosen value \n");
                choice = valid_input(8);
                switch (choice) {
                    case 1: // Display the number of rows
                    {
                        printf("There are %d rows in the dataframe.\n", longest_col(dataframe));
                        break;
                    }
                    case 2: // Display the number of columns
                    {
                        printf("There are %d columns in the dataframe.\n", dataframe->ls);
                        break;
                    }
                    case 3: // Display the number of cells equal to x (x given as parameter)
                    {
                        int value =0;
                        printf("Enter the value to search in the data frame: ");
                        scanf("%d", &value);
                        printf("There are %d cells with the value %d.\n", equal(dataframe, value), value);
                        break;
                    }
                    case 4: // Display the number of cells containing a value greater than a chosen value
                    {
                        //action
                        break;
                    }
                    case 5: // Display the number of cells containing a value less than a chosen value
                    {
                        //action
                        break;
                    }

                }
                break;
            }
        }
    }while(choice !=5);

    return 0;
}