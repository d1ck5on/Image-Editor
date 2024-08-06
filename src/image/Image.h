#pragma once

#include <vector>

using Channel = std::vector<std::vector<double>>;

class Image {
public:
    Image(size_t channels_count = 1, size_t width = 1, size_t height = 1);

    std::vector<Channel>& GetChannels();

    void SetPixel(std::vector<double> pixel, size_t col, size_t row);
    std::vector<double> GetPixel(size_t col, size_t row) const;
    
    size_t GetWidth() const;
    size_t GetHeight() const;

private:
    std::vector<Channel> channels_;
};
