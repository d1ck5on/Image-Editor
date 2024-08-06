#pragma once
#include "ImageFormat.h"
#include "BinaryReader.h"
#include "BinaryWriter.h"

class BMP : ImageFormat {
private:
    struct Header {
        char signature[2] = {'B', 'M'};
        uint32_t file_size = 0;
        uint16_t reserved[2] = {0, 0};
        uint32_t offset = 54;
    };

    struct InfoHeader {
        uint32_t header_size = 40;

        struct Size {
            int32_t width = 0;
            int32_t height = 0;
        } size = {};

        uint16_t planes = 1;
        uint16_t bit_per_pixel = 24;
        uint32_t compression = 0;
        uint32_t image_size = 0;

        struct DPI {
            int32_t hor = 300;
            int32_t ver = 300;
        } dpi = {};

        uint32_t total_colors = 0;
        uint32_t important_colors = 0;
    };

private:
    void ReadRow(Image &image, BinaryReader &input, const size_t row);
    void WriteRow(const Image &image, BinaryWriter &output, const size_t row);
    static auto Tie(BMP::Header &header);
    static auto Tie(BMP::InfoHeader &info_header);
    size_t GetRowSize(size_t width, size_t bits_per_pixel);
    void TryValidateHeader(const Header& header);
    void TryValidateInfoHeader(const InfoHeader& info_header);

public:
    Image Load(const std::string &filename) override;
    void Save(const Image &image, const std::string &filename) override;
};
