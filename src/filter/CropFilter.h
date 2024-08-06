#pragma once

#include "ChannelWiseFilter.h"

class CropFilter final : public ChannelWiseFilter {
public:
    CropFilter(size_t width, size_t height);
    ~CropFilter() override;

private:
    void FilterImpl(Channel& channel) const override;

    size_t width_;
    size_t height_;
};