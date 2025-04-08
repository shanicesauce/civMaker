#include <stdio.h>
#include <stdlib.h>
#include "civMaker.h"

int food = 0; 
int villages = 0;


void gameBoardSetup(char gameBoard[ROWS][COLS], int numRows, int numCols){

    for(int rowIndex = 0 ; rowIndex < numRows ; rowIndex++){
        for(int colIndex = 0; colIndex < numCols ; colIndex++){
            if(rowIndex == 4 && colIndex == 4){
                gameBoard[rowIndex][colIndex] = 'C';            
            } else {
                int randNum = rand() % 100;
                if(randNum < 85){
                    gameBoard[rowIndex][colIndex] = '.';
                } else {
                    gameBoard[rowIndex][colIndex] = '*';
                }
        }
        }
    }
}


void printGameBoard(char gameBoard[ROWS][COLS], int numRows, int numCols){

    printf ("\n  0 1 2 3 4 5 6 7 8\n");

    for(int rowIndex = 0 ; rowIndex < numRows ; rowIndex++){
        printf("%c ",'a' + rowIndex);
        for(int colIndex = 0; colIndex < numCols ; colIndex++){
            printf("%c ", gameBoard[rowIndex][colIndex]);
        }
        printf("\n");
    }
    printf("Food: %d, Villages: %d\n", food,villages);
}


int civDirection(char gameBoard[ROWS][COLS], int row, int col,char building) {
    int direction[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; 
    int count = 0;

    for(int i = 0; i < 4; i++){
        int newRow = row + direction[i][0];
        int newCol = col + direction[i][1];

        if(newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS){
            if(gameBoard[newRow][newCol] == building){
                count++;
            }
        }
    }
    return count;
}




void civGamePlay(char gameBoard[ROWS][COLS]){
    char rowChar;
    char building;
    int col;
    int row; 
    int choice;

do{
    printf("\nChoose an action:\n");
    printf("1. Farm (Cost: 1 food, + food per adjacent fertile ground)\n");
    printf("2. Road (Allows expansion)\n");
    printf("3. Village (Cost: 1 food)\n");
    printf("4. Remove (Sets tile to barren)\n");
    printf("5. End Game\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    getchar(); 
    
    if(choice !=5){
        printf("Enter position (example: a0): ");
        scanf("%c%d", &rowChar, &col);
        row = rowChar - 'a';
    }

int neighborVillage = civDirection(gameBoard, row, col, 'V');
int neighborFarm = civDirection(gameBoard, row, col, 'F');
int mainCapital = civDirection(gameBoard, row, col, 'C');
int nearByRoad = civDirection(gameBoard, row, col, '+');

switch(choice){
    case 1: // farm
        if(gameBoard[row][col] == 'C'){
            printf("\nCan't farm there!\n");
            break;
        } else if(neighborFarm == 0 && nearByRoad == 0 && mainCapital == 0 && neighborVillage == 0){
            printf("\nYou must set up around another building\n");
            break;
        } else {
            food --;
            int addFood = civDirection(gameBoard,row,col,'*');
            food += addFood;
            gameBoard[row][col] = 'F';
        }
    break;
    case 2: //road
    if(neighborFarm == 0 && nearByRoad == 0 && mainCapital == 0 && neighborVillage == 0){
        printf("\nYou must set up around another building\n");
        break;
    } else {
        gameBoard[row][col] = '+';

    }

    break;

    case 3: //village
        if(gameBoard[row][col] == 'C'){
            printf("\nHey! You can't build there!\n");
            break;
        } else if (neighborVillage > 0){
            printf("\nAre you trying to start a war? Villages can't be next to each other\n");
            break;
        } else if(neighborFarm == 0 && nearByRoad == 0 && mainCapital == 0){
            printf("\nYou must set up around one another building\n");
            break;
        }
        else {
            food --;
            villages ++;
            gameBoard[row][col] = 'V';
        }


        break;
    case 4: //remove 

    gameBoard[row][col] = '.';

    break;
    
    case 5: //end game
        if(food >= villages){
            printf("\nYour Civilization Survived with %d Village(s) and %d Food(s) to spare!\n", villages,food);
            printf("\nYour Majesty the Great ｡◕ ‿ ◕｡!\n");
        } else {
            printf("\nYour Civilization Starved o(╥﹏╥)o! Do better next time\n");
        }
        exit(0);
default :
    printf("okay weird...try again?");
    break;
}
printf("\n");
printGameBoard(gameBoard,ROWS,COLS);
    } while (choice != 5);
}
