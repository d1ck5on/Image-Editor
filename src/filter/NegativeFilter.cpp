#include "NegativeFilter.h"

NegativeFilter::~NegativeFilter() = default;

void NegativeFilter::FilterImpl(Channel& channel) const {
    for (auto& row : channel) {
        for (auto& item : row) {
            item = 1 - item;
        }
    }
}