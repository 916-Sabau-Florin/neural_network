#pragma once

#include "neural_network.hpp"

neural_network::neural_network(const std::vector<int> &l, std::vector<fn> activ , cost_fn cst)
{
	nrLayers=l.size();
	layers=l;
	activation=activ;
	cost=cst;
    weights.push_back(matrix<double>(0,0));
	for(int i=1; i<nrLayers; i++)
		weights.push_back(matrix<double>(l[i],l[i-1]));
	for(auto x:l)
	{
		neurons.push_back(matrix<double>(x,1));
		biases.push_back(matrix<double>(x,1));
	}
}



void neural_network::randomize(double m,double M)
{
	for(int i=1; i<nrLayers; i++)
	{
		weights[i]=RNG.getReal(m,M,weights[i].nrRows()*weights[i].nrCols());
		biases[i]=RNG.getReal(m,M,layers[i]);
	}
}

void neural_network::feedforward(const std::vector<double> &input)
{
	neurons[0]=input;
	for(int i=1; i<nrLayers; i++)
		neurons[i]=weights[i]*activation[i-1](neurons[i-1])+biases[i];
	//neurons[nrLayers-1]=neurons[nrLayers-1].apply(activation);
}

matrix<double> neural_network::getOutput()
{
    return activation[nrLayers-1](neurons[nrLayers-1]);
}


void neural_network::backpropagate(std::vector<matrix<double>> &input, const std::vector<matrix<double>> &expected, double learnRate)
{
    int m=input.size();
    int L=nrLayers-1;
    std::vector<matrix<double>> delta_B(1);
    std::vector<matrix<double>> delta_W(1);

    for(int i=1;i<=L;i++)
    {
        delta_B.push_back(matrix<double>(layers[i],1));
        delta_W.push_back(matrix<double>(layers[i],layers[i-1]));
    }

    for(int i=0;i<m;i++)
    {
        this->feedforward(input[i].toVector());
        std::vector<matrix<double>> delta_Z(1);

        for(int j=1;j<=L;j++)
            delta_Z.push_back(matrix<double>(layers[j],1));


        for(int l=L;l>0;l--)
        {
            if(l==L) delta_Z[l]=hadamard(quadratic.delta(this->getOutput(),expected[i]), activation[L].delta(neurons[L]));
            else     delta_Z[l]=hadamard(weights[l+1].transpose()*delta_Z[l+1], activation[l].delta(neurons[l]));
            delta_B[l]=delta_B[l]+delta_Z[l];
            delta_W[l]=delta_W[l]+outer(delta_Z[l], activation[l-1](neurons[l-1]));
        }
    }

    for(int i=1;i<nrLayers;i++)
    {
        biases[i]=biases[i]-(learnRate/(double)m)*delta_B[i];
        weights[i]=weights[i]-(learnRate/(double)m)*delta_W[i];
    }
}

void neural_network::gradientDescent(const std::vector<std::pair<matrix<double>,matrix<double> > > &data, int epochs, int batchSize)
{
    std::vector<matrix<double> > minibatch_images;
    std::vector<matrix<double> > minibatch_labels;

    for(int i=1;i<=epochs;i++)
    {
        std::cout<<"EPOCH "<<i<<":\n";

        for(int k=0;k<data.size()/batchSize;k++)
        {
            double cst=0;
            for(int j=0;j<batchSize;j++)
            {
                auto p=data[j+k];
                minibatch_images.push_back(p.first);
                minibatch_labels.push_back(p.second);
                this->feedforward(p.first.toVector());
                cst+=quadratic(this->getOutput(),p.second);
            }
            this->backpropagate(minibatch_images,minibatch_labels,0.1);
            minibatch_images.clear();
            minibatch_labels.clear();
            std::cout<<k+1<<"/"<<data.size()/batchSize<<" batches "<<loadingBar(k+1,data.size()/batchSize,20)<<" Cost = "<<cst/batchSize<<'\r';
        }
        std::cout<<'\n';
    }
/*    for(int i=0;i<epochs*data.size()/batchSize;i++)
    {




        std::cout<<"Done "<<i+1<<" batches , cost: "<<cst/10.0<<std::endl;
    }
//    this->toFile(obrain); */
}

void neural_network::toFile(std::ofstream &file)
{
    file<<std::setprecision(10)<<std::fixed;
    file<<nrLayers<<'\n';
    for(auto l:layers)
        file<<l<<' ';
    file<<'\n';
    for(int i=0;i<nrLayers;i++)
    {
        for(int j=0;j<layers[i];j++)
            file<<biases[i][j][0]<<' ';
        file<<'\n';
    }
    file<<'\n';
    for(int i=1;i<nrLayers;i++)
    {
        for(int j=0;j<layers[i];j++)
        {
            for(int k=0;k<layers[i-1];k++)
                file<<weights[i][j][k]<<' ';
            file<<'\n';
        }
        file<<'\n';
    }
}

void neural_network::fromFile(std::ifstream &file)
{
    file>>nrLayers;
    for(int i=0;i<nrLayers;i++)
    {
        int l;
        file>>l;
    //    layers.push_back(l);
    }
    weights.clear();
    weights.push_back(matrix<double>(0,0));
    for(int i=1;i<nrLayers;i++)
        weights.push_back(matrix<double>(layers[i],layers[i-1]));

    biases.clear();
    neurons.clear();
    for(auto x:layers)
    {
        biases.push_back(matrix<double>(x,1));
        neurons.push_back(matrix<double>(x,1));
    }

    for(int i=0;i<nrLayers;i++)
        for(int j=0;j<layers[i];j++)
            file>>biases[i][j][0];

    for(int i=1;i<nrLayers;i++)
        for(int j=0;j<layers[i];j++)
            for(int k=0;k<layers[i-1];k++)
                file>>weights[i][j][k];
}




