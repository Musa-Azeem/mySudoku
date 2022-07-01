/*
Musa Azeem
Completed: 10/17/21 - 18:33:01
This program is used to test the mySudoku object
Inputs: Command line inputs include a file containing values representing a sudoku board. 
    Data must be formatted in 9 rows of 9 integer values, with each value seperated by a space
Outputs: Outputs to stdout whether or not the board has been solved, and the result board after solving. 
*/
#include <iostream>
#include <fstream>
#include <string>
#include "inc/mySudoku.h"

using namespace std;

int main(int argc, char **argv){
    if(argc != 2){
        cout << "Usage for " << argv[0] << ":" << endl;
        cout << argv[0] << " <InputFileName>" << endl;
        exit(0);
    }
    mySudoku game;

    game.readData(argv[1]);
    if(game.solvePuzzle()){
        cout << "Solved Puzzle: " << endl;
        game.printData();
    }
    else{
        cout << "Puzzle could not be solved" << endl;
    	game.printData();
    }
}
