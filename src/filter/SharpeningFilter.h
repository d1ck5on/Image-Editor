#pragma once

#include "ConvolutionFilter.h"

class SharpeningFilter final : public ConvolutionFilter {
public:
    SharpeningFilter();
    ~SharpeningFilter() override;
};