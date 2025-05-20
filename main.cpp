#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <algorithm>
#include "PGMImage.hpp"
#include "filter.hpp"

int main(int argc, char* argv[])
{
    // I MUST PREPARE THE SPEECH!!
    std::vector<float> blur_kernel = 
    {
        1/9.f, 1/9.f, 1/9.f,
        1/9.f, 1/9.f, 1/9.f,
        1/9.f, 1/9.f, 1/9.f
    };
    std::vector<float> identity_kernel = 
    {
        0.f, 0.f, 0.f,
        0.f, 1.f, 0.f,
        0.f, 0.f, 0.f
    };

    std::cout << "The Images program!\n";

    PGMImage balloons("../pgmfiles/balloons.pgm");
    Filter blur_filter("../filters/blur_kernel.txt");

    PGMImage filtered = blur_filter.create_filtered_image(balloons);
    filtered.save("../pgmfiles/filtered.pgm");

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