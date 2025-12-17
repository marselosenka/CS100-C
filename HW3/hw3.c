#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * CSD4817 - Marsel Senka
 * HW3 
 */

typedef struct list_node {
    int n;
    char* name;
    int year;
    float bet;
    struct list_node *next;
} movies; 


/**
 * Handles --list-all command line paramater.
 * Output: "List is empty!" when there are no movies.
 * @param root Root of the linked-list.
 */
void listALL(movies *root) {
    movies *temp = root;
    if(temp==NULL) {
        printf("List is empty!\n");
    } else {
        printf("The available movies are: \n");
        while (temp != NULL) {
            printf("%s ",temp->name);
            printf("%d ",temp->year);
            printf("%f ",temp->bet);
            printf("\n");
            temp = temp->next;
        } 
    }
}


/**
 * Handles "--insert". Inserts a new movie on the list
 * 
 * @param argc number of command line arguments.
 * @param argv Array of command-line arguments, [title,year of creation,bets].
 * @param root pointer to a pointer of the first element of our linked list.
 * @param current pointer to a pointer on the last element of our linked list.
 */
void insert(int argc,char **argv,movies **root,movies **current) {
    {

            movies *temp = (movies*) malloc(sizeof(movies));
            char movie[32] = "";
            int i;
            for(i = 2; i < argc; i++ ) {
                if(atoi(argv[i]) < 1800 ) { // So movies like "Shrek: 2" "The 100" can be accepted. 
                    if(strlen(movie)>0) {
                        strcat(movie , " " );
                    }
                    strcat(movie,argv[i]);
                } else {
                    break;
                }
            }
            
            temp->n = strlen(movie)+1;
            temp->name = strdup(movie);
            if( (i >= argc) || (i+1 >= argc) ) {
                printf("Wrong parameters!\n");
                return;
            }
            temp->year = atoi(argv[i]);
            temp->bet = atof(argv[i+1]);
            temp->next = NULL;

            if(*root == NULL) {
                *root = temp;
                *current = temp;
            } else {
                (*current)->next = temp;
                *current = temp;
            }
            printf("Added a new movie!\n");
        }
}


/**
 * Handles "--delete". Deletes a movie (node) from our linked list.
 * 
 * @param argc number of command line arguments.
 * @param argv Array of command-line arguments, [title].
 * @param root pointer to a pointer of the first element of our linked list.
 */
void delete(int argc,char **argv,movies **root) {
    movies *temp = *root;
    movies *prev = NULL;
    char movieName[32] = "";

    if(argc>3) {            // For movie names with more than 1 word, like "Shrek 2" etc
        int i;
        for(i=2;i<argc;i++) {
            if(strlen(movieName)>0) {
                strcat(movieName , " " );
            }
            strcat(movieName,argv[i]);
        }
    } else {
        strcat(movieName,argv[2]);
    }
    while(temp != NULL) {
        if(strcmp(temp->name,movieName)==0) { // Compares the node's name with the parameter name.
            if(prev == NULL) {              // Case if root is the node requested to be deleted.
                *root = temp->next;
                free(temp->name);   // Clears name.
                free(temp);         // Clears root.
                printf("Movie deleted successfully!\n");
                return;
            } else {                        // Any else.
                prev->next = temp->next;
                free(temp->name);   // Clears name.
                free(temp);         // Clear node.
                printf("Movie deleted successfully!\n");
                return;
            }
        } else {
            prev = temp;
            temp = temp->next;
        }
    }
    printf("Movie not found!");

}


/**
 * Handles "--add". Updates the bet of a movie.
 * 
 * @param argc Number of command line arguments.
 * @param argv Array of command-line arguments, [title, += amount].
 * @param root Pointer to a pointer of the first element of our linked list.
 */
void add(int argc,char **argv,movies **root) {
    movies *temp = *root;
    movies *prev = NULL;
    while( temp != NULL ) {
        if(strcmp(temp->name,argv[2])==0) {     // Comparison of node's name to the parameter name.
            temp->bet += atoi(argv[3]);         // Converts argv[3] to a number, and adds it to the current bet.
            printf("New value of movie %s is %f \n \n",argv[2],temp->bet);
            return;
        } else {
            temp = temp->next;
        }
    }
    printf("Movie not found!");

}


/**
 * Handles "--reset". Removes all movies from our movie file.
 * 
 */
void reset() {
    FILE *f = fopen("movies.dat","wb");     // Opens and closes the file, which resets it.
    fclose(f);
    printf("File was reset successfully!\n");
}


/**
 * Updates the movies.dat file , exports our linked-list.
 * 
 * @param root Pointer to a pointer of the first element of our linked list.
 * @param filename 
 */
void exportList(movies **root,char* filename) {
    FILE *f = fopen(filename,"wb");

    if(f == (FILE*)NULL) {
        printf("Couldn't open file!\n");
        return;
    }
    movies *temp = *root;
    while (temp != NULL) {
        fwrite(&temp->n, sizeof(int), 1, f);
        fwrite(temp->name, sizeof(char), temp->n, f);
        fwrite(&temp->year, sizeof(int), 1, f);
        fwrite(&temp->bet, sizeof(float), 1, f);
        
        temp = temp->next;
    }
    fclose(f);
}

