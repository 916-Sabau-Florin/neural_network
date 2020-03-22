#include "utils.hpp"

std::string loadingBar(int current,int total,int siz)
{
    std::string bar="[";
    for(int i=1;i<=siz;i++)
    {
        if(current/(total/siz)>=i)
            bar.push_back('#');
        else bar.push_back(' ');
    }
    bar.push_back(']');
    return bar;
}

double _sigmoid(double x)
{
	return 1/(1+exp(-x));
}

double _sigmoid_delta(double x)
{
    return _sigmoid(x)*(1-_sigmoid(x));
}

double _quadratic(const matrix<double> &output, const matrix<double> &expected)
{
	return (0.5d*((output-expected).apply( [](double x) { return x*x; }).sum()));
}

matrix<double> _quadratic_delta(const matrix<double> &output, const matrix<double> &expected)
{
	return (output-expected);
}

fn sigmoid(_sigmoid,_sigmoid_delta);

cost_fn quadratic(_quadratic ,_quadratic_delta);

