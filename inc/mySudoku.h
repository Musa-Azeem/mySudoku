/*
Musa Azeem
Completed: 10/17/21 - 18:33:01
This program prototypes functions that are defined in mySudoku.cpp
Inputs: No inputs
Outputs: No outputs
*/

#include <string>
using namespace std;

class mySudoku{
    public:
        mySudoku();
        mySudoku(int inputBoard[][9]);
        ~mySudoku();
        void readData(const string FileName);
        void printData();
        bool solvePuzzle();
    private:
        int board[9][9];    //sudoku board
        int pos[9][9][9];   //3d array to hold possible values at each sopt of the board 
        int numPos[9][9];  //number of possibilities at each spot
        int size;           //size of board length/width
        void init();
        bool checkColumn(const int column, const int number);
        bool checkRow(const int row, const int number);
        bool checkSubSquare(int row, int column, const int number);
        bool solvePuzzleRec(int startI, int startJ); //recursively designed function to completely solve puzzle
};
