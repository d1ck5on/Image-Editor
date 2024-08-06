#include "CropFilter.h"
#include <algorithm>

CropFilter::CropFilter(size_t width, size_t height) : width_(width), height_(height){};
CropFilter::~CropFilter() = default;

void CropFilter::FilterImpl(Channel& channel) const {
    channel.resize(std::min(height_, channel.size()));

    for (auto& row : channel) {
        row.resize(std::min(width_, channel[0].size()));
    }
}