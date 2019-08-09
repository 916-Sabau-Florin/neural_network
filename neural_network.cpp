#pragma once

#include <vector>
#include <functional>
#include <cmath>

#include "matrix.tpp"
#include "random.tpp"
#include "neural_network.hpp"


neural_network::neural_network(const std::vector<int> &l, std::function<double(double)> activ)
{
	nrLayers=l.size();
	layers=l;
	activation=activ;
    weights.push_back(matrix<double>(0,0));
	for(int i=1; i<nrLayers; i++)
		weights.push_back(matrix<double>(l[i-1],l[i]));
	for(auto x:l)
	{
		neurons.push_back(matrix<double>(1,x));
		biases.push_back(matrix<double>(1,x));
	}
}

void neural_network::randomize(double m,double M)
{
	for(int i=1; i<nrLayers; i++)
	{
		weights[i]=rng.getReal(m,M,weights[i].nrRows()*weights[i].nrCols());
		biases[i]=rng.getReal(m,M,layers[i]);
	}
}

void neural_network::evaluate(const std::vector<double> &input)
{
	neurons[0]=input;
	for(int i=1; i<nrLayers; i++)
	{
		neurons[i]=neurons[i-1]*weights[i]+biases[i];
		neurons[i]=neurons[i].apply(activation);
	}
}

matrix<double> neural_network::getOutput()
{
    return neurons[nrLayers-1];
}


double sigmoid(double x)
{
	return 1/(1+exp(-x));
}

double quadratic(const matrix<double> &output, const matrix<double> &expected)
{
	double sum=0;
	for(int i=0; i<output.nrCols(); i++)
		sum+=(output.at(0,i)-expected.at(0,i))*(output.at(0,i)-expected.at(0,i));
	return sum/2.0f;
}


