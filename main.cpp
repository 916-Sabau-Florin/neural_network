#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>
#include "neural_network.hpp"
#include "idx_format.hpp"

std::ifstream images("train-images.idx3-ubyte",std::fstream::binary);
std::ifstream labels("train-labels.idx1-ubyte",std::fstream::binary);
std::ifstream ibrain("trainedSmecher.txt");
std::ofstream obrain("trainedSmecher2.txt");


neural_network nn({784,64,32,10},
                  {sigmoid,sigmoid,sigmoid,sigmoid},
                   quadratic);
std::vector<std::pair<matrix<double>,matrix<double>> > data;



void test(int nr)
{
    int correct=0;
    for(int i=0;i<nr;i++)
    {
        nn.feedforward(data[i].first.toVector());
        auto output=nn.getOutput().toVector();
        int imax=0;
        for(int i=0;i<10;i++)
        {
            if(output[i]>output[imax])
                imax=i;
        }
        int nr=0;
        for(int j=0;j<10;j++)
            if(data[i].second[j][0])
                nr=j;
        if(imax == nr)
            correct++;
    }
    std::cout<<(float)correct/(float)nr;
}






int main()
{
    read_headers(images,labels);
    std::cout<<"Loading database...\n";
    for(int i=0;i<50000;i++)
    {
        auto p=next_image(images,labels);
        matrix<double> expected(10,1);
        expected[p.second][0]=1;
        data.push_back({p.first,expected});
    }
    std::cout<<"Done loading :)\n";

    shuffle(data.begin(),data.end(),std::default_random_engine(0));

    nn.randomize(-1.0,1.0);
    nn.gradientDescent(data,25,10);
    nn.toFile(obrain);
    //nn.fromFile(ibrain);
    test(10000);

}
