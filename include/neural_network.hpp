#pragma once
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <matrix.tpp>
#include <random.tpp>
#include <utils.hpp>

namespace nn {

class neural_network
{
public:
    neural_network(const std::vector<int> &l, std::vector<fn> activ , cost_fn cost);

// TO DO:
//  void addLayer(int l, fn activ);
//  void setCost(fn c);

    void randomize(double m,double M);

    void feedforward(const std::vector<double> &input);

    matrix<double> getOutput();

    void backpropagate(std::vector<matrix<double>> &input,const std::vector<matrix<double>> &expected, double learnRate);

    void gradientDescent(const std::vector<std::pair<matrix<double>,matrix<double> > > &data, int epochs, int batchSize);

    void toFile(std::ofstream &file);

    void fromFile(std::ifstream &file);

private:
    int nrLayers;
    std::vector<int> layers;
    std::vector<matrix<double>> neurons;
    std::vector<matrix<double>> weights;
    std::vector<matrix<double>> biases;

    randomWrapper RNG;

    std::vector<fn> activation;
    cost_fn cost;
};


}

