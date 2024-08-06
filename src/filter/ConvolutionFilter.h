#pragma once

#include "ChannelWiseFilter.h"

class ConvolutionFilter : public ChannelWiseFilter {
public:
    ConvolutionFilter(std::vector<std::vector<double>> matrix);
    ~ConvolutionFilter() override;

protected:
    void FilterImpl(Channel& channel) const final;

private:
    double ApplyMatrixToElement(int64_t elem_x, int64_t elem_y, Channel& channel) const;

    std::vector<std::vector<double>> matrix_;
};