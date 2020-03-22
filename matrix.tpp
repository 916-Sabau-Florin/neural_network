#pragma once
#include <iostream>
#include <initializer_list>
#include <vector>
#include <functional>

template<class T>
class matrix
{
public:
    matrix(size_t n,size_t m)
    {
        rows=n;
        cols=m;
        elem.resize(n);
        for(auto &x:elem)
            x.resize(m);
    }

    size_t nrRows() const { return rows; }
    size_t nrCols() const { return cols; }

    std::vector<T>& operator[](const int &index) { return elem[index]; }

    T at(size_t i,size_t j) const
    {
        if(i>rows-1||i<0||j>cols-1||j<0)
        {
            std::cerr<<"INVALID AT\n";
            exit(EXIT_FAILURE);
        }
        return elem[i][j];
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
                elem[r][c]=x;
                c++;
            }
            c=0;
            r++;
        }
    }

    void operator=(const std::vector<T> &v)
    {
        if(cols*rows!=v.size())
        {
            std::cerr<<"INVALID EQUAL VECTOR\n";
            exit(EXIT_FAILURE);
        }

        for(int i=0;i<rows;i++)
            for(int j=0;j<cols;j++)
                elem[i][j]=v[i*rows+j];
    }

    matrix<T> apply(std::function<T(T)> fn)
    {
        matrix<T> m(rows,cols);
        for(int i=0;i<rows;i++)
            for(int j=0;j<cols;j++)
                m[i][j]=fn(elem[i][j]);
        return m;
    }

    matrix<T> transpose()
    {
        matrix<T> m(cols,rows);
        for(size_t i=0;i<rows;i++)
            for(size_t j=0;j<cols;j++)
                m[j][i]=elem[i][j];
        //(*this)=m;
        return m;
    }

private:
    size_t rows=0,cols=0;
    std::vector<std::vector<T>> elem;
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
                prod[i][j]+=left.at(i,k)*right.at(k,j);
    return prod;
}

template <class T>
const matrix<T> operator+(const matrix<T> &left ,const matrix<T> &right)
{
    if(left.nrRows()!=right.nrRows()||left.nrCols()!=right.nrCols())
    {
        std::cerr<<"INVALID ADDITION\n";
        exit(EXIT_FAILURE);
    }

    matrix<T> sum(left.nrRows(),left.nrCols());
    for(size_t i=0;i<sum.nrRows();i++)
        for(size_t j=0;j<sum.nrCols();j++)
            sum[i][j]=left.at(i,j)+right.at(i,j);
    return sum;
}

template <class T>
matrix<T> hadamard(const matrix<T> &left,const matrix<T> &right)
{
    if(left.nrRows()!=right.nrRows()||left.nrCols()!=right.nrCols())
    {
        std::cerr<<"INVALID HADAMARD\n";
        exit(EXIT_FAILURE);
    }

    matrix<T> prod(left.nrRows(),left.nrCols());
    for(size_t i=0;i<prod.nrRows();i++)
        for(size_t j=0;j<prod.nrCols();j++)
            prod[i][j]=left.at(i,j)*right.at(i,j);
    return prod;
}

template <class T>
matrix<T> identity(const size_t &n)
{
    matrix<T> m(n,n);
    for(int i=0;i<n;i++)
        m[i][i]=1;
    return m;
}
