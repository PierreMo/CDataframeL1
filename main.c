#include <stdio.h>
#include <stdlib.h>

#include "column.h"
#include "cdataframe.h"

int main(){
    COLUMN *mycol = create_column("My column");
    insert_value(mycol, 52);
    insert_value(mycol, 44);
    insert_value(mycol, 15);
    print_col(mycol);
    delete_column(&mycol);

    return 0;
}