#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// CSD4817 - Marsel Senka

/**
 * Creates an N-sized 2D array,where each row is one word.
 * 
 * @return int 
 */
int main() {
    int n;
    int i,j;
    scanf("%d",&n);
    if(n<=0) {          // Edge Case
        return 0;
    }
    char** words = malloc(n*sizeof(char*));     // Allocates memory for the array. 
    for(i=0;i<n;i++) {
        words[i] = malloc(32*sizeof(char));     // Allocates memory for each word of the array.
        scanf("%s",words[i]);
    }
    if(n==1) {           // Edge Case
        printf("%s",words[0]);
        printf("\n");
        return 0;
    }

    int max=0;
    char* max_word;
    for(i=0;i<n;i++) {           // Going through all the words.
        char* w = words[i];
        int times=0;
        // strcpy(words[i],w);
        for(j=n-1;j>i;j--) {    // Compares each word with all the others, starting from the end.
            if(strcmp(w,words[j])==0) {
                times++;
            }
        }
        if (times>max) {        // Comparison with previous max values.
            max_word = words[i];
            max=times;
        }

    }

    printf("%s",max_word);
    printf("\n");
    return 0;

}