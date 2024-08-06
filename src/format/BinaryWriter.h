#pragma once
#include <string>
#include <fstream>

class BinaryWriter {
public:
    BinaryWriter(const std::string &filename);
    ~BinaryWriter();

    template <typename T>
    BinaryWriter &operator<<(T value) {
        using U = std::make_unsigned_t<T>;
        U bits = static_cast<U>(value);

        unsigned char buffer[sizeof(T)];
        for (unsigned char& byte : buffer) {
            byte = bits & U{0xFF};
            bits >>= U{8};
        }

        file_.write(reinterpret_cast<char*>(buffer), sizeof(T));
        return *this;
    }

private:
    std::ofstream file_;
};