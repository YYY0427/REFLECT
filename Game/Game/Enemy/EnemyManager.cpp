#include "EnemyManager.h"
#include "EnemyBase.h"
#include "Normal/Mosquito.h"
#include "Boss/BossMosquito.h"
#include "Boss/BossMatrix.h"
#include "../../String/StringUtil.h"
#include "../../Util/DrawFunctions.h"
#include "../../UI/Warning.h"
#include "../../UI/UIManager.h"
#include "../../MyDebug/DebugText.h"
#include "../Player.h"
#include <fstream>
#include <sstream>
#include <cassert>
#include <DxLib.h>

namespace
{
	// �t�@�C���̊K�w
	const std::string wave_file_hierarchy = "Data/Wave/";					// �E�F�[�u
	const std::string enemy_file_hierarchy = "Data/Enemy/";					// �G
	const std::string enemy_action_file_hierarchy = "Data/EnemyAction/";	// �G�̍s��

	// �t�@�C���̊g���q
	const std::string file_extension = ".csv";				

	// �{�X�G�o�ꎞ�̌x���̃t���[��
	constexpr int warning_frame = 180;
}

// �R���X�g���N�^
EnemyManager::EnemyManager(std::shared_ptr<Player> pPlayer, std::shared_ptr<LaserManager> pLaserManager, std::shared_ptr<ScreenShaker> pScreenShaker) :
	m_waveNow(0),
	m_isNextWave(false),
	m_isLoadWave(false),
	m_isDeadBoss(false),
	m_isBoss(false),
	m_pPlayer(pPlayer),
	m_pLaserManager(pLaserManager),
	m_pScreenShaker(pScreenShaker),
	m_bossType(BossEnemyType::NONE),
	m_isStartWave(false)
{
	// �X�e�[�g�}�V���̐ݒ�
	m_stateMachine.AddState(State::NORMAL, {}, [this]() {UpdateNormal(); }, {});
	m_stateMachine.AddState(State::WARNING, {}, [this]() {UpdateWarning(); }, {});
	m_stateMachine.SetState(State::NORMAL);
}

// �f�X�g���N�^
EnemyManager::~EnemyManager()
{
}

// �X�V
void EnemyManager::Update()
{
	// �X�e�[�g�}�V���̍X�V
	m_stateMachine.Update();
}

// �ʏ펞�̍X�V
void EnemyManager::UpdateNormal()
{
	// ���݃t���O���������Ă���G�̍폜
	m_pEnemyList.remove_if([](std::shared_ptr<EnemyBase> data) { return !data->IsEnabled(); });

	// �G���G�̍X�V
	for (auto& enemy : m_pEnemyList)
	{
		enemy->Update();
	}

	// �{�X�G���o�����Ă�����
	if (m_pBossEnemy)
	{
		// �{�X�G���o�����Ă��āA���{�X�G���|����Ă�����
		if (!m_pBossEnemy->IsEnabled())
		{
			// �{�X�G���|���ꂽ���Ƃɂ���
			m_isDeadBoss = true;
		}

		// �X�V
		m_pBossEnemy->Update();
	}
}

// �x�����̍X�V
void EnemyManager::UpdateWarning()
{
	// �x�����I��������
	if (m_pWarning->IsEnd())
	{
		// �x���̍폜
		UIManager::GetInstance().DeleteUI("Warning");

		// �{�X�G�̐���
		AddBossEnemy(m_bossType);

		// �X�e�[�g��ʏ�ɑJ��
		m_stateMachine.SetState(State::NORMAL);
	}
}

