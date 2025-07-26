#include "puzzle_state.h"    
#include <iostream>
#include <queue>
#include <map>
#include <vector>

using namespace std;

// Comparator for pq based on f = cost + level
struct prioritize {
    bool operator()(const Node* p1, const Node* p2) const {
        return (p1->cost + p1->level) > (p2->cost + p2->level);
    }
};

void A_Star(Node* src) {
     
    vector<int> dest;
    for (int i = 1; i < n * n; i++)
        dest.push_back(i);
    dest.push_back(0);  // blank tile as 0 at end

    // Create the root node with heuristic cost
    Node* root = newNode(src->board, src->x_0, src->y_0, src->x_0, src->y_0, src->level, src->par);
    root->cost = heuristic_manhattan(root->board);

    priority_queue<Node*, vector<Node*>, prioritize> pq;
    map<vector<int>, bool> vis;

    pq.push(root);

    while (!pq.empty()) {
        Node* cur = pq.top();
        pq.pop();

        int x = cur->x_0;
        int y = cur->y_0;

        // Flatten current board state to vector for visited checking
        vector<int> arr;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                arr.push_back(cur->board[i][j]);

        if (vis[arr]) {
            delete cur;  // free memory for repeated state
            continue;
        }
        vis[arr] = true;

        if (cur->cost == 0) {  // Puzzle solved
            cout << "SOLUTION STATE using A* star:\n";
            cout << "No. of moves: " << cur->level << "\n\n";

            moves.clear();
            m = 0;
            print_moves(cur);

            // Print solution moves from start to finish
            for (int i = 0; i < m; ++i) {
                cout << "Move " << i << ":\n";
                print(moves[i]);
            }

             
            delete cur;
            while (!pq.empty()) {
                delete pq.top();
                pq.pop();
            }

            return;
        }

        // Explore all possible moves by sliding the blank tile
        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];

            if (check(nx, ny)) {
                Node* temp = newNode(cur->board, x, y, nx, ny, cur->level + 1, cur);
                temp->cost = heuristic_manhattan(temp->board);

                vector<int> tempArr;
                for (int i = 0; i < n; i++)
                    for (int j = 0; j < n; j++)
                        tempArr.push_back(temp->board[i][j]);

                if (!vis[tempArr])
                    pq.push(temp);
                else
                    delete temp;  
            }
        }

        delete cur;  
    }

    /
    cout << "No solution found using A*.\n";
}
