/*
Musa Azeem
Completed: 10/17/21 - 18:33:01
This program definess a sudoku object that holds a sudoku board and is capable of solving it and printing its contents to stdout
    class variables:
        board:  9x9 2d integer array - represents the sudoku board
        pos:    9x9x9 3d integer array - holds all possible values at each empty spot of the sudoku board
        numPos: 9x9 2d integer array - holds the number of possibilities found for each spot on board
        size:   constant value 9 - used for initializing arrays and as limit for valid numbers (0-8)
    functions:
	    default constructor:    initializes the board array. All values are set to 0
        alternate constructor:  initializes the board array using a input 9x9 2d array representing a sudoku board
        destructor:             empty
        init:                   called by constructors - initializes all arrays with 0s
        readData:               reads a input file with 9 rows of 9 values, representing a sudoku board. The method uses the data to populate the board array
        printData:              prints the board array to stdout
        solvePuzzle:            solves the sudoku puzzle held in the board array - calls solvePuzzleRec to completely solve
        solvePuzzleRec:         recursive function to finish solving the puzzle
        checkColumn:            checks a column in the board for a value
        checkRow:               checks a row in the board for a value
        checkSubSquare:         checks a subsquare in the board for a value

Inputs: No inputs required for default constructor. Board may be initialized with a 9x9 array or a input file.
    The input file must be formatted in 9 rows of 9 integer values, with each value seperated by a space.
Outputs: printData() prints the board array to stdout.
*/
#include "../inc/mySudoku.h"
#include <iostream>
#include <fstream>
#include <string>

mySudoku::mySudoku(){
    /*
    defualt constructor, calls initBoard() to initialize board attribute - initially sets all values to zero
    Inputs: None
    Output: None - directly modifies class board array
    */
    init();
}
mySudoku::mySudoku(int inputBoard[][9]){
    /*
    alternate constuctor - calls initBoard() to initialize board attribute
     and populates the board with values from a 9x9 double pointer array
    Inputs: A 9x9 integer array representing a sudoku board
    Output: None - directly modifies class board array
    */
    init();
    for(int i(0); i<SIZE; i++){
        for(int j(0); j<SIZE; j++){
            board[i][j] = inputBoard[i][j];
        }
    }
}
void mySudoku::init(){
    /*
    initializes class variables
    Inputs: None
    Output: None - directly modifies class board array
    */
    // size = 9;
    for(int i=0; i<SIZE;i++){
        //nums[i] = i+1;                  //init nums array
        for(int j(0); j<SIZE; j++){
            board[i][j] = 0;            //init board array
            numPos[i][j] = 0;          //init number of possibilities array
            for(int k(0); k<SIZE; k++){
                pos[i][j][k] = 0;       //init posibilities array
            }
        }
    }
    
}
void mySudoku::readData(const std::string fileName){
    /*
    takes in a file name and reads it, using the values to creates a sudoku board
    Input:  A formatted file containing data defining a sudoku board
    Output: None - directly modifies class board array
    */
    std::ifstream in_file;
    in_file.open(fileName);
    if(in_file.fail()){
        std::cout << "Error opening the file" << std::endl;
        exit(1);
    }
    while(!in_file.eof()){
        for(int i(0); i<SIZE; i++){
            for(int j(0); j<SIZE; j++){
                in_file >> board[i][j];
            }
        }
    }
    in_file.close();
}

