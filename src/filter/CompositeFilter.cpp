#include "CompositeFilter.h"

CompositeFilter::CompositeFilter() = default;

CompositeFilter::CompositeFilter(std::vector<std::unique_ptr<AbstractFilter>> filters)
    : filters_(std::move(filters)) {
}

void CompositeFilter::ApplyFilter(Image& image) const {
    for (const auto& filter : filters_) {
        filter->ApplyFilter(image);
    }
}

void CompositeFilter::AddFilter(std::unique_ptr<AbstractFilter> filterPtr) {
    filters_.push_back(std::move(filterPtr));
}