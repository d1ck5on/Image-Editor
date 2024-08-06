#include "ChannelWiseFilter.h"

ChannelWiseFilter::~ChannelWiseFilter() = default;

void ChannelWiseFilter::ApplyFilter(Image& image) const {
    for (auto& channel : image.GetChannels()) {
        FilterImpl(channel);
    }
}