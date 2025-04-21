#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <eigen3/Eigen/Eigen>
#include <algorithm>

using namespace std;

const int GRID_SIZE = 9;
const int ACTIONS = 4;
const double ALPHA = 0.1;
const double GAMMA = 0.9;
const double EPSILON = 0.1;


Eigen::Matrix<double, 9,4> Qtable;


void eigen () {
    Qtable.setZero();  // Initialize all elements to zero

    // Modify one element
    Qtable(2, 0) = 42;

    // Print each element in "Q(row, col) value" format
    std::cout << "Qtable:\n";
    for (int x = 0; x < Qtable.rows(); x++) {
        for (int y = 0; y < Qtable.cols(); y++) {
            std::cout << "Q(" << x << "," << y << ") " << Qtable(x, y) << "  ";
        }
        std::cout << std::endl;  // Newline after each row
    }
}
    void Qvalue(int x, int y,int action, int next_x, int next_y, double reward) {
double max_futureq = *max_element(Qtable(next_x,next_y).begin(), Qtable(next_x, next_y).end() );

    }


void printQtable() {
vector<vector<vector<double>>> Q(GRID_SIZE, vector<vector<double>>(GRID_SIZE, vector<double>(ACTIONS, 0.0)));

  cout << "\nQ-table: \n";
  for (int x = 0; x < GRID_SIZE; x++){
    for (int y = 0; y < GRID_SIZE; y++ ) {
     cout << "Q("<< x << "," << y << "): ";
     for (double q : Q[x][y]){
       cout << q << " ";
     }
     cout << endl;
    }

}
}


  int main (){
    srand(time(0));

   // printQtable();
    eigen();

    return 0;
  }
