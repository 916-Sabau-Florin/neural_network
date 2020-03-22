#pragma once
#include <functional>
#include "random.tpp"
#include "matrix.tpp"

class neural_network
{
public:
    neural_network(const std::vector<int> &l, std::function<double(double)> activ);

    void randomize(double m,double M);

    void evaluate(const std::vector<double> &input);

    matrix<double> getOutput();
private:
    int nrLayers;
    std::vector<int> layers;
    std::vector<matrix<double>> neurons;
    std::vector<matrix<double>> weights;
    std::vector<matrix<double>> biases;

    randomWrapper rng;

    std::function<double(double)> activation;
//    std::function<double(const matrix<double>&,const matrix<double>&)> cost;
};

double sigmoid(double x);
double quadratic(const matrix<double> &output, const matrix<double> &expected);



