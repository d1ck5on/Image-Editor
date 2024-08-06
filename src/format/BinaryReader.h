#pragma once

#include <fstream>
#include <string>

class BinaryReader {
public:
    BinaryReader(const std::string& filename);
    ~BinaryReader();

    template <typename TValue>
    BinaryReader& operator>>(TValue& value) {
        using U = std::make_unsigned_t<TValue>;
        U bits = 0;

        unsigned char buffer[sizeof(TValue)];
        file_.read(reinterpret_cast<char*>(buffer), sizeof(TValue));

        std::reverse(std::begin(buffer), std::end(buffer));

        for (auto byte : buffer) {
            bits = (bits << U{8}) | byte;
        }

        value = static_cast<TValue>(bits);
        return *this;
    };

private:
    std::ifstream file_;
};