// �`��
void EnemyManager::Draw()
{
	// �G���G�̕`��
	for (auto& enemy : m_pEnemyList)
	{
		enemy->Draw();
	}

	// �{�X�G���o�����Ă�����`��
	if (m_pBossEnemy)
	{
		m_pBossEnemy->Draw();
	}

	// �f�o�b�O�p
#ifdef _DEBUG
	// �G���G�̍��W�̕`��
	for (int i = 0; i < m_pEnemyList.size(); i++)
	{
		auto itr = m_pEnemyList.begin();
		std::advance(itr, i);

		DebugText::Log("NormalEnemyPos", { itr->get()->GetPos().x, itr->get()->GetPos().y, itr->get()->GetPos().z });
	}
#endif
}

// �E�F�[�u�̃X�^�[�g
void EnemyManager::StartWave()
{
	// ���ɃE�F�[�u���n�܂��Ă�����Ȃɂ����Ȃ�
	if (m_isStartWave) return;

	// �t���O�𗧂Ă�
	m_isStartWave = true;

	// �E�F�[�u�f�[�^��ǂݍ���ł��Ȃ�������~�߂�
	if (!m_isLoadWave)
	{
		assert(!"�E�F�[�u�f�[�^��ǂݍ���ł�������");
	}

	// �ŏ��̃E�F�[�u�f�[�^�����s
	auto& waveData = m_waveTable.front();

	// �G���G�̐���
	for (auto& data : waveData.enemyDataList)
	{
		AddEnemy(data);
	}
}

// ���̃E�F�[�u��
void EnemyManager::NextWave()
{
	// �܂��G���c���Ă�����Ȃɂ����Ȃ�
	for (auto& enemy : m_pEnemyList)
	{
		if (enemy->IsEnabled())
		{
			return;
		}
	};

	// �{�X�G���o�����Ă�����Ȃɂ����Ȃ�
	if (m_pBossEnemy)	return;

	// �Ō�̃E�F�[�u��������{�X�G�𐶐�
	if(m_waveNow == m_waveTable.size() - 1)
	{
		// �{�X�G�����Ȃ�������
		if (m_bossType == BossEnemyType::NONE)
		{
			// �{�X�G���|���ꂽ���Ƃɂ���
			m_isDeadBoss = true;
		}
		else
		{
			// �x����ԂɑJ��
			m_stateMachine.SetState(State::WARNING);

			// �x���̐���
			m_pWarning = std::make_shared<Warning>(warning_frame);
			UIManager::GetInstance().AddUI("Warning", m_pWarning, 0, { 0, 0 });
		}
	}
	else
	{
		// �E�F�[�u��i�߂�
		m_waveNow++;
		auto& waveData = m_waveTable[m_waveNow];

		// �G���G�̐���
		for (auto& data : waveData.enemyDataList)
		{
			AddEnemy(data);
		}
	}
}

// �G�̒ǉ�
void EnemyManager::AddEnemy(EnemyData data)
{
	// �G�̎�ނɂ���Đ�������G��ς���
	switch (data.type)
	{
	// ��
	case EnemyType::MOSQUITO:
		m_pEnemyList.push_back(std::make_shared<Mosquito>(
			data,
			m_pPlayer,
			m_pLaserManager));
		break;

	default:
		// �����ɗ�����G�̎�ނ��ǉ�����Ă��Ȃ�
		assert(!"�G�̎�ނ�����܂���");
	}
}

// �{�X�G�̒ǉ�
void EnemyManager::AddBossEnemy(BossEnemyType type)
{
	// ���Ƀ{�X�G����������Ă�����
	if(m_pBossEnemy)
	{
		return;
	}

	// ��ނɂ���ă{�X�G�̐���
	switch (type)
	{	
	case BossEnemyType::MOSQUITO:
		m_pBossEnemy = std::make_shared<BossMosquito>(
			m_pPlayer,
			m_pLaserManager);
		break;

	case BossEnemyType::MATRIX:
		m_pBossEnemy = std::make_shared<BossMatrix>(
			m_pPlayer,
			m_pLaserManager,
			m_pScreenShaker);
		break;

	case BossEnemyType::NONE:
		break;
	default:
		// �����ɗ�����G�̎�ނ��ǉ�����Ă��Ȃ�
		assert(!"�{�X�G�̎�ނ�����܂���");
	}
}

