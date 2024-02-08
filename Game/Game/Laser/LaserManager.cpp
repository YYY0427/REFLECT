#include "LaserManager.h"
#include "LaserBase.h"
#include "NormalLaser.h"
#include "../../Util/DrawFunctions.h"
#include "../Shield.h"
#include "ReflectLaser.h"
#include "CubeLaser.h"
#include "../Player.h"
#include "../Shield.h"
#include <cassert>
#include <string>

// �R���X�g���N�^
LaserManager::LaserManager(std::shared_ptr<Player> pPlayer) :
	m_pPlayer(pPlayer)
{
}

// �f�X�g���N�^
LaserManager::~LaserManager()
{
}

// �X�V
void LaserManager::Update()
{
	// ���݃t���O���������Ă���̃��[�U�[���폜
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

// ���˃��[�U�[�̒ǉ�
int LaserManager::AddReflectLaser(std::shared_ptr<Shield> pShield, std::shared_ptr<LaserBase> pLaser, Vector3 firePos)
{
	// ���[�U�[�̃f�[�^���쐬
	LaserData laserData;
	laserData.type = LaserType::REFLECT;

	// Key�̐ݒ�
	laserData.key = 0;
	for (auto& laser : m_pLaserList)
	{
		if (laserData.key <= laser.key)
		{
			laserData.key = laser.key + 1;
		}
	}

	// ���[�U�[�̃|�C���^��ݒ�
	laserData.pLaser = std::make_shared<ReflectLaser>(pShield, pLaser, firePos);

	// ���[�U�[���X�g�ɒǉ�
	m_pLaserList.push_back(laserData);

	return laserData.key;
}

// �L���[�u���[�U�[�̒ǉ�
int LaserManager::AddCubeLaser(Vector3 firePos, float laserSpeed)
{
	// ���[�U�[�̃f�[�^���쐬
	LaserData laserData;
	laserData.type = LaserType::CUBE;

	// Key�̐ݒ�
	laserData.key = 0;
	for (auto& laser : m_pLaserList)
	{
		if (laserData.key <= laser.key)
		{
			laserData.key = laser.key + 1;
		}
	}

	// ���[�U�[�̃|�C���^��ݒ�
	laserData.pLaser = std::make_shared<CubeLaser>(firePos, laserSpeed, m_pPlayer);

	// ���[�U�[���X�g�ɒǉ�
	m_pLaserList.push_back(laserData);

	// Key��Ԃ�
	return laserData.key;
}

// ���[�U�[�̍폜
void LaserManager::DeleteLaser(int key)
{
	// ���[�U�[�̍폜
	for (auto& laser : m_pLaserList)
	{
		if (laser.key == key)
		{
			laser.pLaser->Delete();
		}
	}
}

// �S�Ẵ��[�U�[�̍폜
void LaserManager::DeleteAllLaser()
{
	// ���[�U�[�̍폜
	for (auto& laser : m_pLaserList)
	{
		laser.pLaser->Delete();
	}
	m_pLaserList.clear();
}

// ���[�U�[�̎擾	
const std::list<LaserData>& LaserManager::GetLaserList() const
{
	return m_pLaserList;
}

// ���[�U�[�̎擾
const LaserData& LaserManager::GetLaserData(int key) const
{
	for (auto& laser : m_pLaserList)
	{
		if (laser.key == key)
		{
			return laser;
		}
	}

	assert(!"���[�U�[��������܂���ł���");
	return m_pLaserList.front();
}

// ���[�U�[�̈ʒu�̐ݒ�
void LaserManager::SetLaserPosition(int key, Vector3 pos)
{
	for (auto& laser : m_pLaserList)
	{
		if (laser.key == key)
		{
			laser.pLaser->SetPos(pos);
		}
	}
}
