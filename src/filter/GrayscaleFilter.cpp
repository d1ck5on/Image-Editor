#include "GrayscaleFilter.h"

GrayscaleFilter::~GrayscaleFilter() = default;

void GrayscaleFilter::ApplyFilter(Image& image) const {

    Channel grayscale(image.GetHeight(), std::vector<double>(image.GetWidth()));

    for (size_t x = 0; x < image.GetWidth(); ++x) {
        for (size_t y = 0; y < image.GetHeight(); ++y) {
            std::vector<double> pixel = image.GetPixel(x, y);
            grayscale[y][x] = 0.299d * pixel[2] + 0.587d * pixel[1] + 0.114d * pixel[0];
        }
    }

    for (auto& channel : image.GetChannels()) {
        channel = grayscale;
    }
}