// �E�F�[�u�̃f�[�^�̓ǂݍ���
void EnemyManager::LoadWaveFileData(std::string filePath)
{
	// �t���O�𗧂Ă�
	m_isLoadWave = true;

	// �t�@�C�����̓ǂݍ���(�ǂݍ��݂Ɏ��s������~�߂�)
	std::string localFilePath = wave_file_hierarchy + filePath + file_extension;
	std::ifstream ifs(localFilePath);
	assert(ifs && "Wave�f�[�^�̓ǂݍ��ݎ��s");

	// csv�f�[�^��1�s���ǂݎ��
	bool isFirst = false;
	std::string line;
	while (getline(ifs, line))
	{
		// 1�s�ڂ͓ǂݍ��܂Ȃ�
		// 1�s�ڂɂ͍��ڂ������Ă��邽��
		if (!isFirst)
		{
			isFirst = true;
			continue;
		}

		// csv�f�[�^�P�s��','�ŕ����̕�����ɕϊ�
		std::vector<std::string> strvec = StringUtil::Split(line, ',');

		// �G�̃f�[�^�̓ǂݍ���
		WaveData data{};
		for (int i = 0; i < strvec.size(); i++)
		{
			if(i == strvec.size() - 1)
			{
				// �{�X�G�̎�ނ̓ǂݍ���
				m_bossType = static_cast<BossEnemyType>(std::stoi(strvec[i]));
			}
			else
			{
				// �G�̃f�[�^�̒ǉ�
				data.enemyDataList = LoadEnemyFileData(strvec[i]);

				// �E�F�[�u�̃f�[�^�̒ǉ�
				m_waveTable.push_back(data);
			}
		}
	}
}

// �G�̃f�[�^�̓ǂݍ���
std::vector<EnemyData> EnemyManager::LoadEnemyFileData(std::string filePath)
{
	// �t�@�C�����̓ǂݍ���(�ǂݍ��݂Ɏ��s������~�߂�)
	std::string localFilePath = enemy_file_hierarchy + filePath + file_extension;
	std::ifstream ifs(localFilePath);
	assert(ifs && "Enemy�f�[�^�̓ǂݍ��ݎ��s");

	// ������
	std::vector<EnemyData> dataTable{};
	bool isFirst = false;
	std::string line;

	// csv�f�[�^��1�s���ǂݎ��
	while (getline(ifs, line))
	{
		// 1�s�ڂ͓ǂݍ��܂Ȃ�
		// 1�s�ڂɂ͍��ڂ������Ă��邽��
		if (!isFirst)
		{
			isFirst = true;
			continue;
		}

		// csv�f�[�^�P�s��','�ŕ����̕�����ɕϊ�
		std::vector<std::string> strvec = StringUtil::Split(line, ',');

		EnemyData data{};

		// ���W�̓ǂݍ���
		data.pos.x = std::stof(strvec[0]);
		data.pos.y = std::stof(strvec[1]);
		data.pos.z = std::stof(strvec[2]);

		// ��ނ̓ǂݍ���
		data.type = static_cast<EnemyType>(std::stoi(strvec[3]));

		// HP�̓ǂݍ���
		data.hp = std::stoi(strvec[4]);

		// �U���͂̓ǂݍ���
		data.attack = std::stoi(strvec[5]);

		// �傫���̓ǂݍ���
		data.scale = std::stof(strvec[6]);

		// �ړ����x�̓ǂݍ���
		data.speed = std::stof(strvec[7]);

		// �s���f�[�^�̓ǂݍ���
		data.actionDataList = LoadEnemyActionFileData(strvec[8]);

		// �f�[�^�̒ǉ�
		dataTable.push_back(data);
	}
	return dataTable;
}

