#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class PGMImage
{
public:
    PGMImage(size_t width, size_t height, int maxGreyValue);
    PGMImage(std::string filename);

    unsigned char get_at(size_t x, size_t y) const;
    void modify_at(size_t x, size_t y, unsigned char newGreyness);
    void save(const std::string filename) const;
    void load(const std::string filename);
    void print() const;
    size_t get_width() const;
    size_t get_height() const;
    int get_maxGrey() const;


private:
    size_t m_width, m_height;
    int m_maxGrey;
    std::vector<unsigned char> m_pixelsGreyness;
};