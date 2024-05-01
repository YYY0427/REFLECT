#pragma once
#include <string>
#include <vector>

/// <summary>
/// �t�@�C�����[�e�B���e�B
/// </summary>
namespace FileUtil
{
	/// <summary>
	/// �t�H���_�z���̃t�@�C�����A�t�H���_���̎擾
	/// </summary>
	/// <param name="folderPath">�p�X</param>
	/// <param name="extension">�g���q(�t�H���_���̏ꍇ�͂Ȃ�)</param>
	/// <returns>�擾�����t�@�C�����A�t�H���_���̖��O</returns>
	std::vector<std::string> LoadFileNames(const std::string& folderPath, const std::string& extension = "");

	/// <summary>
	/// CSV�t�@�C���̓ǂݍ���
	/// </summary>
	/// <param name="filePath">�t�@�C���p�X</param>
	/// <returns>�ǂݍ��񂾃f�[�^</returns>
	std::vector<std::vector<std::string>> LoadCsvFile(const std::string& filePath);
}