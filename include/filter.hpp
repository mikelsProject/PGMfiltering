#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include "PGMImage.hpp"

//class which stores kernel and uses it to perform filtering operation on PGMImages
class Filter
{
public:
    Filter(size_t size);
    Filter(std::string filename);

    void load(std::string filename);
    PGMImage create_filtered_image(const PGMImage& image);
private:
    float S(const PGMImage& image, int x, int y);

private:
    size_t m_size;
    std::vector<float> m_kernel;
};
