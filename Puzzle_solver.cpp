#include <bits/stdc++.h>
#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <algorithm>  // if needed
using namespace std;  // Or prefix std:: everywhere

#include "puzzle_state.h"     // contains declarations for n, initial, moves, m, Node, etc.
#include "Check_Solvable.h"   // declares isSolvable()
using namespace std;

extern void bfs(Node*);
extern void A_Star(Node*);
extern void IDA_star(Node*);

int main() {
#ifndef ONLINE_JUDGE
    // Redirect input/output files
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Read initial puzzle config and locate blank tile
    int x0 = -1, y0 = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int val;
            cin >> val;
            initial[i][j] = val;
            if (val == 0) {
                x0 = i;
                y0 = j;
            }
        }
    }

    cout << "Choose algorithm:\n1. BFS\n2. A*\n3. IDA*\n";
    int choice;
    cin >> choice;

    if (!isSolvable()) {
        cout << "SORRY NOT SOLVABLE\n";
        return 0;
    } else {
        cout << ":) SOLVABLE\n";
    }

    // Create initial node
    Node* root = newNode(initial, x0, y0, x0, y0, 0, nullptr);

    clock_t start = clock();

    if (choice == 1) {
        bfs(root);
    } else if (choice == 2) {
        A_Star(root);
    } else if (choice == 3) {
        IDA_star(root);
    } else {
        cout << "Invalid choice!\n";
        delete root;
        return 1;
    }

    clock_t end = clock();
    cout << "Time taken to execute: " << fixed << setprecision(6)
         << double(end - start) / CLOCKS_PER_SEC << " seconds\n";

    delete root;
    return 0;
}
