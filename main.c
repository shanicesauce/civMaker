#include <stdio.h>
#include <stdlib.h>
#include "civMaker.h"

int main(void){
    char gameBoard[ROWS][COLS];
    
    
    gameBoardSetup(gameBoard, ROWS,COLS);
    printGameBoard(gameBoard, ROWS,COLS);
    
    civGamePlay(gameBoard);

    return 0;
}
