#include "FileUtil.h"
#include <filesystem>

namespace FileUtil
{
	// �t�H���_�z���̃t�@�C�����̈ꊇ�ǂݍ���
	std::vector<std::string> LoadFileNames(std::string folderPath, std::string extension)
	{
		std::vector<std::string> fileNames;

		// �t�@�C�����̈ꊇ�ǂݍ���
		for (auto& p : std::filesystem::directory_iterator(folderPath))
		{
			// �g���q�̎擾
			std::string ext = p.path().extension().string();

			// �g���q����v���Ă��邩
			if (ext == extension)
			{
				// �t�@�C�����̕ۑ�
				fileNames.push_back(p.path().filename().string());
			}
		}
		return fileNames;
	}

	// �t�H���_�z���̃t�H���_���̈ꊇ�ǂݍ���
	std::vector<std::string> LoadDirectoryNames(std::string folderPath)
	{
		std::vector<std::string> directoryNames;

		// �t�H���_���̈ꊇ�ǂݍ���
		for (auto& p : std::filesystem::directory_iterator(folderPath))
		{
			// �t�H���_���̕ۑ�
			directoryNames.push_back(p.path().filename().string());
		}
		return directoryNames;
	}
}