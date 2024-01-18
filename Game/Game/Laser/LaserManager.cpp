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
	for (auto it = m_pLaserList.begin(); it != m_pLaserList.end();)
	{
		// ���[�U�[�������ɂȂ�����폜
		if (!it->second.pLaser->IsEnabled())
		{
			// ���[�U�[�̍폜
			it = m_pLaserList.erase(it);
		}
		else
		{
			// ���̗v�f��
			it++;
		}
	}

	// ���[�U�[�̍X�V
	for (auto& laser : m_pLaserList)
	{
		laser.second.pLaser->Update();
	}
}

// �`��
void LaserManager::Draw()
{
	for (auto& laser : m_pLaserList)
	{
		laser.second.pLaser->Draw();
	}
}

// ���[�U�[�̒ǉ�
int LaserManager::AddLaser(LaserType type, std::shared_ptr<EnemyBase> pEnemy, int laserFireFrame, float laserSpeed, bool isPlayerFollowing)
{
	LaserData laserData;
	laserData.type = type;

	// ���[�U�[�̎�ނɂ���ď����𕪊�
	switch (laserData.type)
	{
	case LaserType::NORMAL:
		laserData.pLaser = std::make_shared<NormalLaser>(
			m_modelHandleTable[LaserType::NORMAL],
			pEnemy, m_pPlayer, laserFireFrame, laserSpeed, isPlayerFollowing);
		break;
	default:
		assert(!"���[�U�[�̎�ނ�����܂���");
	}

	// Key�̐ݒ�
	int key = 0;
	if (m_pLaserList.size() != 0)
	{
		key = m_pLaserList.rbegin()->first + 1;
	}

	// ���[�U�[���X�g�ɒǉ�
	m_pLaserList[key] = laserData;

	// Key��Ԃ�
	return key;
}

// ���[�U�[�̍폜
void LaserManager::DeleteLaser(int key)
{
	// ���[�U�[�̍폜
	m_pLaserList.erase(key);
}

// ���[�U�[�̎擾	
const std::map<int, LaserData>& LaserManager::GetLaserList() const
{
	return m_pLaserList;
}