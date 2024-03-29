#include <stdio.h>
#include <stdlib.h>

#include "column.h"
#include "cdataframe.h"

int main(){
    printf("hello");

    COLUMN *mycol = create_colum("My column");
    printf("%s", mycol->title);
    /*
   int val = 5;
   if (insert_value(mycol, val)){
       printf("Value added successfully to my column\n");
   }
   else{
       printf("Error adding value to my column\n");
   }
*/
    return 0;
}