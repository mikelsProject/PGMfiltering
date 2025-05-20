#include "PGMImage.hpp"


PGMImage::PGMImage(size_t width, size_t height, int maxGreyValue)
        :m_width(width), m_height(height), m_maxGrey(maxGreyValue), m_pixelsGreyness(width*height, 0)
{}

PGMImage::PGMImage(std::string filename)
{
    load(filename);
}

unsigned char PGMImage::get_at(size_t x, size_t y) const
{
    if(x < 0 || x >= m_width || y < 0 || y >= m_height)
    {
        std::cerr << "Trying to read pixel index out of bounds\n";
        return m_pixelsGreyness[0];
    }
    return m_pixelsGreyness[x + y*m_width];
}

void PGMImage::modify_at(size_t x, size_t y, unsigned char newGreyness)
{
    if(x < 0 || x >= m_width || y < 0 || y >= m_height)
        std::cerr << "Trying to modify pixel index out of bounds\n";
    else
        m_pixelsGreyness.at(x + y*m_width) = newGreyness;
}

void PGMImage::save(const std::string filename) const
{
    std::ofstream out(filename, std::ios::binary);
    if(!out)
        std::cerr << "Could not open the file for writing!\n";
    out << "P5\n" << m_width << " " << m_height << "\n" << m_maxGrey << "\n";
    out.write(reinterpret_cast<const char*>(m_pixelsGreyness.data()), m_pixelsGreyness.size());
}

void PGMImage::load(const std::string filename)
{
    std::ifstream in(filename, std::ios::binary);
    if(!in)
        std::cerr << "Could not open the file for reading PGMImage";
    std::string magic;
    in >> magic;
    in >> m_width >> m_height >> m_maxGrey;
    in.ignore();

    if (magic == "P5") //binary format
    {
        m_pixelsGreyness.resize(m_width * m_height);
        in.read(reinterpret_cast<char*>(m_pixelsGreyness.data()), m_pixelsGreyness.size());
    }
    else if (magic == "P2") //text format
    {
        m_pixelsGreyness.clear();
        m_pixelsGreyness.reserve(m_height * m_width);
        int greyness;
        while(in >> greyness)
            m_pixelsGreyness.push_back(greyness);
    }
    else
        std::cerr << "Invalid PGM format (expected P5 or P2)\n";
}

void PGMImage::print() const
{
    std::cout << m_width << " " << m_height << "\n";
    for(int y = 0; y < m_height - 478; ++y)
    {
        for(int x = 0; x < m_width; ++x)
        {
            std::cout << static_cast<int>(get_at(x,y)) << " ";
        }
        std::cout << std::endl;
    }
}

size_t PGMImage::get_width() const
{
    return m_width;
}

size_t PGMImage::get_height() const
{
    return m_height;
}

int PGMImage::get_maxGrey() const
{
    return m_maxGrey;
}