#include "Image.h"

Image::Image(size_t channels_count, size_t width, size_t height)
    : channels_(channels_count, Channel(height, std::vector<double>(width, 0))){};

std::vector<Channel>& Image::GetChannels() {
    return channels_;
}

size_t Image::GetWidth() const {
    if (channels_[0].size() == 0) {
        return 0;
    }

    return channels_[0][0].size();
}

size_t Image::GetHeight() const {
    return channels_[0].size();
}

void Image::SetPixel(std::vector<double> pixel, size_t col, size_t row) {
    for (size_t channel = 0; channel < pixel.size(); ++channel) {
        channels_[channel][row][col] = pixel[channel];
    }
}

std::vector<double> Image::GetPixel(size_t col, size_t row) const {
    std::vector<double> pixel(channels_.size());
    for (size_t channel = 0; channel < channels_.size(); ++channel) {
        pixel[channel] = channels_[channel][row][col];
    }
    
    return pixel;
}
