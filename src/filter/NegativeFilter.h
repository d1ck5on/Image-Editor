#pragma once
#include "ChannelWiseFilter.h"

class NegativeFilter final : public ChannelWiseFilter {
public:
    ~NegativeFilter() override;

protected:
    void FilterImpl(Channel& channel) const override;
};