/**
 * Handles "--list-after". Displays all the movies that were released after the specified year.
 * 
 * @param argv Array of command-line arguments, [year].
 * @param root Pointer to a pointer of the first element of our linked list. 
 */
void listAfter(char **argv,movies **root) {
    movies *temp = *root;
    int counter = 0;
    while(temp != NULL) {
        if( atoi(argv[2]) < temp->year ) {
            printf("%s ",temp->name);
            printf("%d ",temp->year);
            printf("\n");
            counter++;
        }
        temp = temp->next;
    }
    if(counter==0) {
        printf("No movies were released after that year!\n");
    }
}

/**
 * BubbleSort algorithm that sorts the linked-list in an ascending order.
 * 
 * @param root Pointer to a pointer of the first element of our linked list.
 */
void sort(movies **root) {
    movies *temp;
    movies *current;
    movies *prev;
    
    int swap=1;     // To implement the bubble sort logic.
    while(swap) {
        swap = 0;   // Flag
        temp = *root;
        prev = NULL;
        while (temp->next != NULL) {
            current = temp->next;
            if (strcmp(temp->name, current->name) > 0) {
                if (prev == NULL) {
                    *root = current; // If it's the first node.
                } else {
                    prev->next = current;   // If it's not the first node.
                }
                temp->next = current->next;     // Updates the next pointers.
                current->next = temp;

                prev = current;     // New prev, since it's been swapped.
                swap = 1;   // Flag to decide when to stop.
            } else {
                prev = temp;
                temp = temp->next;
            }
        }
    }
}

/**
 * Configuration of the command line arguments
 * 
 * @param argc Number of command line arguments.
 * @param argv Array of command-line arguments.
 * @param root Pointer of the first element of our linked list.
 * @param current Pointer of the last element of our linked list.
 * @return int Debug handling, whether an error has occured 
 */

int configure_mode(int argc,char **argv,movies *root,movies **current) {
    if (strcmp(argv[1],"--insert") == 0 ) {             // Handling --insert

        if (argc<5) {
            printf("Missing arguments in --insert!\n");
            return -1;
        } else {
            insert(argc,argv,&root,current);
            exportList(&root,"movies.dat");
            return 1;
        }

    } else if ( strcmp(argv[1],"--delete")==0 ) {       // Handling --delete
            delete(argc,argv,&root);
            exportList(&root,"movies.dat");
    } else if ( strcmp(argv[1],"--add")==0 ) {          // Handling --add
        if (argc>4) {
            return -3;
        } else {
            add(argc,argv,&root);
            exportList(&root,"movies.dat");
        }
    } else if( strcmp(argv[1],"--list-after") == 0) {       // Handling --list-after
        if (argc>3) {
            return -4;
        } else {
            listAfter(argv,&root);
        }
    } else if( strcmp(argv[1],"--reset") == 0 ) {           // Handling --reset
        exportList(&root,"movies.dat");
        reset();
    } else if( strcmp(argv[1],"--list-all") == 0 ) {        // Handling --list-all
        listALL(root);
    } else if( strcmp(argv[1],"--sort")==0 ) {              // Handling --sort
        sort(&root);
        exportList(&root,"movies.dat");
    } else {
        return 0;   // Parameters are wrong.
    }
    
}
/**
 * Initializes linked list. When program is started movies are read from .dat file and 
 * initialized as a linked list.
 * 
 * @param root Pointer to a pointer of the first node of our linked list.
 * @param current Pointer to a pointer of the last added node of our linked list. 
 * @param filename Name of the file (movie.dat)
 */
void initList(movies **root,movies **current,char* filename) {
    FILE *f = fopen(filename,"r");

    if(f == (FILE*)NULL) {
        printf("File didn't open!\n");
        return;
    }
    while(1) {

        movies *temp = (movies*) malloc(sizeof(movies));
        if(temp==NULL) {                            // Case where memory was not allocated.
            printf("Not enough memory!\n");
            return;
       }
        if(fread(&temp->n, sizeof(int), 1, f)!=1) {         // Case where the file is empty.
            return;
        }
        

        temp->name = (char*) malloc(temp->n * sizeof(char));    // Reading from the binary file.
        fread(temp->name, sizeof(char), temp->n, f);
        fread(&temp->year, sizeof(int), 1, f);
        fread(&temp->bet, sizeof(float), 1, f);
        temp->next = NULL;
        
        if(*root == NULL) {
            *root = temp;
            *current = temp;
        } else {
            (*current)->next = temp;
            *current = temp;
        }
    }
    fclose(f);
}

int main(int argc, char **argv) {
    movies *root = NULL;
    movies *current = NULL;
    initList(&root,&current,"movies.dat");      // Init of linked list from file contains.
    if(argc > 1) {
        configure_mode(argc,argv,root,&current);    // Translating the command line arguments.
    } else {
        printf("Wrong arguments!");
    }
    return 0;
}

