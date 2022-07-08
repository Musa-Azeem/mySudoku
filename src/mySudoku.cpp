/*
Musa Azeem
Completed: 10/17/21 - 18:33:01
This program defines the functions of the mySudoku class

Functions:
    default constructor:    initializes the board array. All values are set to 0
    alternate constructor:  initializes the board array using a input 9x9 2d array representing a sudoku board
    destructor:             empty
    init:                   called by constructors - initializes all arrays with 0s
    readData:               reads a input board file with 9 rows of 9 values
    printData:              prints the board array to stdout
    solvePuzzle:            solves the sudoku puzzle held in the board array - calls solvePuzzleRec
    solvePuzzleRec:         recursive function to finish solving the puzzle
    checkColumn:            checks a column in the board for a value
    checkRow:               checks a row in the board for a value
    checkSubSquare:         checks a subsquare in the board for a value
*/

#include "../inc/mySudoku.h"
#include <iostream>
#include <fstream>
#include <string>

mySudoku::mySudoku(){
    /*
    default constructor, calls init() to initialize class variables
    */

    init();
}

mySudoku::mySudoku(int inputBoard[][9]){
    /*
    Alternate constuctor - calls init() to initialize class variables and 
        populates the board with values from a 9x9 2D array
    Sets ready to true
    
    Parameters:
        inputBoard (int[][]):   A 9x9 integer array representing a sudoku board
    */
    
    init();
    for(int i(0); i<SIZE; i++){
        for(int j(0); j<SIZE; j++){
            board[i][j] = inputBoard[i][j];
        }
    }
    ready = true;
}

void mySudoku::init(){
    /*
    Initializes class variables - sets all elements of all three arrays to 0
    */

    for(int i=0; i<SIZE;i++){
        for(int j=0; j<SIZE; j++){
            board[i][j] = 0;            //init board array
            numPos[i][j] = 0;          //init number of possibilities array
            for(int k=0; k<SIZE; k++){
                pos[i][j][k] = 0;       //init posibilities array
            }
        }
    }
    
}
void mySudoku::readData(const std::string filename){
    /*
    Reads a file to populate the board variable with a sudoku board
    Sets ready to true

    Parameters:
        filename (const string):  name of file in directory to read
    */

    std::ifstream in_file;
    in_file.open(filename);
    if(in_file.fail()){
        std::cout << "Error opening the file" << std::endl;
        exit(1);
    }
    while(!in_file.eof()){
        for(int i=0; i<SIZE; i++){
            for(int j(0); j<SIZE; j++){
                in_file >> board[i][j];
            }
        }
    }
    in_file.close();
    ready = true;
}

void mySudoku::printData(){
    /*
    Prints sudoku board to stdout
    If there are any zeroes (emtpy values) in the board, an X is printed
    */

    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            if (board[i][j] == 0)
                std::cout << "X" << " ";
            else
                std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool mySudoku::solvePuzzle(){
    /*
    Solves the sudoku puzzle:
        First all possible values are found for every empty spot on the board
        Any spots with only one possibility are filled with that value
        After going through every spot once, the function calls solvePuzzleRec
            to completely solve puzzle
    If the "ready" value is false, there is no board, and the function returns false
    
    Return:
        bool:   true if the puzzle has been solved, false if not
    */

    if(!ready){
        std::cout << "Board not loaded into object yet" << std::endl;
        return false;
    }
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            int index = 0;                  // index for pos array
            if(board[i][j] == 0){           // check if spot is empty
                for(int k=1; k<SIZE+1; k++){// iterate through each possible number 1-9
                    if (!checkRow(i, k) &&   //check if each number is a possibility
                            !checkColumn(j, k) && 
                            !checkSubSquare(i,j,k)) {     
                        pos[i][j][index] = k;   // add possibilies to the pos array
                        index++;                // update index for possibility array at this spot
                        numPos[i][j]++;         // update number of possibilities for this spot
                    }
                }

                // enter unique solutions into board
                if(numPos[i][j]==1){
                    board[i][j] = pos[i][j][0];
                }
            }
        }
    }
    // Call solvePuzzleRec to complete puzzle
    return(solvePuzzleRec(0,0));
}

