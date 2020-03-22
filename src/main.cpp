#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>
#include <neural_network.hpp>
#include <idx_format.hpp>

std::ifstream images("train-images.idx3-ubyte",std::fstream::binary);
std::ifstream labels("train-labels.idx1-ubyte",std::fstream::binary);
std::ifstream ibrain("trainedSmecher.txt");
std::ofstream obrain("trainedSmecher2.txt");


nn::neural_network NN({784,64,32,10},
                  {nn::sigmoid,nn::sigmoid,nn::sigmoid,nn::sigmoid},
                   nn::quadratic);
std::vector<std::pair<nn::matrix<double>,nn::matrix<double>> > data;



void test(int nr)
{
    int correct=0;
    for(int i=0;i<nr;i++)
    {
        NN.feedforward(data[i].first.toVector());
        auto output=NN.getOutput().toVector();
        int imax=0;
        for(int i=0;i<10;i++)
        {
            if(output[i]>output[imax])
                imax=i;
        }
        int nr=0;
        for(int j=0;j<10;j++)
            if(data[i].second[{j,0}])
                nr=j;
        if(imax == nr)
            correct++;
    }
    std::cout<<(float)correct/(float)nr;
}

int main()
{
    nn::read_headers(images,labels);
    std::cout<<"Loading database...\n";
    for(int i=0;i<50000;i++)
    {
        auto p=nn::next_image(images,labels);
        nn::matrix<double> expected(10,1);
        expected[{p.second,0}]=1;
        data.push_back({p.first,expected});
    }
    std::cout<<"Done loading :)\n";

    shuffle(data.begin(),data.end(),std::default_random_engine(0));

    NN.randomize(-1.0,1.0);
    NN.gradientDescent(data,2,10);
    NN.toFile(obrain);
    //nn.fromFile(ibrain);
    test(10000);

}
