#include <iostream>
#include <cstring>  // for memcpy
#include <vector>
#include <cmath>    // for abs
#include <climits>

#include <queue>
#include <map>

#include <algorithm>  // if needed
using namespace std;  // Or prefix std:: everywhere

#include "puzzle_state.h"
const int n = 3;           // actual definition
int initial[3][3];         // actual definition



int dx[] = {0, 0, 1, -1};  // Directions for row movement
int dy[] = {1, -1, 0, 0};  // Directions for column movement

// Structure to represent the current state of the puzzle


// Function to create a new node given the current board and move
Node* newNode(int board[n][n], int x_0, int y_0, int nx, int ny, int level, Node* par) {
    Node* temp = new Node;
    temp->par = par;
    memcpy(temp->board, board, sizeof(temp->board));
    // Swap blank tile with target tile to create new state
    swap(temp->board[x_0][y_0], temp->board[nx][ny]);
    temp->x_0 = nx;
    temp->y_0 = ny;
    temp->level = level;
    temp->cost = INT_MAX;  // Initialize cost with a large value
    return temp;
}

// Manhattan distance heuristic: sum of distances of tiles from their goal positions
int heuristic_manhattan(int b[n][n]) {
    int dist = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int val = b[i][j];
            if (val != 0) {
                int target_x = (val - 1) / n;
                int target_y = (val - 1) % n;
                dist += abs(i - target_x) + abs(j - target_y);
            }
        }
    }
    return dist;
}

// Check if given coordinates are within the board boundaries
bool check(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < n;
}

// Global variables to store moves for printing
int m = 0;
vector<vector<vector<int>>> moves;

// Helper recursive function to build the moves vector from parent pointers
void print_moves(Node* cur) {
    if (cur == nullptr) return;

    print_moves(cur->par);

    vector<vector<int>> step(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            step[i][j] = cur->board[i][j];
        }
    }
    moves.push_back(step);
    m++;
}

// Utility function to print a puzzle board configuration
void print(const vector<vector<int>>& arr) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

// Alternative print overload for raw arrays if used elsewhere
void print(int arr[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}
