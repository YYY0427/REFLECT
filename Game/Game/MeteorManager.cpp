#include "MeteorManager.h"
#include "../Util/DrawFunctions.h"
#include "../Editor/DataReaderFromUnity.h"
#include <string>

namespace
{
	// ���f���̃t�@�C���p�X
	const std::string model_file_path = "Data/Model/Meteor.mv1";
}

// �R���X�g���N�^
MeteorManager::MeteorManager(std::string objectDataFileName) :
	m_createIntervalFrameTimer(0)
{
	// ���f���̓ǂݍ���
	m_modelHandle = my::MyLoadModel(model_file_path.c_str());

	// �z�u�f�[�^�����݂���ꍇ�͔z�u�f�[�^����覐΂𐶐�
	auto& data = DataReaderFromUnity::GetInstance().GetData(objectDataFileName, "Meteor");
	for (auto& meteorData : data)
	{
		m_pMeteorList.push_back(std::make_shared<Meteor>(m_modelHandle, meteorData));
	}
}

// �f�X�g���N�^
MeteorManager::~MeteorManager()
{
}

// �X�V
void MeteorManager::Update(Vector3 cameraPos)
{
	// ���݂��Ȃ�覐΂��폜
	m_pMeteorList.remove_if([](std::shared_ptr<Meteor> meteor) { return !meteor->IsEnabled(); });

	// 覐΂̍X�V
	for (auto& meteor : m_pMeteorList)
	{
		meteor->Update(cameraPos);
	}
}

// �`��
void MeteorManager::Draw()
{
	for (auto& meteor : m_pMeteorList)
	{
		meteor->Draw();
	}
}

// 覐΂̐���
void MeteorManager::CreateMeteor(int createIntervalFrame, Vector3 playerPos)
{
	// �^�C�}�[�̍X�V
	m_createIntervalFrameTimer++;

	// �^�C�}�[���w��t���[���𒴂�����
	if (m_createIntervalFrameTimer > createIntervalFrame)
	{
		// 覐΂̐���
		m_pMeteorList.push_back(std::make_shared<Meteor>(m_modelHandle, playerPos));

		// �^�C�}�[�̃��Z�b�g
		m_createIntervalFrameTimer = 0;
	}
}

// �X���[�l�̐ݒ�
void MeteorManager::SetSlowValue(float slowValue)
{
	for (auto& meteor : m_pMeteorList)
	{
		meteor->SetSlowValue(slowValue);
	}
}

// 覐΂̎擾
const std::list<std::shared_ptr<Meteor>>& MeteorManager::GetMeteor() const
{
	return m_pMeteorList;
}
