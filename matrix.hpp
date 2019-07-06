#include <initializer_list>

template<class T>
class matrix
{
public:
    matrix(const matrix<T> &m)
    {
        rows=m.nrRows();
        cols=m.nrCols();
        elem=new T*[rows+1];

        for(size_t i=0;i<=rows;i++)
            elem[i]= new T[cols+1];


        for(int i=1;i<=rows;i++)
            for(int j=1;j<=cols;j++)
                elem[i][j]=m.at(i,j);
    }


    matrix(size_t n,size_t m)
    {
        rows=n;
        cols=m;
        elem=new T*[rows+1];

        for(size_t i=0;i<=rows;i++)
            elem[i]= new T[cols+1];

        for(size_t i=0;i<=rows;i++)
            for(size_t j=0;j<=cols; j++)
                elem[i][j]=T();
    }

    ~matrix()
    {
        for(size_t i=0;i<=rows;i++)
            delete [] elem[i];
        delete [] elem;
    }

    size_t nrRows() const { return rows; }
    size_t nrCols() const { return cols; }

    T* operator[](const int &index) { return elem[index]; }

    T at(const size_t &i,const size_t &j) const { return elem[i][j]; }


    void operator=(std::initializer_list< std::initializer_list<T> > ll)
    {
        size_t r=1,c=1;
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
            c=1;
            r++;
        }
    }
    void operator=(matrix<T> m)
    {
        for(size_t i=0;i<=rows;i++)
            delete [] elem[i];
        delete [] elem;

        matrix(m.nrRows(),m.nrCols());
        for(int i=1;i<=rows;i++)
            for(int j=1;j<=cols;j++)
                elem[i][j]=m[i][j];
    }

    matrix<T> transpose()
    {
        matrix<T> m(cols,rows);
        for(size_t i=1;i<=rows;i++)
            for(size_t j=1;j<=cols;j++)
                m[j][i]=elem[i][j];
        //(*this)=m;
        return m;
    }

private:
    size_t rows=0,cols=0;
    T **elem=nullptr;
};

template <class T>
std::ostream& operator<<(std::ostream &os , matrix<T> m)
{
    for(int i=1;i<=m.nrRows();i++)
    {
        for(int j=1;j<=m.nrCols();j++)
            os<<m[i][j]<<' ';
        os<<std::endl;
    }
    return os;
}


template <class T>
matrix<T> operator*(matrix<T> left,matrix<T> right)
{
    if(left.nrCols()!=right.nrRows())
    {
        std::cerr<<"INVALID MULTIPLICATION\n";
        exit(EXIT_FAILURE);
    }

    int kMax=left.nrCols();
    matrix<T> prod(left.nrRows(),right.nrCols());

    for(size_t i=1;i<=prod.nrRows();i++)
        for(size_t j=1;j<=prod.nrCols();j++)
            for(size_t k=1;k<=kMax;k++)
                prod[i][j]+=left[i][k]*right[k][j];
    return prod;
}

template <class T>
matrix<T> operator+(matrix<T> left,matrix<T> right)
{
    if(left.nrRows()!=right.nrRows()||left.nrCols()!=right.nrCols())
    {
        std::cerr<<"INVALID ADDITION\n";
        exit(EXIT_FAILURE);
    }

    matrix<T> sum(left.nrRows(),left.nrCols());
    for(size_t i=1;i<=sum.nrRows();i++)
        for(size_t j=1;j<=sum.nrCols();j++)
            sum[i][j]=left[i][j]+right[i][j];
    return sum;
}

template <class T>
matrix<T> hadamard(matrix<T> left,matrix<T> right)
{
    if(left.nrRows()!=right.nrRows()||left.nrCols()!=right.nrCols())
    {
        std::cerr<<"INVALID HADAMARD\n";
        exit(EXIT_FAILURE);
    }

    matrix<T> prod(left.nrRows(),left.nrCols());
    for(size_t i=1;i<=prod.nrRows();i++)
        for(size_t j=1;j<=prod.nrCols();j++)
            prod[i][j]=left[i][j]*right[i][j];
    return prod;
}

template <class T>
matrix<T> identity(const size_t &n)
{
    matrix<T> m(n,n);
    for(int i=1;i<=n;i++)
        m[i][i]=1;
    return m;
}
