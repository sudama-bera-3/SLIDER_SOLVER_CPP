



#pragma once
extern const int n;
extern int initial[3][3];

#include <vector>
// Direction arrays for moving the blank tile (0)
// dx and dy arrays correspond to movements: Right, Left, Down, Up
extern int dx[4];
extern int dy[4];

// The initial board configuration, global 2D array
extern int initial[3][3];

// Node structure representing a state in the puzzle
struct Node {
    Node* par;       // Pointer to parent Node (previous state)
    int board[3][3]; // Current puzzle board state
    int x_0, y_0;    // Coordinates of the blank tile (0)
    int level;       // Number of moves to reach this state
    int cost;        // Heuristic cost (used in A* and IDA*)
};

// Creates a new Node from the given board by swapping the blank tile position
// Parameters:
// - board: current board state
// - x_0, y_0: current blank tile coordinates
// - nx, ny: new blank tile coordinates (after the move)
// - level: depth level (number of moves so far)
// - par: pointer to parent node
Node* newNode(int board[3][3], int x_0, int y_0, int nx, int ny, int level, Node* par);

// Calculates the Manhattan distance heuristic for a board configuration
int heuristic_manhattan(int b[3][3]);

// Checks if the coordinates (x, y) are within the puzzle boundaries
bool check(int x, int y);

// Prints a puzzle state (2D array) to stdout
void print(int arr[3][3]);

// Prints a puzzle state stored as vector of vectors (alternative overload)
void print(const std::vector<std::vector<int>>& arr);

// Records the solution moves (path from root to current node) into a global container
void print_moves(Node* cur);

// Global container to store the sequence of moves (each move is a 3x3 board vector)
// This is used to print the solution path after solving
extern std::vector<std::vector<std::vector<int>>> moves;

// Counter for the number of moves/states stored in `moves`
extern int m;
