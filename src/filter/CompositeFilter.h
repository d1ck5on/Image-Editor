#pragma once

#include "AbstractFilter.h"

#include <memory>
#include <vector>

class CompositeFilter : public AbstractFilter {
public:
    ~CompositeFilter() override = default;

    explicit CompositeFilter(std::vector<std::unique_ptr<AbstractFilter>> filters);
    CompositeFilter();

    void ApplyFilter(Image& image) const final;

protected:
    void AddFilter(std::unique_ptr<AbstractFilter> filterPtr);

private:
    std::vector<std::unique_ptr<AbstractFilter>> filters_;
};
