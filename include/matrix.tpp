#pragma once
#include <iostream>
#include <initializer_list>
#include <vector>
#include <cmath>
#include <functional>

namespace nn {

template<class T>
class matrix
{
public:

    matrix() {}

    matrix(size_t n,size_t m)
    {
        rows=n;
        cols=m;
        elem.resize(n*m);
    }

    matrix(size_t n,size_t m, const std::vector<T> &v)
    {
        rows=n;
        cols=m;
        elem.resize(n*m);

        if(cols*rows!=v.size())
        {
            std::cerr<<"INVALID VECTOR CONSTRUCTOR\n";
            exit(EXIT_FAILURE);
        }

        elem=v;
    }

    size_t nrRows() const { return rows; }
    size_t nrCols() const { return cols; }

    T& operator[](const std::pair<int,int> &indices) { return elem[indices.second*rows+indices.first]; }


    std::vector<T> toVector()
    {
        std::vector<T> v;
        for(int i=0;i<rows*cols;i++)
            v.push_back(elem[i]);
        return v;
    }

    T at(size_t i,size_t j) const
    {
        if(i>rows-1||i<0||j>cols-1||j<0)
        {
            std::cerr<<"INVALID AT\n";
            exit(EXIT_FAILURE);
        }

        return elem[j*rows+i];
    }

    void operator=(std::initializer_list< std::initializer_list<T> > ll)
    {
        size_t r=0,c=0;
        if(ll.size()!=rows)
        {
            std::cerr<<"INVALID INIT LIST\n";
            exit(EXIT_FAILURE);
        }

        for(auto l:ll)
        {
            if(l.size()!=cols)
            {
                std::cerr<<"INVALID INIT LIST\n";
                exit(EXIT_FAILURE);
            }
            for(auto x:l)
            {
                elem[r+c*rows]=x;
                c++;
            }
            c=0;
            r++;
        }
    }

    T sum()
    {
        T s=0;
        for(int i=0;i<rows*cols;i++)
            s+=elem[i];
        return s;
    }

    void operator=(const std::vector<T> &v)
    {
        if(cols*rows!=v.size())
        {
            std::cerr<<"INVALID EQUAL VECTOR\n";
            exit(EXIT_FAILURE);
        }
        elem=v;
    }

    matrix<T> apply(std::function<T(T)> fn) const
    {
        matrix<T> m(rows,cols);
        for(int i=0;i<rows;i++)
            for(int j=0;j<cols;j++)
                m[{i,j}]=fn(elem[i+j*rows]);
        return m;
    }

    matrix<T> transpose()
    {
        matrix<T> m(cols,rows);
        for(size_t i=0;i<rows;i++)
            for(size_t j=0;j<cols;j++)
                m[{j,i}]=elem[i+j*rows];
        //(*this)=m;
        return m;
    }

private:
    size_t rows=0,cols=0;
    std::vector<T> elem;
};

template <class T>
std::ostream& operator<<(std::ostream &os ,matrix<T> m)
{
    for(int i=0;i<m.nrRows();i++)
    {
        for(int j=0;j<m.nrCols();j++)
            os<<m.at(i,j)<<' ';
        os<<std::endl;
    }
    return os;
}

template <class T>
bool operator==(const matrix<T> &left,const matrix<T> &right)
{
    if(left.nrCols()!=right.nrCols()||left.nrRows()!=right.nrRows())
        return 0;

    for(int i=0;i<left.nrRows();i++)
        for(int j=0;j<left.nrCols();j++)
            if(left.at(i,j)!=right.at(i,j))
                return 0;
    return 1;
}

template <class T>
const matrix<T> operator*(const matrix<T> &left,const matrix<T> &right)
{
    if(left.nrCols()!=right.nrRows())
    {
        std::cerr<<"INVALID MULTIPLICATION\n";
        exit(EXIT_FAILURE);
    }

    int kMax=left.nrCols();
    matrix<T> prod(left.nrRows(),right.nrCols());

    for(size_t i=0;i<prod.nrRows();i++)
        for(size_t j=0;j<prod.nrCols();j++)
            for(size_t k=0;k<kMax;k++)
                prod[{i,j}]+=left.at(i,k)*right.at(k,j);
    return prod;
}

template<class T>
const matrix<T> operator*(T left,const matrix<T> &right)
{
    matrix<T> prod(right.nrRows(),right.nrCols());
    for(size_t i=0;i<right.nrRows();i++)
        for(size_t j=0;j<right.nrCols();j++)
            prod[{i,j}]=left*right.at(i,j);
    return prod;
}

template <class T>
const matrix<T> operator+(const matrix<T> &left ,const matrix<T> &right)
{
    if(left.nrRows()!=right.nrRows()||left.nrCols()!=right.nrCols())
    {
        std::cerr<<"INVALID ADDITION\n";
        std::cerr<<left.nrRows()<<' '<<left.nrCols()<<'\n';
        std::cerr<<right.nrRows()<<' '<<right.nrCols()<<'\n';
        exit(EXIT_FAILURE);
    }

    matrix<T> sum(left.nrRows(),left.nrCols());
    for(size_t i=0;i<sum.nrRows();i++)
        for(size_t j=0;j<sum.nrCols();j++)
            sum[{i,j}]=left.at(i,j)+right.at(i,j);
    return sum;
}

template <class T>
const matrix<T> operator-(const matrix<T> &left ,const matrix<T> &right)
{
    if(left.nrRows()!=right.nrRows()||left.nrCols()!=right.nrCols())
    {
        std::cerr<<"INVALID SUBSTRACTION\n";
        exit(EXIT_FAILURE);
    }

    matrix<T> diff(left.nrRows(),left.nrCols());
    for(size_t i=0;i<diff.nrRows();i++)
        for(size_t j=0;j<diff.nrCols();j++)
            diff[{i,j}]=left.at(i,j)-right.at(i,j);
    return diff;
}

template <class T>
matrix<T> hadamard(const matrix<T> &left,const matrix<T> &right)
{
    if(left.nrRows()!=right.nrRows()||left.nrCols()!=right.nrCols())
    {
        std::cerr<<"INVALID HADAMARD\n";
        std::cerr<<left.nrRows()<<' '<<left.nrCols()<<'\n';
        std::cerr<<right.nrRows()<<' '<<right.nrCols()<<'\n';
        exit(EXIT_FAILURE);
    }

    matrix<T> prod(left.nrRows(),left.nrCols());
    for(size_t i=0;i<prod.nrRows();i++)
        for(size_t j=0;j<prod.nrCols();j++)
            prod[{i,j}]=left.at(i,j)*right.at(i,j);
    return prod;
}

template <class T>
double twoNorm(matrix<double> v)
{
    double sum=0;
    for(int i=0;i<v.nrRows();i++)
        sum=sum+v[{i,0}]*v[{i,0}];
    return std::sqrt(sum);
}

template <class T>
matrix<T> outer(const matrix<T> &left, const matrix<T> &right)
{
    if(left.nrCols()!=1 || right.nrCols()!=1)
    {
        std::cerr<<"INVALID OUTER\n";
        exit(EXIT_FAILURE);
    }

    matrix<T> prod(left.nrRows(), right.nrRows());
    for(int i=0;i<left.nrRows();i++)
        for(int j=0;j<right.nrRows();j++)
            prod[{i,j}]=left.at(i,0)*right.at(j,0);
    return prod;
}


template <class T>
matrix<T> identity(int n)
{
    matrix<T> m(n,n);
    for(int i=0;i<n;i++)
        m[{i,i}]=1;
    return m;
}

}
