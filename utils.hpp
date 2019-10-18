#include <cmath>
#include <string>
#include "func.hpp"

std::string loadingBar(int current,int total,int siz);

double _sigmoid(double x);
double _sigmoid_delta(double x);
double _quadratic(const matrix<double> &output, const matrix<double> &expected);
matrix<double> _quadratic_delta(const matrix<double> &output, const matrix<double> &expected);


extern fn sigmoid;

extern cost_fn quadratic;

