# mySudoku
Author: Musa Azeem
Date Completed: 7/7/22

This project defines a C++ class that can solve a 9x9 Sudoku puzzle

## Requirements
Unix operating system with C++ 17

## Directory Structure
```
.
├── inc
│   └── mySudoku.h
├── LICENSE
├── main.cpp
├── makefile
├── README.md
├── res
│   ├── Puzzle1.in
│   ├── Puzzle2.in
│   └── PuzzleUnsolveable.in
└── src
    └── mySudoku.cpp
```
## Usage

### Clone this repository
1. Open terminal
2. Clone the repository  
```
    git clone "https://github.com/Musa-Azeem/mySudoku"
```
3. Change directory to local project
```
    cd mySudoku
```  

### Commands
    clean repository:   make clean
    compile project:    make compile
    run project:        ./sudoku <Input File>

### Input File Format
- Input file must be formatted in 9 rows of 9 integer values, with each value 
separated by a blank space
- Empty spots are represented by a 0


## Project Components

### mySudoku Class
- This class loads in a sudoku board and recursively solves the puzzle
- The sudoku board can be provided to the object as a file or a 9x9 array
- This class is defined in the files `inc/mySudoku.h` and `src/mySudoku.cpp`

### Main Method
- The main method defined in `main.cpp` showcases an example usage of the
mySudoku class
- It receives a filename as a command line argument, and uses the mySudoku
class to solve the provided sudoku puzzle