// �G�̍s���̃f�[�^�̓ǂݍ���
std::vector<EnemyActionData> EnemyManager::LoadEnemyActionFileData(std::string filePath)
{
	// �t�@�C�����̓ǂݍ���(�ǂݍ��݂Ɏ��s������~�߂�)
	std::string localFilePath = enemy_action_file_hierarchy + filePath + file_extension;
	std::ifstream ifs(localFilePath);
	assert(ifs && "EnemyAction�f�[�^�̓ǂݍ��ݎ��s");

	// ������
	std::vector<EnemyActionData> dataTable;
	bool isFirst = false;
	std::string line;

	// csv�f�[�^��1�s���ǂݎ��
	while (getline(ifs, line))
	{
		// 1�s�ڂ͓ǂݍ��܂Ȃ�
		// 1�s�ڂɂ͍��ڂ������Ă��邽��
		if (!isFirst)
		{
			isFirst = true;
			continue;
		}

		// csv�f�[�^�P�s��','�ŕ����̕�����ɕϊ�
		std::vector<std::string> strvec = StringUtil::Split(line, ',');

		EnemyActionData data{};

		// �ړI�n�̓ǂݍ���
		data.goalPos.x = std::stof(strvec[0]);
		data.goalPos.y = std::stof(strvec[1]);
		data.goalPos.z = std::stof(strvec[2]);

		// �ړI�n�ɓ��B���Ă��玟�̖ړI�n�Ɍ������܂ł̑ҋ@�t���[���̓ǂݍ���
		data.idleFrame = std::stoi(strvec[3]);

		// �ړI�n�ɓ��B�����烌�[�U�[�𔭎˂��邩�ǂ����̃t���O�̓ǂݍ���
		data.isLaser = std::stoi(strvec[4]);

		// ���[�U�[�𔭎˂���ꍇ
		if (data.isLaser)
		{
			// ���[�U�[�̎�ނ̓ǂݍ���
			data.laserType = static_cast<LaserType>(std::stoi(strvec[5]));

			// ���[�U�[�𔭎˂���܂ł̃`���[�W�t���[���̓ǂݍ���
			data.laserChargeFrame = std::stoi(strvec[6]);

			// ���[�U�[�𔭎˂���܂ł̑ҋ@�t���[���̓ǂݍ���
			data.laserIdleFrame = std::stoi(strvec[7]);

			// ���[�U�[�̑��x�̓ǂݍ���
			data.laserSpeed = std::stof(strvec[8]);

			// ���[�U�[�����t���[���̊ԁA���˂��邩�̓ǂݍ���
			data.laserFireFrame = std::stoi(strvec[9]);

			// ���[�U�[���v���C���[��Ǐ]���邩�ǂ����̃t���O�̓ǂݍ���
			data.isPlayerFollowing = std::stoi(strvec[10]);
		}

		// �f�[�^�̒ǉ�
		dataTable.push_back(data);
	}
	return dataTable;
}

// �{�X�G�̎��S����
bool EnemyManager::IsDeadBoss() const
{
	return m_isDeadBoss;
}

// ���݂̃E�F�[�u���I���������ǂ���
bool EnemyManager::IsEndWave() const
{
	// �܂��G���c���Ă�����
	for (auto& enemy : m_pEnemyList)
	{
		if (enemy->IsEnabled())
		{
			return false;
		}
	}

	// �{�X�G���o�����Ă�����
	if (m_pBossEnemy)
	{
		return false;
	}

	// ����ȊO�̓E�F�[�u���I�����Ă���
	return true;
}

// �G���G�̃��X�g�̎擾
const std::list<std::shared_ptr<EnemyBase>>& EnemyManager::GetEnemyList() const
{
	return m_pEnemyList;
}

// �{�X�G�̎擾
const std::shared_ptr<EnemyBase>& EnemyManager::GetBossEnemy() const
{
	return m_pBossEnemy;
}