#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// CSD4817 - Marsel Senka

/**
 * 
 * A void function that reverses a string.
 * @param s String parameter.
 */
void reverse(char* s) {
    int i;
    int n = strlen(s);

    for(i=0;i<(n/2);i++) {
        char temp = s[i];
        s[i] = s[n-i-1];
        s[n-i-1] = temp;
    }

    return;
}
void main() {
    int n;
    scanf("%d",&n);
    if(n<=0) {                  // Edge case
        return;
    }
    char s[21];
    char words[630];            // 21 * 30 , worst case scenario on size.
    int i = 0;                  // Counter of words that must be read.
    int j;                  
    int k=0;                    // Index on the 1D array.
    words[0] = '\0';
    while(scanf("%s",s) != EOF && i<n) {      // Read until we meet the correct amount of words.
        for(j = 0; j<strlen(s); j++ ) {
            words[k]=s[j];
            k++;
        }
        i++;
    }
    words[k]='\0';              // Null terminates a string.

    char* words_rev = malloc(k);                // Allocating k space where the reverse word will be stored.
    strncpy(words_rev,words,k);                 // Copying k chars.
    reverse(words_rev);                         // calls reverse() function.
    if(strcmp(words_rev,words)==0) {            // Decides whether its palindrome or not.
        printf("Input is a palindrome\n");     
    } else {
        printf("Input is not a palindrome\n");
    }


}