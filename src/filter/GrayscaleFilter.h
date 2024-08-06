#pragma once

#include "AbstractFilter.h"

class GrayscaleFilter final : public AbstractFilter {
public:
    ~GrayscaleFilter() override;

    void ApplyFilter(Image& image) const override;
};