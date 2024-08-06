#pragma once

#include "CompositeFilter.h"

class EdgeDetectionFilter final : public CompositeFilter {
public:
    EdgeDetectionFilter(double threshold);
    ~EdgeDetectionFilter() override;
};