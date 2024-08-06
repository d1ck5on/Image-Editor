#pragma once

#include "Image.h"
#include <string>


class ImageFormat {
public:
    ImageFormat() = default;
    virtual ~ImageFormat() = default;

    virtual Image Load(const std::string &filename) = 0;
    virtual void Save(const Image& image, const std::string &filename) = 0;
};
