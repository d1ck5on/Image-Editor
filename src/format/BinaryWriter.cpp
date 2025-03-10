#include "BinaryWriter.h"

BinaryWriter::BinaryWriter(const std::string &filename) : file_(filename, std::ios::binary) {};

BinaryWriter::~BinaryWriter() {
    file_.close();
}