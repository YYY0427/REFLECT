#include "ModelHandleManager.h"
#include "Util/DrawFunctions.h"
#include "Util/FileUtil.h"
#include <DxLib.h>
#include <cassert>

namespace
{
	// ���f���̃t�@�C���p�X
	const std::string model_list_file_path = "Data/Csv/Model.csv";		
}

// �C���X�^���X�̎擾
ModelHandleManager& ModelHandleManager::GetInstance()
{
	static ModelHandleManager instance;
	return instance;
}

// �R���X�g���N�^
ModelHandleManager::ModelHandleManager()
{
	// ���f���̃t�@�C���p�X�̓ǂݍ���
	auto data = FileUtil::LoadCsvFile(model_list_file_path);
	for (auto& line : data)
	{
		// ���f���̓ǂݍ���
		m_handleMap[line[static_cast<int>(ModelFileType::ID)]].modelHandle = LoadModel(line[static_cast<int>(ModelFileType::FILE_PATH)]);

		// �t�@�C���p�X�̓o�^
		m_handleMap[line[static_cast<int>(ModelFileType::ID)]].filePath = line[static_cast<int>(ModelFileType::FILE_PATH)];
	}
}

// �f�X�g���N�^
ModelHandleManager::~ModelHandleManager()
{
	// �n���h���̉��
	ReleaseHandle();
}

// �n���h���̉��
void ModelHandleManager::ReleaseHandle()
{
	// ���f���̃n���h�������
	for (auto& handle : m_handleMap)
	{
		MV1DeleteModel(handle.second.modelHandle);
	}
}

// ���f���̓ǂݍ���
int ModelHandleManager::LoadModel(const std::string& filePath)
{
	// ���Ƀt�@�C���p�X���o�^����Ă���ꍇ�̓n���h���Ԃ�
	for (auto& handle : m_handleMap)
	{
		if (handle.second.filePath == filePath)
		{
			return handle.second.modelHandle;
		}
	}

	// ���f���̓ǂݍ���
	return my::MyLoadModel(filePath.c_str());
}

// �n���h���̎擾
int ModelHandleManager::GetHandle(const std::string& id)
{
	// �n���h�������݂��Ă�����
	if (m_handleMap.find(id) != m_handleMap.end())
	{
		return m_handleMap[id].modelHandle;
	}
	// ���݂��Ȃ�������
	assert(!"���f����ID��������܂���");
	return -1;
}

// �n���h���̍폜
void ModelHandleManager::DeleteHandle(const std::string& id)
{
	// �n���h�������݂��Ă�����
	if (m_handleMap.find(id) != m_handleMap.end())
	{
		// ���f���̃n���h�������
		MV1DeleteModel(m_handleMap[id].modelHandle);

		// �}�b�v����폜
		m_handleMap.erase(id);
	}
	// ���݂��Ȃ�������
	else
	{
		assert(!"���f����ID��������܂���");
	}
}