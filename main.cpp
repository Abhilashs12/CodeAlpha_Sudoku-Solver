#include <iostream>
#include <vector>

using namespace std;

const int SIZE = 9;


void printGrid(const vector<vector<int>>& grid) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}


bool isSafe(const vector<vector<int>>& grid, int row, int col, int num) {
    // Check if the number is not repeated in the row
    for (int x = 0; x < SIZE; ++x) {
        if (grid[row][x] == num) {
            return false;
        }
    }

    // Check if the number is not repeated in the column
    for (int x = 0; x < SIZE; ++x) {
        if (grid[x][col] == num) {
            return false;
        }
    }

    // Check if the number is not repeated in the 3x3 sub-grid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

// Function to solve the Sudoku using backtracking
bool solveSudoku(vector<vector<int>>& grid) {
    int row, col;
    bool empty = false;

    // Find an empty cell
    for (row = 0; row < SIZE; ++row) {
        for (col = 0; col < SIZE; ++col) {
            if (grid[row][col] == 0) {
                empty = true;
                break;
            }
        }
        if (empty) break;
    }

    // If there is no empty cell left, the Sudoku is solved
    if (!empty) return true;

    // Try placing numbers from 1 to 9 in the empty cell
    for (int num = 1; num <= SIZE; ++num) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            if (solveSudoku(grid)) {
                return true;
            }

            // If placing num doesn't lead to a solution, reset and try next number
            grid[row][col] = 0;
        }
    }

    return false;
}

int main() {
    vector<vector<int>> grid = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (solveSudoku(grid)) {
        cout << "Sudoku solved successfully!" << endl;
        printGrid(grid);
    } else {
        cout << "No solution exists." << endl;
    }

    return 0;
}
