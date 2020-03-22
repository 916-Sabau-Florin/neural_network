#pragma once
#include <random>
#include <chrono>
#include <vector>

namespace nn {

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
};

}

