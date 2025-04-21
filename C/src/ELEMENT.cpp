#include <iostream>
#include <vector>
#include <algorithm>  // Required for max_element

using namespace std;

int main() {
    vector<double> values = {0.2, 0.5, -0.1, 0.8,4000};  // List of Q-values

     auto max_it = max_element(values.begin(), values.end());
    cout << "Max value: " << *max_it << endl;  // Dereference pointer to get value

    return 0;
}
