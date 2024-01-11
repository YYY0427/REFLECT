#pragma once
#include <string>
#include <map>
#include <vector>
#include "../Math/Vector3.h"

// Unity�Ŕz�u�����I�u�W�F�N�g�̃f�[�^
struct UnityGameObject
{
	std::string name;
	Vector3 pos;
	Vector3 rot;
	Vector3 scale;
};

/// <summary>
/// Unity����z�u�f�[�^��ǂݍ��ރN���X
/// </summary>
class DataReaderFromUnity
{
public:
	// �f�X�g���N�^
	~DataReaderFromUnity();

	// Unity�Ŕz�u�����I�u�W�F�N�g�̃f�[�^��ǂݎ��
	void LoadUnityGameObjectData(std::string fileName);

	// �C���X�^���X�̎擾
	static DataReaderFromUnity& GetInstance();

	// �ǂݎ�����f�[�^�̎擾
	const std::vector<UnityGameObject>& GetData(std::string objectName) const;

private:
	// �R���X�g���N�^
	DataReaderFromUnity();

	// �R�s�[��������֎~
	DataReaderFromUnity(const DataReaderFromUnity&) = delete;	// �R�s�[�R���X�g���N�^�֎~
	void operator = (const DataReaderFromUnity&) = delete;		// ����֎~

private:
	// �ǂݎ�����f�[�^
	// �����Ƀf�[�^���i�[����
	std::map<std::string, std::vector<UnityGameObject>> m_data;
};