bool mySudoku::solvePuzzleRec(int startI, int startJ){
    /*
    Function to be called recursively in order to completely solve puzzle
    At the point of this functions first call, all initially unique values are
        placed on the board, and every spot that was not unique has a list of 
        possible values in the pos array
    The rest of the puzzle is solved with branching - one option is chosen for
        the first unsolved spot, and the function will search for unique 
        numbers in later spots using this temporary value
    After branching, if another spot with multiple possibilities is encountered,
        a number is again chosen for that spot, and another branch is started
    If a certain branch does not yield a solution, the function will backtrack
        to the most recent branching spot, and another option is chosen instead
    This is repeated until a branch yields a solution for each spot
    If the function reaches a point where there are no more possibilities for a
        spot and no branches have yeilded a solution, the function cannot solve 
        the puzzle and false is returned

    Parameters:
        startI (int):   row index to start search from ater branching
        startJ (int):   column index to start search from
    

    Returns:
        bool:   false if the current branch does not yeild a solution, true if it does
    */

    bool found = 0;       // if number that fits has been found for each spot
    for(int i=startI; i<SIZE; i++) {    // start on row of the last branch
        int j;
        // if this is the first iteration, start on column after the last branch spot
        if (i == startI)
            j=startJ;
        else
            j=0;

        for(int j=0; j<SIZE; j++) {    //start on column of last branch
            // if this is the first iteration of the function call, start on column after the last branch spot
            // otherwise, start at first column of new row (as usual)
            if(i == startI && j == 0) {
                j=startJ;
                if(j>=SIZE){    //if this value of j is outside of range, go to next row
                    continue;
                }
            }

            if(board[i][j] == 0) {    //if the spot is empty
                for(int k=0; k<numPos[i][j]; k++){ // iterate through possible numbers at this spot
                    if(!checkRow(i, pos[i][j][k]) && 
                            !checkColumn(j, pos[i][j][k]) && 
                            !checkSubSquare(i, j, pos[i][j][k])) {
                        board[i][j] = pos[i][j][k];
                        found = 1;                      // indicate that a number had been found for this spot in this branch
                        if (solvePuzzleRec(i, j+1)) {  
                            // if a number that fits in this spot is found, recursively call function to go down this branch
                            return 1;
                        }
                    }
                    found = 0;      // if spot has no more possibilities that fit in this branch
                }
                if (found == 0) {
                    board[i][j] = 0;    //change this spot back to 0 before backtracking
                    return 0;      // f no possibilities worked at this spot, return 0 to indicate this branch is not a solution
                }
            }
        }
    }
    return(1);  // if end of board has been reached, all spots on the board have a valid number in it, and the functions can return
}


bool mySudoku::checkRow(const int row, const int number){
    /*
    Searches a row in the board for a value

    Parameters:
        row (const int):    row index to search
        number (const int): number to search for

    Return:
        returns true if value is found, and false if not
    */

    for(int j=0; j<SIZE; j++){
        if(number == board[row][j]){
            return(1);      // return true - number was found
        }
    }
    return 0;
}

bool mySudoku::checkColumn(const int column, const int number){
    /*
    Searches a column in the board for a value

    Parameters:
        column (const int): column index to search
        number (const int): number to search for

    Return:
        returns true if value is found, and false if not
    */

    for(int i=0; i<SIZE; i++){
        if(number == board[i][column]){
            return(1);  // return true if number is found
        }
    }
    return(0);
}

bool mySudoku::checkSubSquare(int row, int column, const int number){
    /*
    Searches a subsquare in the board for a value
    Searches the subsquare containing the spot at the given row / column:
        First, finds the row and column index of the top left corner of this subsquare
        It then uses this corner as a reference to search the rest of the subquare

    Parameters:
        row (int):    row index to search
        column (int): column index to search
        number (const int): number to search for

    Return:
        returns true if value is found, and false if not
    */

    if(row%3 != 0){     // given row is not the beginning of a subsquare (0, 3, or 6)
        if(row > 6)
            row = 6;  
        else if(row > 3)
            row = 3;
        else
            row = 0;    
    }
    if(column%3 != 0){ // given column is not the beginning of a subsquare (0, 3, or 6)
        if(column > 6)
            column = 6;
        else if(column > 3)
            column = 3;
        else
            column = 0;    
    }
    // now can check subsquare for number
    for(int i=row; i<row+3; i++){
        for(int j=column; j<column+3; j++){
            if(board[i][j] == number)
                return 1;
        }
    }
    return 0;
}

mySudoku::~mySudoku(){
}