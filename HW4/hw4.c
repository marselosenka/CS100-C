#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * @brief Function to Shuffle the directions that we will be visiting.
 * 
 * @param directions 
 */
void getShuffledDirections(int* directions) {
    for (int i = 0; i < 4; i++) {
        directions[i] = i;
    }
    for (int i = 3; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = directions[i];
        directions[i] = directions[j];
        directions[j] = temp;
    }
    return;
}

/**
 * @brief Checks whether the cell is valid
 * 
 * @param maze a 2D array which contains X's 
 * @param n rows
 * @param m columns
 * @param newR row to check
 * @param newC column to check
 * @return int valid or invalid 
 */
int isValidCell(char** maze, int n, int m, int newR, int newC) {
    if ((n * m) % 2 == 1) {
        if (newR > 0 && newR < n - 1 && newC > 0 && newC < m - 1 && maze[newR][newC] == 'X') {
            return 1;
        } else {
            return 0;
        }
    } else {
        if (newR > 0 && newR < n-1 && newC > 0 && newC < m-1 && maze[newR][newC] == 'X') {
            return 1;
        } else {
            return 0;
        }
    }
    return 0;
}

/**
 * @brief Breaks a wall
 * 
 * @param maze a 2D array which contains X's 
 * @param n rows
 * @param m columns
 * @param dir direction
 * @param dx row direction
 * @param dy column direction
 */
void breakWall(char** maze, int r, int c, int dir,int* dx ,int* dy) {
    maze[r + dx[dir]][c + dy[dir]] = ' ';
}

/**
 * @brief Recursive function that will be solving the Maze
 * 
 * @param maze a 2D array which contains X's 
 * @param n rows of maze.
 * @param m columns of maze.
 * @param r row we are at right now.
 * @param c coulmn we are at right now.
 */
void checkGenerateMaze(char** maze, int n, int m, int r, int c) {
    srand(time(NULL));

    // directions
    int dirForX[4] = {1, 0, 0, -1}; 
    int dirForY[4] = {0, -1, 1, 0}; 

    // shuffle
    int directions[4];
    getShuffledDirections(directions);
    for (int i = 0; i < 4; i++) {
        int dir = directions[i];
        int newR = r + 2 * dirForX[dir];
        int newC = c + 2 * dirForY[dir];

        if (isValidCell(maze, n, m, newR, newC)) {
            breakWall(maze, r, c, dir, dirForX,dirForY);
            maze[newR][newC] = ' ';
            checkGenerateMaze(maze, n, m, newR, newC);
        }
    }
}
int main(int argc,char *argv[]) {
    if(argc != 3) {
        printf("Expected two arguments, you entered: %d ",argc);
    }
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    
    char **maze = (char**)malloc(n*sizeof(char*));
    if(maze == NULL) {
        printf("Failed allocating memory!");
        return -1;
    }

    for(int i=0; i < n;i++) {
        maze[i] = (char*)malloc(m*sizeof(char));
    }

    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            maze[i][j] = 'X';
        } 
    }

    maze[0][1] = ' ';
    maze[1][1] = ' ';
    checkGenerateMaze(maze,n,m,1,1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%c", maze[i][j]);
        }
        printf("\n");
    }
    return 0;
}