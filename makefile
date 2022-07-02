# compiler
cc := g++

# source code
src := main.cpp src/mySudoku.cpp

# final executable
exe := sudoku

# compile flags
flags := -std=c++17 

# compile command
compile.cc = $(cc) $(flags) $^ -o $@

# make
$(exe): $(src)
	@$(compile.cc)

clean:
	@rm -rf $(exe)
