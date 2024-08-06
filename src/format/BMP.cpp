#include "BMP.h"
#include "Image.h"

#include <iostream>
#include <tuple>
#include <limits>
#include <algorithm>
#include <stdexcept>

auto BMP::Tie(BMP::Header &header) {
    return std::tie(header.signature[0], header.signature[1], header.file_size, header.reserved[0], header.reserved[1],
                    header.offset);
}

auto BMP::Tie(BMP::InfoHeader &info_header) {
    return std::tie(info_header.header_size, info_header.size.width, info_header.size.height, info_header.planes,
                    info_header.bit_per_pixel, info_header.compression, info_header.image_size, info_header.dpi.hor,
                    info_header.dpi.ver, info_header.total_colors, info_header.important_colors);
}

Image BMP::Load(const std::string &filename) {
    BinaryReader input(filename);
    Header header{};
    InfoHeader info_header{};

    std::apply([&input](auto &...args) { (input >> ... >> args); }, Tie(header));

    TryValidateHeader(header);

    std::apply([&input](auto &...args) { (input >> ... >> args); }, Tie(info_header));

    TryValidateInfoHeader(info_header);

    Image image(3, static_cast<size_t>(info_header.size.width), static_cast<size_t>(info_header.size.height));

    if (image.GetWidth() == 0 || image.GetHeight() == 0) {
        return image;
    }

    for (size_t row = 0; row != image.GetHeight(); ++row) {
        ReadRow(image, input, row);
    }

    for (auto& channel : image.GetChannels()) {
        std::reverse(channel.begin(), channel.end());
    }

    return image;
}

void BMP::Save(const Image &image, const std::string &filename) {
    BinaryWriter output(filename);
    Header header{};
    InfoHeader info_header{};

    size_t bits_per_pixel = 24;

    info_header.size.width = static_cast<int32_t>(image.GetWidth());
    info_header.size.height = static_cast<int32_t>(image.GetHeight());
    info_header.image_size = GetRowSize(image.GetWidth(), bits_per_pixel) * image.GetHeight();

    header.file_size = info_header.image_size + header.offset;

    std::apply([&output](auto &...args) { (output << ... << args); }, Tie(header));

    std::apply([&output](auto &...args) { (output << ... << args); }, Tie(info_header));

    for (size_t row = 0; row < image.GetHeight(); ++row) {
        WriteRow(image, output, image.GetHeight() - row - 1);
    }
};

void BMP::ReadRow(Image &image, BinaryReader &input, const size_t row) {
    const double upper = std::numeric_limits<u_int8_t>::max();
    size_t bits_per_pixel = 24;

    for (size_t col = 0; col != image.GetWidth(); ++col) {
        u_int8_t r, g, b;
        input >> r >> g >> b;

        image.SetPixel(std::vector<double>{static_cast<double>(r) / upper, static_cast<double>(g) / upper,
                                           static_cast<double>(b) / upper},
                       col, row);
    }

    size_t row_size = GetRowSize(image.GetWidth(), bits_per_pixel);
    uint8_t reserved = 0;
    for (size_t bytes_read = bits_per_pixel / 8 * image.GetWidth(); bytes_read < row_size; ++bytes_read) {
        input >> reserved;
    }
}

void BMP::WriteRow(const Image &image, BinaryWriter &output, const size_t row) {
    const double upper = std::numeric_limits<u_int8_t>::max();
    size_t bits_per_pixel = 24;

    for (size_t col = 0; col != image.GetWidth(); ++col) {
        auto pixel = image.GetPixel(col, row);

        u_int8_t r = static_cast<u_int8_t>(std::clamp(pixel[0] * upper, 0.0d, upper));
        u_int8_t g = static_cast<u_int8_t>(std::clamp(pixel[1] * upper, 0.0d, upper));
        u_int8_t b = static_cast<u_int8_t>(std::clamp(pixel[2] * upper, 0.0d, upper));

        output << r << g << b;
    }

    size_t row_size = GetRowSize(image.GetWidth(), bits_per_pixel);
    uint8_t reserved = 0;

    for (size_t bytes_written = bits_per_pixel / 8 * image.GetWidth(); bytes_written < row_size; ++bytes_written) {
        output << reserved;
    }
}

size_t BMP::GetRowSize(size_t width, size_t bits_per_pixel) {
    return (bits_per_pixel * width + 31) / 32 * 4;
}

void BMP::TryValidateHeader(const Header& header) {
    std::string bmp_signature = {header.signature[0], header.signature[1]};
    if (bmp_signature != "BM" || header.file_size < header.offset) {
        throw std::invalid_argument("Incorrect file format: invalid bitmap header data!");
    }
}

void BMP::TryValidateInfoHeader(const InfoHeader& info_header) {
    if (
        (info_header.header_size != 40) 
        || (info_header.planes != 1)
        || (info_header.bit_per_pixel != 24)
        || (info_header.compression != 0)
    ) {
        throw std::invalid_argument("Incorrect file format: unsupported DIB header value!");
    }
}
