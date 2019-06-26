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


