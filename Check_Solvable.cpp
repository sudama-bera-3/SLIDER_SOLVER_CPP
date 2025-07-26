#include "puzzle_state.h"  // for n, initial[][]
#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <algorithm>  // if needed
using namespace std;  // Or prefix std:: everywhere

// Flatten the board into 1D array excluding the blank tile (0)
int flatten[9 - 1];  // for 3x3 puzzle: 8 elements

// Merge function to count inversions while sorting
int merge(int a[], int start, int mid, int end) {
    int temp[8];
    int pos = 0;
    int i = start, j = mid + 1;
    int invCount = 0;

    while (i <= mid && j <= end) {
        if (a[i] > a[j]) {
            temp[pos++] = a[j++];
            invCount += (mid - i + 1);
        } else {
            temp[pos++] = a[i++];
        }
    }
    while (i <= mid) temp[pos++] = a[i++];
    while (j <= end) temp[pos++] = a[j++];

    // Copy back to original array
    for (int k = 0; k < pos; ++k)
        a[start + k] = temp[k];

    return invCount;
}

// Recursive mergesort to count inversions
int mergesort(int a[], int start, int end) {
    if (start >= end) return 0;
    int mid = start + (end - start) / 2;
    int invCount = 0;
    invCount += mergesort(a, start, mid);
    invCount += mergesort(a, mid + 1, end);
    invCount += merge(a, start, mid, end);
    return invCount;
}

// Find the row of the blank tile (0) counting from the bottom (1-based)
int find_blankRow_pos() {
    for (int i = n - 1; i >= 0; --i) {
        for (int j = 0; j < n; ++j) {
            if (initial[i][j] == 0) {
                return n - i;  // Row from bottom
            }
        }
    }
    return 0;  // Should never happen if blank tile exists
}

// Main solvability check function
bool isSolvable() {
    int idx = 0;
    // Flatten puzzle into 1D ignoring the zero tile
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (initial[i][j] != 0)
                flatten[idx++] = initial[i][j];

    int invCount = mergesort(flatten, 0, n * n - 2);
    int blank_row = find_blankRow_pos();

    if (n % 2 == 1) {
        // For odd grid, puzzle is solvable if inversion count even
        return (invCount % 2 == 0);
    } else {
        // For even grid, solvability depends on blank row and inversions
        return ((invCount + blank_row) % 2 == 0);
    }
}
