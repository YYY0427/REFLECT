#include "LaserManager.h"
#include "LaserBase.h"
#include "NormalLaser.h"
#include "../../Util/DrawFunctions.h"
#include <cassert>
#include <string>

namespace
{
	// �ʏ탌�[�U�[�̃��f���t�@�C���p�X
	const std::string normal_laser_model_file_path = "Data/Model/Laser.mv1";	
} 

// �R���X�g���N�^
LaserManager::LaserManager(std::shared_ptr<Player> pPlayer) :
	m_pPlayer(pPlayer)
{
	// ���f���̓ǂݍ���
	m_modelHandleTable[LaserType::NORMAL] = my::MyLoadModel(normal_laser_model_file_path.c_str());
}

// �f�X�g���N�^
LaserManager::~LaserManager()
{
}

// �X�V
void LaserManager::Update()
{
	// �s�v�ɂȂ������[�U�[�̍폜
	m_pLaserList.remove_if([](const LaserData& laser) { return !laser.pLaser->IsEnabled(); });

	// ���[�U�[�̍X�V
	for (auto& laser : m_pLaserList)
	{
		laser.pLaser->Update();
	}
}

// �`��
void LaserManager::Draw()
{
	for (auto& laser : m_pLaserList)
	{
		laser.pLaser->Draw();
	}
}

// ���[�U�[�̒ǉ�
int LaserManager::AddLaser(LaserType type, std::shared_ptr<EnemyBase> pEnemy, int laserChargeFrame, int laserFireFrame, float laserSpeed, bool isPlayerFollowing)
{
	LaserData laserData;
	laserData.type = type;

	// ���[�U�[�̎�ނɂ���ď����𕪊�
	switch (laserData.type)
	{
	case LaserType::NORMAL:
		laserData.pLaser = std::make_shared<NormalLaser>(
			m_modelHandleTable[LaserType::NORMAL],
			pEnemy, m_pPlayer, laserChargeFrame, laserFireFrame, laserSpeed, isPlayerFollowing);
		break;
	default:
		assert(!"���[�U�[�̎�ނ�����܂���");
	}

	// Key�̐ݒ�
	laserData.key = 0;
	for (auto& laser : m_pLaserList)
	{
		if (laserData.key <= laser.key)
		{
			laserData.key = laser.key + 1;
		}
	}

	// ���[�U�[���X�g�ɒǉ�
	m_pLaserList.push_back(laserData);

	// Key��Ԃ�
	return laserData.key;
}

// ���[�U�[�̍폜
void LaserManager::DeleteLaser(int key)
{
	// ���[�U�[�̍폜
	m_pLaserList.remove_if([key](const LaserData& laser) { return laser.key == key; });
}

// ���[�U�[�̎擾	
const std::list<LaserData>& LaserManager::GetLaserList() const
{
	return m_pLaserList;
}