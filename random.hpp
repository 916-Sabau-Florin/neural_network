<<<<<<< HEAD
#include <random>
#include <chrono>
#include <vector>
#include <iostream>
class randomWrapper
{
public:

    randomWrapper()
    {
        unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
        generator.seed(seed);
    }

    template <class T>
    T get(T m, T M)
    {
        std::uniform_int_distribution<T> distribution(m,M);
        return distribution(generator);
    }

    template <class T>
    std::vector<T> get(T m, T M, size_t cnt)
    {
        std::uniform_int_distribution<T> distribution(m,M);

        std::vector<T> v;
        for(int i=0;i<cnt;i++)
            v.push_back(distribution(generator));
        return v;
    }


    template <class T>
    T getReal(T m,T M)
    {
        std::uniform_real_distribution<T> distribution(m,M);
        return distribution(generator);
    }

    template <class T>
    std::vector<T> getReal(T m, T M, size_t cnt)
    {
        std::uniform_real_distribution<T> distribution(m,M);

        std::vector<T> v;
        for(int i=0;i<cnt;i++)
            v.push_back(distribution(generator));
        return v;
    }


private:
    std::default_random_engine generator;
}rng;



=======
#include <random>
#include <chrono>

int randomInt(int m,int M)
{
    unsigned int seed= std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(m,M);
    return distribution(generator);
}

long long randomLongLong(long long m,long long M)
{
    unsigned int seed= std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<long long> distribution(m,M);
    return distribution(generator);
}

float randomFloat(float m,float M)
{
    unsigned int seed= std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_real_distribution<float> distribution(m,M);
    return distribution(generator);
}

double randomDouble(double m,double M)
{
    unsigned int seed= std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_real_distribution<double> distribution(m,M);
    return distribution(generator);
}


>>>>>>> 0852c8731a471954ee8fa4f99ddcb519badb8c97
