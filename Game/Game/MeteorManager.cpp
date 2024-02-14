#include "MeteorManager.h"
#include "../Util/DrawFunctions.h"
#include "../Editor/DataReaderFromUnity.h"
#include <string>

// �R���X�g���N�^
MeteorManager::MeteorManager(std::string objectDataFileName) :
	m_createIntervalFrameTimer(0)
{
	// �z�u�f�[�^�����݂���ꍇ�͔z�u�f�[�^����覐΂𐶐�
	auto& data = DataReaderFromUnity::GetInstance().GetData(objectDataFileName, "Meteor2");
	for (auto& meteorData : data)
	{
		m_pMeteorList.push_back(std::make_shared<Meteor>(meteorData));
	}
}

// �f�X�g���N�^
MeteorManager::~MeteorManager()
{
}

// �X�^�[�g���o���̍X�V
void MeteorManager::UpdateStart(Vector3 playerVec)
{
	// 覐΂̍X�V
	for (auto& meteor : m_pMeteorList)
	{
		meteor->UpdateStart(playerVec);
	}
}

void MeteorManager::UpdateSmallMeteor()
{
	// 覐΂̍X�V
	for (auto& meteor : m_pMeteorList)
	{
//		meteor->UpdateSmallMeteor();
	}
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
		m_pMeteorList.push_back(std::make_shared<Meteor>(playerPos));

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
