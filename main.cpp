#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <algorithm>
#include "PGMImage.hpp"

//sx,y=∑ci=1∑cj=1I[max{1,x−ceil(c/2)+i},max{1,y−ceil(c/2)+j}]∗k[i,j]
float S(const PGMImage& image, const std::vector<float>& kernel, int kernelSize, int x, int y)
{
    float sum = 0.f;
    int center = static_cast<int>(std::ceil(kernelSize / 2.0));
    for(int i = 0; i < kernelSize; ++i)
    {
        for(int j = 0; j < kernelSize; ++j)
        {
            int Ix = std::max(1, x - center + i);
            int Iy = std::max(1, y - center + j);
            sum += image.get_at(Ix, Iy) * kernel.at(i + j*kernelSize);
        }
    }
    return sum;
}

PGMImage filter(const PGMImage& image, const std::vector<float>& kernel)
{
    int kernelSize = static_cast<int>(sqrt(kernel.size()));
    PGMImage filtered(image.get_width(), image.get_height(), image.get_maxGrey());

    for(int y = 0; y < image.get_height(); ++y)
    {
        for(int x = 0; x < image.get_width(); ++x)
        {
            unsigned char newGreyness = static_cast<unsigned char>(std::round( S(image, kernel, kernelSize, x, y) ));
            filtered.modify_at(x,y, newGreyness);
        }
    }
    return filtered;
}


int main(int argc, char* argv[])
{
    // I MUST PREPARE THE SPEECH!!
    std::vector<float> blur_kernel = 
    {
        1/9.f, 1/9.f, 1/9.f,
        1/9.f, 1/9.f, 1/9.f,
        1/9.f, 1/9.f, 1/9.f
    };
    //which somehow destroys the picture
    std::vector<float> blur_kernel2 = 
    {
        1/8.f, 1/8.f, 1/8.f,
        1/8.f, 1/8.f, 1/8.f,
        1/8.f, 1/8.f, 1/8.f
    };
    std::vector<float> identity_kernel = 
    {
        0.f, 0.f, 0.f,
        0.f, 1.f, 0.f,
        0.f, 0.f, 0.f
    };

    std::cout << "The Images program!\n";

    PGMImage balloons("../pgmfiles/balloons.pgm");
    PGMImage filtered = filter(balloons, blur_kernel);
    filtered.save("../pgmfiles/filtered.pgm");
    
    PGMImage apollo("../pgmfiles/apollo.pgm");
    PGMImage filtered2 = filter(apollo, blur_kernel);
    filtered2.save("../pgmfiles/filtered2.pgm");

    return 0;
}




/*

float S(size_t x, size_t y, const std::vector<float>& kernel, size_t kernelSize, const PGMImage& image)
{

    int offset = static_cast<int>(std::ceil(kernelSize / 2.0));
    float sum = 0.0f;
    for(size_t j = 0; j < kernelSize; ++j)
    {
        for(size_t i = 0; i < kernelSize; ++i)
        {
            int xi = std::max(0, static_cast<int>(x) - offset + static_cast<int>(i));
            int yj = std::max(0, static_cast<int>(y) - offset + static_cast<int>(j));
            xi = std::min(static_cast<int>(image.get_width()) - 1, xi);
            yj = std::min(static_cast<int>(image.get_height()) - 1, yj);

            unsigned char pixel = image.get_at(xi, yj);
            float k = kernel.at(j * kernelSize + i);
            sum += pixel * k;
        }
    }
    return sum;
}
/*
void filter(PGMImage& toFilter, const PGMImage& image, const std::vector<float>& kernel)
{
    size_t kernelSize = static_cast<size_t>(std::sqrt(kernel.size()));
    for(size_t y = 0; y < image.get_height(); ++y)
    {
        for(size_t x = 0; x <image.get_width(); ++x)
        {
            float sum = S(x, y, kernel, kernelSize, image);
            unsigned char newValue = static_cast<unsigned char>(std::clamp(sum, 0.0f, 255.0f));
            std::cout << static_cast<int>(newValue) << " ";
            toFilter.modify_at(x,y,newValue);
        }
    }

}
*/