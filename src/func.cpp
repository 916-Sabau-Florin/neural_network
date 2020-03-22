#pragma once
#include "func.hpp"

namespace nn {

fn::fn()
{

}

fn::fn(std::function<double(double)> F,std::function<double(double)> dF)
{
    this->f = F;
    this->df= dF;
}

/*fn::fn(std::function<matrix<double>(const matrix<double> &)> F, std::function<matrix<double>(const matrix<double> &)> dF )
{
    this->f=F;
    this->df=dF;
}*/

matrix<double> fn::operator()(const matrix<double> &x)
{
    return x.apply(f);
}

matrix<double> fn::delta(const matrix<double> &x)
{
    return x.apply(df);
}


/*matrix<double> fn::lift(const &matrix<double> &m, std::function<double(double)> f)
{
    return f()
}*/

cost_fn::cost_fn()
{

}

cost_fn::cost_fn(std::function<double(const matrix<double> &,const matrix<double> &)> F, std::function<matrix<double>(const matrix<double> &,const matrix<double> &)> dF )
{
    this->f=F;
    this->df=dF;
}

double cost_fn::operator()(const matrix<double> &output,const matrix<double> &expected)
{
    return f(output,expected);
}

matrix<double> cost_fn::delta(const matrix<double> &output,const matrix<double> &expected)
{
    return df(output,expected);
}

}



