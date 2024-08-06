#pragma once

#include "AbstractFilter.h"

class ChannelWiseFilter : public AbstractFilter {
public:
    virtual ~ChannelWiseFilter() override;

    void ApplyFilter(Image& image) const override;

protected:
    virtual void FilterImpl(Channel& channel) const = 0;
};