/*
Musa Azeem
Completed: 10/17/21 - 18:33:01
This file defines the mySudoku class and one related constant
Definitions:
    SIZE:   Length and width of board - is equal to 9

Constructors:
    default:        no arguments
    alternate:      takes an input 9x9 2D array to initilize board variables

Class private variables:
    board (int[][]):    9x9 2D array to represent the sudoku board
    pos (int[][][]):    9x9x9 3D array to hold possble values at each position of the board
    numPos (int[][]):   9x9 2D array to hold the number of possiblities at each position of the board

Class functions:
    Public:
        readData:       reads a sudoku board from a file of a specified name
        printData:      prints sudoko board to the console
        solvePuzzle:    solves the board
    Private:
        init:           initializes all class array variables (baord, pos and numPos) to zeroes
        checkColumn:    checks a column of the board for a value
        checkRow:       checks a row of the board for a value
        checkSubSquare: checks a 3x3 subsquare of the board for a value
        solvePuzzleRec: recursive function call to solve puzzle
*/

#ifndef MY_SUDOKU_H
#define MYSUDOKU_H

#include <string>

#define SIZE 9
class mySudoku{
    public:
        mySudoku();
        mySudoku(int inputBoard[][9]);
        ~mySudoku();
        void readData(const std::string FileName);
        void printData();
        bool solvePuzzle();
    private:
        int board[SIZE][SIZE];
        int pos[SIZE][SIZE][SIZE];
        int numPos[SIZE][SIZE];
        void init();
        bool checkColumn(const int column, const int number);
        bool checkRow(const int row, const int number);
        bool checkSubSquare(int row, int column, const int number);
        bool solvePuzzleRec(int startI, int startJ);
};

#endif