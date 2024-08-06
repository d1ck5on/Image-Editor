#pragma once

#include "ChannelWiseFilter.h"

class ThresholdFilter final : public ChannelWiseFilter {
public:
    ThresholdFilter(double threshold);
    ~ThresholdFilter() override;

private:
    void FilterImpl(Channel& channel) const final;

    double threshold_;
};