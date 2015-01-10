#include <stdio.h>
#include <stdlib.h>

#define ROW 7
#define COL 7
#define START_ROW 3
#define START_COL 0
#define END_ROW 4
#define END_COL 6

struct Space{
    int row;
    int col;
};

int isPrev(struct Space *path, int pathLength, int direction){
    int i;
    if(pathLength == 1)
        return 0;

    for(i=1; i<pathLength; i++){
        if(direction == 0){
            if(path[pathLength-1].row-1 != path[i-1].row || path[pathLength-1].col != path[i-1].col)
                continue;
            else
                return 0;
        }
        else if(direction == 1){
            if(path[pathLength-1].row+1 != path[i-1].row || path[pathLength-1].col != path[i-1].col)
                continue;
            else
                return 0;
        }
        else if(direction == 2){
            if(path[pathLength-1].row != path[i-1].row || path[pathLength-1].col-1 != path[i-1].col)
                continue;
            else
                return 0;
        }
        else if(direction == 3){
            if(path[pathLength-1].row != path[i-1].row || path[pathLength-1].col+1 != path[i-1].col)
                continue;
            else
                return 0;
        }
    }

    return 1;
};


void move(struct Space *path, int pathLength, int maze[][COL]){
    
    if(path[pathLength-1].row == END_ROW && path[pathLength-1].col == END_COL){
        int i;
        printf("---Path---\n");
        printf("PathLength = %d\n", pathLength);
        for(i=0; i<pathLength; i++)
            printf("(%d, %d)\n", path[i].row, path[i].col);
        printf("----------\n\n");
        return;
    }
    else{
        if(path[pathLength-1].row-1 >= 0 && maze[path[pathLength-1].row-1][path[pathLength-1].col] == 0){
            int pass = isPrev(path, pathLength, 0);

            if(pathLength == 1 || pass == 1){
                path[pathLength].row = path[pathLength-1].row-1;
                path[pathLength].col = path[pathLength-1].col;
                
                move(path, ++pathLength, maze);
                pathLength--;
            }
            
        }
        if(path[pathLength-1].row+1 < ROW && maze[path[pathLength-1].row+1][path[pathLength-1].col] == 0){
            int pass = isPrev(path, pathLength, 1);

            if(pathLength == 1 || pass == 1){
                path[pathLength].row = path[pathLength-1].row+1;
                path[pathLength].col = path[pathLength-1].col;

                move(path, ++pathLength, maze);
                pathLength--;
            }
        }
        if(path[pathLength-1].col-1 >= 0 && maze[path[pathLength-1].row][path[pathLength-1].col-1] == 0){
            int pass = isPrev(path, pathLength, 2);
            
            if(pathLength == 1 || pass == 1){
                path[pathLength].row = path[pathLength-1].row;
                path[pathLength].col = path[pathLength-1].col-1;

                move(path, ++pathLength, maze);
                pathLength--;
            }
        }
        if(path[pathLength-1].col+1 < COL && maze[path[pathLength-1].row][path[pathLength-1].col+1] == 0){
            int pass = isPrev(path, pathLength, 3);

            if(pathLength  == 1 || pass == 1){
                path[pathLength].row = path[pathLength-1].row;
                path[pathLength].col = path[pathLength-1].col+1;

                move(path, ++pathLength, maze);
                pathLength--;
            }
        }
        return;
    }

};


int main(){

    int maze[ROW][COL] = {
        {0,1,0,0,0,0,1},
        {0,0,0,1,1,0,0},
        {1,0,1,0,0,0,1},
        {0,0,0,1,0,1,1},
        {0,1,0,0,0,0,0},
        {0,1,1,0,1,1,1},
        {0,0,0,0,0,0,0}
        };


    struct Space *path = malloc(sizeof(struct Space)*(ROW*COL));
    path[0].row = START_ROW;
    path[0].col = START_COL;
    int pathLength = 1;

    move(path, pathLength, maze);

}
