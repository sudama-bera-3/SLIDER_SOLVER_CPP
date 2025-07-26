# SLIDER_SOLVER_CPP
A 3x3 sliding puzzle (8-puzzle) solver implementing BFS, A*, and IDA* search algorithms.

## Features

- Solve any 3x3 puzzle configuration (`0` for blank tile).  
- Choose algorithm:  
  - `1` BFS  
  - `2` A* (Manhattan distance heuristic)  
  - `3` IDA* (memory-efficient)  
- Automatic solvability check.  
- Prints solution moves and execution time.

## Usage

1. Compile all source files with a C++11+ compiler:
g++ Puzzle_solver.cpp BFS.cpp A_star.cpp IDA_STAR.cpp Check_Solvable.cpp puzzle_state.cpp -o solver
2. Run the program:  
3. Input the initial puzzle (3 rows of 3 integers) and algorithm choice (1, 2, or 3).


## Output

- Prints whether puzzle is solvable.  
- If solvable, prints moves from start to goal and time taken.  
- Otherwise, prints "SORRY NOT SOLVABLE".

## Project files

- `Puzzle_solver.cpp`: Main program.  
- `BFS.cpp`, `A_star.cpp`, `IDA_STAR.cpp`: Search algorithms.  
- `Check_Solvable.cpp`: Solvability checker.  
- `puzzle_state.*`: Puzzle representation, heuristics, and utilities.  
- `input.txt` & `output.txt`: Sample I/O files.

## Requirements

- C++11 or newer compiler.  
- Standard C++ libraries.

---

**Author:** SUDAMA BERA




