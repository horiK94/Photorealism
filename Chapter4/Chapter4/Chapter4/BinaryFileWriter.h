#pragma once
#include <iosfwd>
#include <fstream>
#include <string>

class BinaryFileWriter
{
public:
	/// @brief �f�t�H���g�R���X�g���N�^
	[[nodiscard]]
	BinaryFileWriter() = default;

	/// @brief �R���X�g���N�^
	/// @param filename 
	[[nodiscard]]
	explicit BinaryFileWriter(const std::string& filename);

	/// @brief �t�@�C�����J���Ă��邩
	/// @return 
	[[nodiscard]]
	bool isOpen() const;

	/// @brief �t�@�C�����J���Ă��邩
	[[nodiscard]]
	explicit operator bool() const;

	/// @brief ��������
	/// @param buffer 
	/// @param size 
	void write(const void* buffer, size_t size);

	/// @brief ����
	void close();

private:
	/// @brief �t�@�C��
	std::ofstream file;
};