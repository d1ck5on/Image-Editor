#include "ConvolutionFilter.h"
#include <algorithm>

ConvolutionFilter::ConvolutionFilter(std::vector<std::vector<double>> matrix) : matrix_(std::move(matrix)){};
ConvolutionFilter::~ConvolutionFilter() = default;

void ConvolutionFilter::FilterImpl(Channel& channel) const {
    Channel new_channel(channel);

    for (size_t x = 0; x < channel[0].size(); ++x) {
        for (size_t y = 0; y < channel.size(); ++y) {
            new_channel[y][x] = std::clamp(ApplyMatrixToElement(x, y, channel), 0.0d, 1.0d);
        }
    }

    channel = std::move(new_channel);
}

double ConvolutionFilter::ApplyMatrixToElement(int64_t elem_x, int64_t elem_y, Channel& channel) const {
    int64_t padding = matrix_.size() / 2;

    int64_t clamp_min = 0;
    int64_t clamp_max_x = channel[0].size() - 1;
    int64_t clamp_max_y = channel.size() - 1;

    double result = 0;

    // TODO: сделать итерацию по size_t (проблема в unsigned)
    for (int64_t x = elem_x - padding; x <= elem_x + padding; ++x) {
        for (int64_t y = elem_y - padding; y <= elem_y + padding; ++y) {

            result += matrix_[y - (elem_y - padding)][x - (elem_x - padding)] *
                      channel[std::clamp(y, clamp_min, clamp_max_y)][std::clamp(x, clamp_min, clamp_max_x)];
        }
    }

    return result;
}