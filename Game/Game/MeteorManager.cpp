#include "MeteorManager.h"
#include "../Util/DrawFunctions.h"
#include "../Editor/DataReaderFromUnity.h"
#include <string>

namespace
{
	// ������覐΂̐����Ԋu
	const int small_create_interval_frame = 10;
}

// �R���X�g���N�^
MeteorManager::MeteorManager(std::string objectDataFileName) :
	m_createIntervalFrame(0),
	m_smallCreateIntervalFrame(0)
{
	// �z�u�f�[�^�����݂���ꍇ�͔z�u�f�[�^����覐΂𐶐�
	auto data = DataReaderFromUnity::GetInstance().GetData(objectDataFileName, "Meteor2");
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

// ������覐΂̐���
void MeteorManager::SmallMeteorCreate(Vector3 playerPos)
{
	m_smallCreateIntervalFrame++;
	if (small_create_interval_frame < m_smallCreateIntervalFrame)
	{
		// ������覐΂̐���
		m_pMeteorList.push_back(std::make_shared<Meteor>(MeteorType::SMALL, playerPos));
		m_smallCreateIntervalFrame = 0;
	}
}

// 覐΂̐���
void MeteorManager::CreateMeteor(int createIntervalFrame, Vector3 playerPos)
{
	// �^�C�}�[�̍X�V
	m_createIntervalFrame++;

	// �^�C�}�[���w��t���[���𒴂�����
	if (m_createIntervalFrame > createIntervalFrame)
	{
		// 覐΂̐���
		m_pMeteorList.push_back(std::make_shared<Meteor>(MeteorType::NORMAL, playerPos));

		// �^�C�}�[�̃��Z�b�g
		m_createIntervalFrame = 0;
	}
}

// 覐΂̍폜
void MeteorManager::DeleteMeteor()
{
	m_pMeteorList.clear();
}

// 覐΂̎擾
const std::list<std::shared_ptr<Meteor>>& MeteorManager::GetMeteor() const
{
	return m_pMeteorList;
}
