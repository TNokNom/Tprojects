#include <iostream>
#include <vector>
#include <algorithm> // For max_element

using namespace std;

// Constants
const int GRID_SIZE = 3;   // 3x3 grid
const int ACTIONS = 4;     // LEFT, RIGHT, UP, DOWN
const double ALPHA = .1;  // Learning rate
const double GAMMA = 0.9;  // Discount factor

// Q-table
vector<vector<vector<double>>> Q(GRID_SIZE, vector<vector<double>>(GRID_SIZE, vector<double>(ACTIONS, 0.0)));


void updateQ (int x, int y, int action, int next_x, int next_y, double reward) {
    double max_future_q =* max_element(Q[next_x][next_y].begin(), Q[next_x][next_y].end());

    // Q-learning update rule
    Q[x][y][action] += ALPHA * (reward + GAMMA * max_future_q - Q[x][y][action]);
}

// Function to print the Q-table
void printQTable() {
    cout << "\nQ-table:\n";
    for (int x = 0; x < GRID_SIZE; x++) {
        for (int y = 0; y < GRID_SIZE; y++) {
            cout << "Q(" << x << "," << y << "): ";
            for (double q : Q[x][y]) {
                cout << q << " ";
            }
            cout << endl;
        }
    }
}

int main() {
    // Simulating one step: Start at (0,0), move RIGHT to (0,1)
    int x = 0, y = 2;
    int action = 1; // RIGHT
    int next_x = 0, next_y = 0;
    double reward = -0.1;

    // Update Q-table
    updateQ(x, y, action, next_x, next_y, reward);

    // Print updated Q-table
    printQTable();
    return 0;
}
