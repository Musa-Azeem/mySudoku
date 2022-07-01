/*
Musa Azeem
Completed: 10/17/21 - 18:33:01
This program is used to run the mySudoku project

Inputs: Command line input - filename of a sudoku board file

Outputs: Outputs to stdout whether or not the board has been solved, and the result board after solving. 
*/

#include <iostream>
#include <string>
#include "inc/mySudoku.h"

using namespace std;

int main(int argc, char **argv){
    if(argc != 2){
        cout << "Usage for " << argv[0] << ":" << endl;
        cout << argv[0] << " <InputFileName>" << endl;
        exit(0);
    }
    mySudoku game;              // create mySudoku object to solve the puzzle

    game.readData(argv[1]);     // read board

    // solve puzzle
    if(game.solvePuzzle()){
        // if object has solved the puzzle, print the board to stdout
        cout << "Solved Puzzle: " << endl;
        game.printData();
    }
    else{
        // If object was unable to solve the puzzle, report to user
        cout << "Puzzle could not be solved" << endl;
    	game.printData();
    }
}
