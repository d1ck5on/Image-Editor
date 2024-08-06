#include "BinaryReader.h"

#include <ranges>

BinaryReader::BinaryReader(const std::string &filename) : file_(filename, std::ios::binary) {};
BinaryReader::~BinaryReader() {
    file_.close();
}