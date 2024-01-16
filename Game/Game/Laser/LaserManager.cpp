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
	m_pLaserList.remove_if([](LaserData data) { return !data.pLaser->IsEnabled(); });

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
void LaserManager::AddLaser(LaserType type, std::shared_ptr<EnemyBase> pEnemy, int laserFireFrame, float laserSpeed, bool isPlayerFollowing)
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
}

// ���[�U�[�̎擾	
const std::list<LaserData>& LaserManager::GetLaserList() const
{
	return m_pLaserList;
}