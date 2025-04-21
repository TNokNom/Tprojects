#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <thread>
#include <chrono> // For sleep
#include <numeric>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include <imgui_back/imgui_impl_glfw.h>
#include <imgui_back/imgui_impl_opengl3.h>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

// Constants
const int Grid_Size = 5;
const int ACTIONS = 4;
double ALPHA = 0.3, GAMMA = 0.9, EPSILON = 0.2;
const int STEP_DELAY_MS = 200;  // Delay per step to visualize movement

// Q-table
vector<vector<vector<double>>> Q(5, vector<vector<double>>(5, vector<double>(ACTIONS, 0.0)));

// Possible actions
enum Action { LEFT, RIGHT, UP, DOWN };

// Agent position
int agent_x = 0, agent_y = 0;

// Camera position
float cameraX = 5 / 2.0, cameraY = 7.0, cameraZ = 5 + 3.0;

// Choose action using ε-greedy policy
Action chooseAction(int x, int y) {
    if ((rand() / (double)RAND_MAX) < EPSILON) {
        return static_cast<Action>(rand() % ACTIONS);
    } else {
        return static_cast<Action>(max_element(Q[x][y].begin(), Q[x][y].end()) - Q[x][y].begin());
    }
}

// Get next state
pair<int, int> getNextState(int x, int y, Action action) {
    if (action == LEFT)  y = max(0, y - 1);
    if (action == RIGHT) y = min(5 - 1, y + 1);
    if (action == UP)    x = max(0, x - 1);
    if (action == DOWN)  x = min(5 - 1, x + 1);
    return {x, y};
}

// Get reward
double getReward(int x, int y) {
    return (x == 5 - 1 && y == 5 - 1) ? 1.0 : -0.1;
}

// Update Q-values
void updateQ(int x, int y, Action action, int next_x, int next_y, double reward) {
    double max_future_q = *max_element(Q[next_x][next_y].begin(), Q[next_x][next_y].end());
    Q[x][y][action] += ALPHA * (reward + GAMMA * max_future_q - Q[x][y][action]);
}

// Train agent in real-time visualization
void trainStep() {
    for (int episode = 0; episode < 500; episode++) {
        agent_x = 0, agent_y = 0;  // Reset agent position at start of episode

        while (!(agent_x == 5 - 1 && agent_y == 5 - 1)) {  // Until goal is reached
            Action action = chooseAction(agent_x, agent_y);
            pair<int, int> next = getNextState(agent_x, agent_y, action);
            int nx = next.first, ny = next.second;
            double reward = getReward(nx, ny);
            updateQ(agent_x, agent_y, action, nx, ny, reward);

            // Move agent
            agent_x = nx;
            agent_y = ny;

            // Pause to allow visualization
            sleep_for(milliseconds(STEP_DELAY_MS));
        }

        // Reduce exploration rate
        EPSILON = max(0.01, EPSILON * 0.995);
    }
}

// OpenGL - 3D Ground
void drawGround() {
    glColor3f(0.3f, 0.7f, 0.3f);
    glBegin(GL_QUADS);
    glVertex3f(0, 0, 0);
    glVertex3f(5, 0, 0);
    glVertex3f(5, 0, 5);
    glVertex3f(0, 0, 5);
    glEnd();
}

// OpenGL - 3D Cube Drawing (Replaces `glutSolidCube`)
void drawCube(float size) {
    float half = size / 2.0f;
    glBegin(GL_QUADS);

    // Front
    glVertex3f(-half, -half, half);
    glVertex3f(half, -half, half);
    glVertex3f(half, half, half);
    glVertex3f(-half, half, half);

    // Back
    glVertex3f(-half, -half, -half);
    glVertex3f(-half, half, -half);
    glVertex3f(half, half, -half);
    glVertex3f(half, -half, -half);

    // Left
    glVertex3f(-half, -half, -half);
    glVertex3f(-half, -half, half);
    glVertex3f(-half, half, half);
    glVertex3f(-half, half, -half);

    // Right
    glVertex3f(half, -half, -half);
    glVertex3f(half, half, -half);
    glVertex3f(half, half, half);
    glVertex3f(half, -half, half);

    // Top
    glVertex3f(-half, half, -half);
    glVertex3f(-half, half, half);
    glVertex3f(half, half, half);
    glVertex3f(half, half, -half);

    // Bottom
    glVertex3f(-half, -half, -half);
    glVertex3f(half, -half, -half);
    glVertex3f(half, -half, half);
    glVertex3f(-half, -half, half);

    glEnd();
}

void drawAgent() {
    glColor3f(1.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(agent_y + 0.5, 0.5, agent_x + 0.5);
    drawCube(0.8);  // Manual cube instead of `glutSolidCube`
    glPopMatrix();
}

// OpenGL - Camera Setup
void setupCamera() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cameraX, cameraY, cameraZ, 5 / 2, 0, 5 / 2, 0, 1, 0);
}

// Visualization Loop
void visualize() {
    if (!glfwInit()) return;
    GLFWwindow* window = glfwCreateWindow(800, 600, "Q-learning 3D", NULL, NULL);
    glfwMakeContextCurrent(window);
    glewInit();

    thread training_thread(trainStep);  // Run training in parallel

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        setupCamera();

        drawGround();
        drawAgent();

        glfwSwapBuffers(window);
    }

    training_thread.join();
    glfwDestroyWindow(window);
    glfwTerminate();
}

int main() {
    srand(time(0));
    visualize();
    return 0;
}
