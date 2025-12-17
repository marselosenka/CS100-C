#include <stdio.h>
#include <stdlib.h>
int main() {
    int a;
    printf("Enter a number higher than 3\n");
    scanf("%d",&a);
    if( a <= 3 ) {
        printf("Number must be higher than 3\n");
        exit(0);
    }
    int b = a/2; 
    int c = 0;
    for(int i=0;i<a;i++) {
        printf("*");
        if(b>=1) {
            for(int j=0;j<b-1;j++) {
            printf(" ");
            
        }
        printf("*");
        b--;
        } else {
            c++;
            for(int i=0;i<c;i++) {
                printf(" ");
            }
            printf("*");
        }
        printf("\n");
    }
}