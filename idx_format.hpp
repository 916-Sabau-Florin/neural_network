#include <fstream>
#include "matrix.tpp"


uint32_t IDX3_HEADER[4];
uint32_t IDX1_HEADER[2];

void read_headers(std::ifstream &images, std::ifstream &labels)
{
    images.read((char *) IDX3_HEADER, sizeof(uint32_t)*4);
    labels.read((char *) IDX1_HEADER, sizeof(uint32_t)*2);
    for(int i=0;i<4;i++)
        IDX3_HEADER[i]=__builtin_bswap32(IDX3_HEADER[i]);
    for(int i=0;i<2;i++)
        IDX1_HEADER[i]=__builtin_bswap32(IDX1_HEADER[i]);
}

std::pair<matrix<double>,int> next_image(std::ifstream &images,std::ifstream &labels)
{
    int rows=IDX3_HEADER[2],cols=IDX3_HEADER[3];
    matrix<double> m(rows,cols);
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            uint8_t pixel;
            images.read((char*)&pixel,sizeof(uint8_t));
            //std::cout<<images.tellg()<<' '<<(images.tellg()==i*28+j+17)<<'\n';
            if(!images.good())
            {
                std::cout<<"Error when reading from file:\n";
                std::cout<<"eof:"<<images.eof()<<'\n';
                std::cout<<"fail:"<<images.fail()<<'\n';
                std::cout<<"bad:"<<images.bad()<<'\n';
                exit(EXIT_FAILURE);
            }
            m[i][j]=((double)pixel)/255.0d;
        }
    }
    uint8_t digit;
    labels.read((char*) &digit , sizeof(uint8_t));
    return {m,(int)digit};
}


