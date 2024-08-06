#include "SharpeningFilter.h"

SharpeningFilter::SharpeningFilter() : ConvolutionFilter({{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}}){};
SharpeningFilter::~SharpeningFilter() = default;