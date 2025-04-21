#include <eigen3/Eigen/Eigen>
#include <iostream>

int main() {
    Eigen::Matrix<int, 3, 4> me;
    Eigen::Matrix<double, 3, 4> mat;
    mat << 1, 2, 3, 4,
           5, 6, 7, 8,
           9, 10, 11, 12;

    // Accessing a specific element (row, col)
    std::cout << "Element at (1,2): " << mat(1,2) << std::endl;

    // Modify an element
    mat(2, 3) = 12;
    std::cout << "Modified matrix:\n" << mat << std::endl;
    return 0;
}
