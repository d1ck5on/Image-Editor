#include "EdgeDetectionFilter.h"
#include "GrayscaleFilter.h"
#include "ConvolutionFilter.h"
#include "ThresholdFilter.h"

EdgeDetectionFilter::EdgeDetectionFilter(double threshold) {
    AddFilter(std::make_unique<GrayscaleFilter>());
    std::vector<std::vector<double>> matrix = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};
    AddFilter(std::make_unique<ConvolutionFilter>(matrix));
    AddFilter(std::make_unique<ThresholdFilter>(threshold));

}

EdgeDetectionFilter::~EdgeDetectionFilter() = default;