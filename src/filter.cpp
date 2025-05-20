#include "filter.hpp"

Filter::Filter(size_t size)
    :m_size(size) 
{}

Filter::Filter(std::string filename)
{
    load(filename);
}

void Filter::load(std::string filename)
{
    std::ifstream in(filename);
    if(!in)
        std::cerr << "Could not open the file for reading filter";
    std::string size;
    in >> size;
    m_size = stoi(size);
    m_kernel.reserve(m_size * m_size);
    float data;
    while(in >> data)
    {
        m_kernel.push_back(data);
    }
}

//function to perform mathematical operation of filtering
//S(x,y) = ∑ci=1∑cj=1 I[max{1,x−ceil(c/2)+i},max{1,y−ceil(c/2)+j}]∗k[i,j]
float Filter::S(const PGMImage& image, int x, int y)
{
    float sum = 0.f;
    int center = static_cast<int>(std::ceil(m_size / 2.0));
    for(int i = 0; i < m_size; ++i)
    {
        for(int j = 0; j < m_size; ++j)
        {
            int Ix = std::max(1, x - center + i);
            int Iy = std::max(1, y - center + j);
            sum += image.get_at(Ix, Iy) * m_kernel.at(i + j*m_size);
        }
    }
    return sum;
}

PGMImage Filter::create_filtered_image(const PGMImage& image)
{
    PGMImage filtered(image.get_width(), image.get_height(), image.get_maxGrey());
    //fitering operations on each pixel
    for(int y = 0; y < image.get_height(); ++y)
    {
        for(int x = 0; x < image.get_width(); ++x)
        {
            float result = S(image, x, y);
            unsigned char newGreyness = static_cast<unsigned char>(std::round(result));
            filtered.modify_at(x,y, newGreyness);
        }
    }
    return filtered;
}

