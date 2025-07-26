#include "puzzle_state.h"
#include <queue>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>  
using namespace std; 

void bfs(Node* src) {
    // Destination configuration: 1, 2, 3, ..., n*n-1, 0
    vector<int> dest;
    for (int i = 1; i < n * n; ++i) dest.push_back(i);
    dest.push_back(0);

    // Create a root node from source
    Node* root = newNode(src->board, src->x_0, src->y_0, src->x_0, src->y_0, src->level, src->par);

    queue<Node*> q;
    map<vector<int>, bool> vis;

    q.push(root);

    while (!q.empty()) {
        Node* cur = q.front();
        q.pop();

        int x = cur->x_0;
        int y = cur->y_0;

        // Flatten the board for visited state checks
        vector<int> arr;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                arr.push_back(cur->board[i][j]);

        if (vis[arr]) continue;
        vis[arr] = true;

        // Check if current state is goal
        if (arr == dest) {
            cout << "SOLUTION STATE using BFS:\n";
            cout << "No. of moves: " << cur->level << "\n\n";

            moves.clear();
            m = 0;
            print_moves(cur);

            // Print all moves from start to goal
            for (int i = 0; i < m; ++i) {
                cout << "Move " << i << ":\n";
                print(moves[i]);
            }

            // Cleanup remaining nodes in queue
            while (!q.empty()) {
                delete q.front();
                q.pop();
            }
            delete cur; // delete current node after done
            return;
        }

        // Explore possible moves by sliding the blank space
        for (int k = 0; k < 4; ++k) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (check(nx, ny)) {
                Node* temp = newNode(cur->board, x, y, nx, ny, cur->level + 1, cur);

                vector<int> tmp;
                for (int i = 0; i < n; i++)
                    for (int j = 0; j < n; j++)
                        tmp.push_back(temp->board[i][j]);

                if (!vis[tmp]) {
                    q.push(temp);
                } else {
                    delete temp;  // Avoid memory leak
                }
            }
        }

        delete cur;  // Clean up current node after expanding
    }

    cout << "No solution found using BFS.\n";
}
