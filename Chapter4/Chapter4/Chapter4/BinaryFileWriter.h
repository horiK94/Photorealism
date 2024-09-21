#pragma once
#include <iosfwd>
#include <fstream>
#include <string>

class BinaryFileWriter
{
public:
	/// @brief デフォルトコンストラクタ
	[[nodiscard]]
	BinaryFileWriter() = default;

	/// @brief コンストラクタ
	/// @param filename 
	[[nodiscard]]
	explicit BinaryFileWriter(const std::string& filename);

	/// @brief ファイルを開けているか
	/// @return 
	[[nodiscard]]
	bool isOpen() const;

	/// @brief ファイルを開けているか
	[[nodiscard]]
	explicit operator bool() const;

	/// @brief 書き込み
	/// @param buffer 
	/// @param size 
	void write(const void* buffer, size_t size);

	/// @brief 閉じる
	void close();

private:
	/// @brief ファイル
	std::ofstream file;
};