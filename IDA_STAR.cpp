#include "puzzle_state.h"   // must declare Node, n, dx, dy, check(), print(), print_moves(), moves, m
#include <iostream>
#include <climits>

#include <queue>
#include <map>
#include <vector>
#include <algorithm>  // if needed
using namespace std;  // Or prefix std:: everywhere

using namespace std;

// IDA* depth-first bounded search
int IDDFS(Node* cur, int level, int threshold) {
    int f = level + heuristic_manhattan(cur->board);
    if (f > threshold)
        return f;

    // Check goal state (heuristic is zero)
    if (heuristic_manhattan(cur->board) == 0) {
        cout << "SOLUTION STATE using IDA* star:\n";
        cout << "No. of moves: " << cur->level << "\n\n";
        moves.clear();
        m = 0;
        print_moves(cur);

        for (int i = 0; i < m; ++i) {
            cout << "Move " << i << ":\n";
            print(moves[i]);
        }
        return 0;
    }

    int mini = INT_MAX;
    for (int k = 0; k < 4; ++k) {
        int nx = cur->x_0 + dx[k];
        int ny = cur->y_0 + dy[k];
        if (check(nx, ny)) {
            Node* temp = newNode(cur->board, cur->x_0, cur->y_0, nx, ny, cur->level + 1, cur);
            int bound = IDDFS(temp, level + 1, threshold);
            if (bound == 0) {
                delete temp;
                return 0;
            }
            mini = std::min(mini, bound);
            delete temp; // avoid memory leak
        }
    }
    return mini;
}

void IDA_star(Node* src) {
    Node* root = newNode(src->board, src->x_0, src->y_0, src->x_0, src->y_0, src->level, src->par);
    root->cost = heuristic_manhattan(root->board);
    int threshold = root->cost;

    while (true) {
        int temp_threshold = IDDFS(root, root->level, threshold);
        if (temp_threshold == 0) {
            delete root;
            return;
        }
        if (temp_threshold == INT_MAX) {
            cout << "No solution found using IDA*.\n";
            delete root;
            return;
        }
        threshold = temp_threshold;
    }
}
