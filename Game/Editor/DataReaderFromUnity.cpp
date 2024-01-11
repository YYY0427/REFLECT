#include "DataReaderFromUnity.h"
#include <cassert>
#include "../Math/MathUtil.h"
#include "DxLib.h"

namespace
{
	// �t�@�C���̊K�w
	const std::string file_hierarchy = "Data/Stage/";	

	// �g���q
	const std::string extension = ".dat";
}

// �R���X�g���N�^
DataReaderFromUnity::DataReaderFromUnity()
{
}

// �f�X�g���N�^
DataReaderFromUnity::~DataReaderFromUnity()
{
}

// Unity�Ŕz�u�����I�u�W�F�N�g�̃f�[�^��ǂݎ��
void DataReaderFromUnity::LoadUnityGameObjectData(std::string fileName)
{
	// �t�@�C�����̊K�w��t����
	fileName = file_hierarchy + fileName;

	// �g���q��t����
	fileName += extension;

	// �t�@�C���ɃA�N�Z�X
	auto dataHandle = FileRead_open(fileName.c_str());

	// �f�[�^���𓾂�
	int dataNum = 0;
	int result = FileRead_read(&dataNum, sizeof(dataNum), dataHandle);
	assert(result != -1);

	// �f�[�^�̓ǂݎ��
	for (int i = 0; i < dataNum; i++)
	{
		UnityGameObject data;

		// ���O�̕����񐔂̓ǂݎ��
		uint8_t nameSize = 0;
		result = FileRead_read(&nameSize, sizeof(nameSize), dataHandle);
		assert(result != -1);

		// ���O���̂��̂�ǂݎ��
		data.name.resize(nameSize);
		result = FileRead_read(data.name.data(), sizeof(char) * nameSize, dataHandle);
		assert(result != -1);

		// ���W�f�[�^xyz��ǂ�
		result = FileRead_read(&data.pos, sizeof(data.pos), dataHandle);
		assert(result != -1);

		// Unity�Ƃ̍��W�f�[�^�����킹�邽�߂�100�{
		data.pos *= 100.0f;

		// ��]�f�[�^xyz��ǂ�
		result = FileRead_read(&data.rot, sizeof(data.rot), dataHandle);
		assert(result != -1);

		// �x���@���ʓx�@�ɕϊ�
		data.rot.x = MathUtil::ToDegree(data.rot.x);
		data.rot.y = MathUtil::ToDegree(data.rot.y);
		data.rot.z = MathUtil::ToDegree(data.rot.z);

		// Unity��DxLib�ł͉�]������邽�ߍ��킹��
		data.rot.y += DX_PI_F;

		// �g��f�[�^xyz��ǂ�
		result = FileRead_read(&data.scale, sizeof(data.scale), dataHandle);
		assert(result != -1);

		// �I�u�W�F�N�g�̖��O���Ƃɕۑ�
		m_data[data.name].push_back(data);
	}

	// �t�@�C�������
	FileRead_close(dataHandle);
}

// �C���X�^���X�̎擾
DataReaderFromUnity& DataReaderFromUnity::GetInstance()
{
	// �B��̃C���X�^���X��Ԃ�
	static DataReaderFromUnity instance;
	return instance;
}

// �I�u�W�F�N�g�̖��O����f�[�^���擾
const std::vector<UnityGameObject>& DataReaderFromUnity::GetData(std::string objectName) const
{
	// �f�[�^������������
	if (m_data.find(objectName) != m_data.end())
	{
		return m_data.find(objectName)->second;
	}
	// �f�[�^��������Ȃ�����
	return std::vector<UnityGameObject>();
}
