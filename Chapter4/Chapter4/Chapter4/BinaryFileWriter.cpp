#include "BinaryFileWriter.h"

BinaryFileWriter::BinaryFileWriter(const std::string& filename)
{
	file.open(filename, std::ios::binary);
}

bool BinaryFileWriter::isOpen() const
{
	return file.is_open();
}

BinaryFileWriter::operator bool() const
{
	return isOpen();
}

void BinaryFileWriter::write(const void* buffer, size_t size)
{
	file.write(static_cast<const char*>(buffer), size);
}

void BinaryFileWriter::close()
{
	file.close();
}