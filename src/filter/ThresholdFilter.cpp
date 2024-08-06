#include "ThresholdFilter.h"

ThresholdFilter::ThresholdFilter(double threshold) : threshold_(threshold) {};
ThresholdFilter::~ThresholdFilter() = default;

void ThresholdFilter::FilterImpl(Channel& channel) const {
    for (auto& row : channel) {
        for (auto& elem : row) {
            elem = elem > threshold_ ? 1 : 0;
        }
    }
}