#include <stdio.h>
// CSD4817 - Marsel Senka
/**
 * 
 * @param arr Sudoku array
 * @param row Row to check
 * @return int 0 if okay, 1 if duplicate values.
 */
int checkRow(int arr[9][9], int row) {
    int i,j;
    int a[] = {0,0,0,0,0,0,0,0,0,0};            // Temporary array so we check for duplicates
    for(i=0;i<9;i++) {
        int n = arr[row][i];
        if(n<=0 || n>9) {
            return 1;
        }
        if(a[n]==0) {
            a[n]=1;
        } else {
            return 1;
        }
    }
    return 0;
}
/**
 * 
 * @param arr Sudoku array.
 * @param column Column we are looking into.
 * @return int 0 if okay, 1 if duplicate found.
 */
int checkColumn(int arr[9][9], int column) {
    int i,j;
    int a[] = {0,0,0,0,0,0,0,0,0,0};        // Temporary array so we check for duplicates
    for(i=0;i<9;i++) {
        int n = arr[i][column];
        if(n<=0 || n>9) {
            return 1;
        }
        if(a[n]==0) {
            a[n]=1;
        } else {
            return 1;
        }
    }
    return 0;
}

/**
 * 
 * @param arr Sudoku Array.
 * @param block We are looking into
 * @return int 0 if okay, 1 if duplicate found.
 */
int checkBlocks(int arr[9][9],int block) {
    int i,j;
    int a[] = {0,0,0,0,0,0,0,0,0,0};        // Temporary array so we check for duplicates

    int row = (int)(block/3)*3;             // Finding where the row starts on given block.
    int column = (int)(block%3)*3;          // Finding where the column starts on given block.
    for(i=0;i<3;i++) {
        for(j=0;j<3;j++) {
            int n = arr[row+i][column+j];   // Navigation through the 3X3 block.
            if(n<=0 || n>9) {
                return 1;
            }
            if(a[n]==0) {
                a[n]=1;
            } else {
                return 1;
            }

        }
    }
    return 0;
}
/**
 * 
 * @param arr Array of duplicate status we will be printing out. 
 * @param s either rows,columns,or blocks.
 */
void printInvalid(int arr[9],char* s) {
    int i;
    printf("Invalid %s:",s);
    for(i=0;i<9;i++) {
            if(arr[i]==1) {
                printf(" %d",i+1);
            }            
    }
}

void main() {

    int arr[9][9];
    int rows[] = {0,0,0,0,0,0,0,0,0};
    int columns[] = {0,0,0,0,0,0,0,0,0};
    int blocks[] = {0,0,0,0,0,0,0,0,0};
    int i,j;
    int num;
    for(i=0;i<9;i++) {
        for(j=0;j<9;j++) {
            scanf("%d",&num);
            arr[i][j] = num;
        }
    }
    for(i=0;i<9;i++) {
        rows[i] = checkRow(arr,i);
        columns[i] = checkColumn(arr,i);
        blocks[i] = checkBlocks(arr,i);
    }

    // 3 flags in order to see whether there are duplicates or not.
    int check_row=0;           
    int check_column=0;
    int check_block=0;
    for(i=0;i<9;i++){
        if(rows[i]==1){
            check_row=1;
        }
        if(columns[i]==1){
            check_column=1;
        }
        if(blocks[i]==1){
            check_block=1;
        }
    }
    // Deciding depending on the flag value,whether to print or not
    if(check_row==1) {
        printInvalid(rows,"rows");
        printf("\n");                   // new line at the end because the tests are weird.
    }
    if(check_column==1) {
        printInvalid(columns,"columns");
        printf("\n");
    }
    if(check_block==1) {
        printInvalid(blocks,"blocks");
        printf("\n");
    }
    if(check_row==0 && check_block==0 && check_column==0) {
        printf("OK\n");                // Period.
    }


}
