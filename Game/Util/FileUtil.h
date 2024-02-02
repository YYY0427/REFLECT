#pragma once
#include <string>
#include <vector>

/// <summary>
/// �t�@�C�����[�e�B���e�B
/// </summary>
namespace FileUtil
{
	// �t�H���_�z���̃t�@�C�����̈ꊇ�ǂݍ���
	std::vector<std::string> LoadFileNames(std::string folderPath, std::string extension);

	// �t�H���_�z���̃t�H���_���̈ꊇ�ǂݍ���
	std::vector<std::string> LoadDirectoryNames(std::string folderPath);
}