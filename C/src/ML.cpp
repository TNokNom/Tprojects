#include <iostream>
#include <vector>

using namespace std;
double compute_loss(const vector<double>& y_pred,const vector<double>& y_true) {
double loss = 0.0;
for (size_t i = 0; i < y_pred.size(); i++){
  loss += (y_pred[i] - y_true[i] ) * (y_pred[i] - y_true[i]);
}
return loss/y_pred.size();

}
void train(vector<double> &W, double &b,const vector<double> &X, const vector<double> &Y, double learning_rate, int epochs){
  for (int epoch = 0; epoch < epochs; epoch++) {
    vector<double> y_pred(X.size());
  }
}