void mySudoku::printData(){
    /*
    prints sudoku board
    Input:  None
    Output: prints the class board array to stdout - does not modify class variables
    */
    for(int i(0); i<SIZE; i++){
        for(int j(0); j<SIZE; j++){
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool mySudoku::solvePuzzle(){
    /*
    function to solve the sudoku puzzle:
        first finds the possible values at every empty spot on the board
        any spots with only one possibility are filled with that value - this is done for each spot after its possibilities are found, so the next spot takes this value into consideration
        after going through every empty spot, the function calls solvePuzzleRec to completely solve puzzle
    Input:  None
    Output: function directly modifies class board array, and returns the return of solvePuzzleRec, which is 1 if the puzzle is solved, and 0 if not
    */
    for(int i(0); i<SIZE; i++){
        for(int j(0); j<SIZE; j++){
            int index(0);           //index for posibilities arrays
            if(board[i][j] == 0){   //check if spot is empty

                for(int k(1); k<SIZE+1; k++){   //iterate through each possible number 1-9
                    if(!checkRow(i, k) && !checkColumn(j, k) && !checkSubSquare(i,j,k)){    //check if each number is a possibility
                        pos[i][j][index] = k;   //add possibilies to the pos array
                        index++;                //update index for possibility array at this spot
                        numPos[i][j]++;         //update number of possibilities for this spot

                    }
                }

                //enter unique solutions into board
                if(numPos[i][j]==1){
                    //if there is only one possibility at this spot, set it in the board
                    //since this is the only possible number at this spot, it is entered into the board and
                    //the next spot will take this number into consideration
                    board[i][j] = pos[i][j][0];
                
                }
            }
        }
    }
    return(solvePuzzleRec(0,0));
}

bool mySudoku::solvePuzzleRec(int startI, int startJ){
    /*
    function to be called recursively in order to completely solve puzzle
        at the point of this functions first call, all initially unique values are placed on the board, and every spot that was not unique has a list of possible values in the pos array
        the rest of the puzzle is solved with branching - one option is chosen for the the first unsolved spot, and the puzzle will search for unique numbers in later spots.
        If another spot has multiple possibilities, a number is chosen for that spot, and the solution continues.
        If a certain number does not yield a solution, the program will go back to the most recent spot where a choice was made, and another option is chosen instead.
        This is repeated until the correct number is chosen for each spot, yielding a solution
        If the function reaches a point where there are no more possibilities for a spot and none have yeilded a solution, the function cannot solve the puzzle and 0 is returned
        Input:  None
        Output: function directly modifies the class board array, and returns 1 if the puzzle is solved, and 0 if not
            at the last recursive call, 1 is returned if the end of the board has been reached, the rest of the functions calls on the stack then return 1
            if 0 is returned during a recursive call, the current branch is not a solution, and the recursion backtracks until it reaches the last spot with another possibility
            if no possibilities work, the functions on the stack return 0 until the initial call also returns 0.
    */

    bool found(0); //keeps track of whether or not a number that fits has been found for each spot
    for(int i(startI); i<SIZE; i++){    //start on row of last branch
        int j;
        if(i==startI){      //if this is the first iteration of the function call, start on column after the last branch spot
            j=startJ;
        }
        else{
            j=0;
        }
        for(int j(0); j<SIZE; j++){    //start on column of last branch
            //if this is the first iteration of the function call , start on column after the last branch spot
            //otherwise, start at first column of new row (as usual)
            if(i==startI && j==0){
                j=startJ;
                if(j>=SIZE){    //if this value of j is outside of range, go to next row
                    continue;
                }
            }
            if(board[i][j]==0){     //if the spot has a 0, it must have multiple possibilities
                for(int k(0); k<numPos[i][j]; k++){ //iterate through possible numbers at this spot
                    if(!checkRow(i, pos[i][j][k]) && !checkColumn(j, pos[i][j][k]) && !checkSubSquare(i, j, pos[i][j][k])){
                        board[i][j] = pos[i][j][k];
                        found = 1;      //indicate that a number had been found for this spot in this branch
                        if(solvePuzzleRec(i, j+1)){  
                            //if a number is found that works for this spot, recursively call function to go down this branch
                            return(1);
                        }
                    }
                    found = 0;      //if spot has no more possibilities that fit in this branch
                }
                if(found==0){
                    board[i][j] = 0;    //change this spot back to 0 before backtracking
                    return(0);      //if no possibilities worked at this spot, return 0 to indicate this branch is not a solution
                }
            }
        }
    }
    return(1);  //if end of board has been reached, all spots on the board have a valid number in it, and the functions can return
}


bool mySudoku::checkRow(const int row, const int number){
    /*
    takes in a row number and value to search for
    Input:  integer value for row on board to search, and integer value to search for
    Output: returns 1 if the value is found, and 0 if not
    */
    for(int j=0; j<SIZE; j++){
        if(number==board[row][j]){
            return(1); //return true - number was found
        }
    }
    return(0);
}

bool mySudoku::checkColumn(const int column, const int number){
    /*
    takes in a column number and value to search for
    Input: integer value for column on board to search, and integer value to search for
    Output: returns 1 if the value is found, and 0 if not
    */
    for(int i(0); i<SIZE; i++){
        if(number==board[i][column]){
            return(1);  //return true if number is found
        }
    }
    return(0);
}

bool mySudoku::checkSubSquare(int row, int column, const int number){
    /*
    takes in a row, column, and number to search the subsquare containing the row and column for
        operates by finding the row and column of the top left corner of the subsquare, and searches the values of the subsquare using that corner as reference.
    Input: integer values for row and column on board to search subsquare of, and integer value to search for
    Output: returns 1 if the value is found, and 0 if not
    */
    if(row%3 != 0){ //given row is not the beginning of a subsquare (0, 3, or 6)
        if(row > 6)
            row = 6;
        else if(row > 3)
            row = 3;
        else
            row = 0;    
    }
    if(column%3 != 0){ //given column is not the beginning of a subsquare (0, 3, or 6)
        if(column > 6)
            column = 6;
        else if(column > 3)
            column = 3;
        else
            column = 0;    
    }
    //now can check for number
    for(int i=row; i<row+3;i++){
        for(int j=column; j<column+3; j++){
            if(board[i][j]==number)
                return(1);
        }
    }
    return(0);
}

mySudoku::~mySudoku(){
}