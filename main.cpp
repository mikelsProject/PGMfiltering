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
    
    std::string image = "../pgmfiles/balloons.pgm";
    std::string kernel = "../filters/blur_kernel10.txt";
    std::cout << "Arguments number: " << argc << "\n";
    if(argc == 3)
    {
        std::cout << "I am using arguments used after calling the ./images\n";
        image = argv[1];
        kernel = argv[2];
        std::cout << image << "\n";
        std::cout << kernel << "\n";
    }
    std::cout << "The Images program!\n";

    PGMImage balloons(image);
    Filter blur_filter(kernel);

    std::cout << "Calculations are about to begin\n ";
    PGMImage filtered = blur_filter.create_filtered_image(balloons);
    std::cout << "Calculations finished\n ";
    filtered.save("../pgmfiles/filterednew.pgm");

    return 0;
}
