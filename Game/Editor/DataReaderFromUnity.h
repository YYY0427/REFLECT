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
	// �R���X�g���N�^
	DataReaderFromUnity();

	// �f�X�g���N�^
	~DataReaderFromUnity();

	// Unity�Ŕz�u�����I�u�W�F�N�g�̃f�[�^��ǂݎ��
	void LoadUnityGameObjectData(std::string fileName);

	// �ǂݎ�����f�[�^�̎擾
	const std::vector<UnityGameObject>& GetData(std::string objectName) const;

private:
	// �ǂݎ�����f�[�^
	// �����Ƀf�[�^���i�[����
	std::map<std::string, std::vector<UnityGameObject>> m_data;
};