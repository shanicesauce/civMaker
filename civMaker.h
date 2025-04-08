#ifndef CIVMAKER_H
#define CIVMAKER_H


#define ROWS 9
#define COLS 9



void gameBoardSetup(char gameBoard[ROWS][COLS], int numRows, int numCols);
void printGameBoard(char gameBoard[ROWS][COLS], int numRows, int numCols);
int civDirection(char gameBoard[ROWS][COLS], int row, int col, char building);
void civGamePlay(char gameBoard[ROWS][COLS]);

#endif
