#include <iostream>
#include <vector>
#include <cstdlib>  // For rand()
#include <ctime>    // For seeding randomness
#include <algorithm> // For max_element

using namespace std;

// Constants
const int GRID_SIZE = 3;   // 3x3 grid
const int ACTIONS = 4;     // LEFT, RIGHT, UP, DOWN
const double ALPHA = 0.1;  // Learning rate
const double GAMMA = 0.9;  // Discount factor
const double EPSILON = 0.1; // Exploration rate
const int MAX_STEPS = 100;  // Max steps per episode

// Q-table
vector<vector<vector<double>>> Q(GRID_SIZE, vector<vector<double>>(GRID_SIZE, vector<double>(ACTIONS, 0.0)));

// Possible actions
enum Action { LEFT, RIGHT, UP, DOWN };

// Function to choose an action using ε-greedy policy
Action chooseAction(int x, int y) {
    if ((rand() / (double)RAND_MAX) < EPSILON) {
        return static_cast<Action>(rand() % ACTIONS); // Random action (exploration)
    } else {
        return static_cast<Action>(max_element(Q[x][y].begin(), Q[x][y].end()) - Q[x][y].begin()); // Best action (exploitation)
    }
}

// Function to get next state based on action
pair<int, int> getNextState(int x, int y, Action action) {
    if (action == LEFT)  y = max(0, y - 1);
    if (action == RIGHT) y = min(GRID_SIZE - 1, y + 1);
    if (action == UP)    x = max(0, x - 1);
    if (action == DOWN)  x = min(GRID_SIZE - 1, x + 1);
    return {x, y};
}

// Function to get reward
double getReward(int x, int y) {
    return (x == GRID_SIZE - 1 && y == GRID_SIZE - 1) ? 1.0 : -0.1; // Reward for goal, penalty otherwise
}

// Function to update Q-values
void updateQ(int x, int y, Action action, int next_x, int next_y, double reward) {
    double max_future_q = *max_element(Q[next_x][next_y].begin(), Q[next_x][next_y].end());
    Q[x][y][action] += ALPHA * (reward + GAMMA * max_future_q - Q[x][y][action]);
}

// Function to train agent over multiple episodes
void train(int episodes) {
    for (int episode = 0; episode < episodes; episode++) {
        int x = 0, y = 0; // Start at top-left
        int steps = 0; // Step counter

        while (!(x == GRID_SIZE - 1 && y == GRID_SIZE - 1) && steps < MAX_STEPS) { // Stop if max steps reached
            Action action = chooseAction(x, y);
            pair<int, int> next = getNextState(x, y, action);
            int nx = next.first, ny = next.second;
            double reward = getReward(nx, ny);
            updateQ(x, y, action, nx, ny, reward);
            x = nx;
            y = ny;
            steps++; // Increase step count
        }
    }
}

// Function to print Q-table
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
    srand(time(0)); // Seed randomness
    train(10000);    // Train for 100 episodes
    printQTable();  // Print final Q-table
    return 0;
}
