#pragma once
#include <functional>
#include <cmath>
#include <matrix.tpp>

namespace nn {

class fn
{
public:
    fn();
    fn(std::function<double(double)> F, std::function<double(double)> dF);
 //   fn(std::function<matrix<double>(const matrix<double> &)> F, std::function<matrix<double>(const matrix<double> &)> dF );

    matrix<double> operator()(const matrix<double>& x);

    matrix<double> delta(const matrix<double>& x);

private:
    std::function<double(double)> f;
    std::function<double(double)> df;
};

class cost_fn
{
public:
    cost_fn();
    cost_fn(std::function<double(const matrix<double> &,const matrix<double> &)> F, std::function<matrix<double>(const matrix<double> &,const matrix<double> &)> dF );

    double operator()(const matrix<double>& output,const matrix<double> &expected);

    matrix<double> delta(const matrix<double>& output,const matrix<double> &expected);

private:
    std::function<double(const matrix<double>&,const matrix<double>&)> f;
    std::function<matrix<double>(const matrix<double>&,const matrix<double> &)> df;
};


}

//matrix<double> lift(const &matrix<double> &m, std::function<double(double)> f);


//fn relu(relu,relu_delta);
//fn softplus(softplus,softplus_delta);
//fn quadratic(_quadratic,_quadratic_delta);


