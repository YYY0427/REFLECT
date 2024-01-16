#include "EnemyManager.h"
#include "BossEnemyBase.h"
#include "EnemyBase.h"
#include "Mosquito.h"
#include "BossMosquito.h"
#include "../../StringManager.h"
#include "../../Util/DrawFunctions.h"
#include <fstream>
#include <sstream>
#include <cassert>

namespace
{
	// �t�@�C���̊K�w
	const std::string wave_file_hierarchy = "Data/Wave/";					// �E�F�[�u
	const std::string enemy_file_hierarchy = "Data/Enemy/";					// �G
	const std::string enemy_action_file_hierarchy = "Data/EnemyAction/";	// �G�̍s��

	// �t�@�C���̊g���q
	const std::string file_extension = ".csv";				

	// �G�̃��f���̃t�@�C���p�X
	const std::string mosquito_model_file_path = "Data/Model/Mosquito.mv1";	// ��
}

// �R���X�g���N�^
EnemyManager::EnemyManager(std::shared_ptr<Player> pPlayer, std::shared_ptr<LaserManager> pLaserManager) :
	m_waveNow(0),
	m_isNextWave(false),
	m_isLoadWave(false),
	m_pPlayer(pPlayer),
	m_pLaserManager(pLaserManager)
{
	// �G���G���f���n���h���̓ǂݍ���
	m_modelHandleTable[EnemyType::MOSQUITO] = my::MyLoadModel(mosquito_model_file_path.c_str());
	
	// �{�X�G���f���n���h���̓ǂݍ���
	m_bossModelHandleTable[BossEnemyType::NONE] = -1;
	m_bossModelHandleTable[BossEnemyType::MOSQUITO] = m_modelHandleTable[EnemyType::MOSQUITO];
}

// �f�X�g���N�^
EnemyManager::~EnemyManager()
{
}

// �X�V
void EnemyManager::Update()
{
	// �G���G�̍X�V
	for (auto& enemy : m_pEnemyList)
	{
		enemy->Update();
	}

	// �{�X�G���o�����Ă�����X�V
	if(m_pBossEnemy)
	{
		m_pBossEnemy->Update();
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
}

// �E�F�[�u�̃X�^�[�g
void EnemyManager::StartWave()
{
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
	if (m_pBossEnemy)
	{
		return;
	};

	// �E�F�[�u��i�߂�
	m_waveNow++;
	auto& waveData = m_waveTable[m_waveNow];

	// �Ō�̃E�F�[�u��������{�X�G�𐶐�
	if(m_waveNow == m_waveTable.size() - 1)
	{
		// �{�X�G�̐���
		AddBossEnemy(waveData.bossType);
	}
	else
	{
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
			m_modelHandleTable[data.type], 
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
		m_pBossEnemy = std::make_shared<BossMosquito>(m_bossModelHandleTable[type]);
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
		std::vector<std::string> strvec = StringManager::GetInstance().SplitString(line, ',');

		WaveData data{};

		// �Ō�̍s�̓{�X�G�̎�ނ̓ǂݍ���
		if (ifs.eof())
		{
			data.bossType = static_cast<BossEnemyType>(std::stoi(strvec[0]));
		}
		// ����ȊO�͎G���G�̃f�[�^�̓ǂݍ���
		else
		{
			// �G�̃f�[�^�̓ǂݍ���
			for (auto& str : strvec)
			{
				// �G�̃f�[�^�̒ǉ�
				data.enemyDataList.push_back(LoadEnemyFileData(str));

				// �{�X�G�̎�ނ͖���
				data.bossType = BossEnemyType::NONE;
			}
		}
		// �E�F�[�u�̃f�[�^�̒ǉ�
		m_waveTable.push_back(data);
	}
}

// �G�̃f�[�^�̓ǂݍ���
EnemyData EnemyManager::LoadEnemyFileData(std::string filePath)
{
	// �t�@�C�����̓ǂݍ���(�ǂݍ��݂Ɏ��s������~�߂�)
	std::string localFilePath = enemy_file_hierarchy + filePath + file_extension;
	std::ifstream ifs(localFilePath);
	assert(ifs && "Enemy�f�[�^�̓ǂݍ��ݎ��s");

	// ������
	EnemyData data{};
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
		std::vector<std::string> strvec = StringManager::GetInstance().SplitString(line, ',');

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

		// �ړ����x�̓ǂݍ���
		data.speed = std::stof(strvec[6]);

		// �傫���̓ǂݍ���
		data.scale = std::stof(strvec[7]);

		// �s���f�[�^�̓ǂݍ���
		data.actionDataList = LoadEnemyActionFileData(strvec[8]);
	}
	return data;
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
		std::vector<std::string> strvec = StringManager::GetInstance().SplitString(line, ',');

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
		//	data.laserType = static_cast<LaserType>(std::stoi(strvec[5]));

			// ���[�U�[�𔭎˂���܂ł̑ҋ@�t���[���̓ǂݍ���
			data.laserIdleFrame = std::stoi(strvec[6]);

			// ���[�U�[�̑��x�̓ǂݍ���
			data.laserSpeed = std::stof(strvec[7]);

			// ���[�U�[�����t���[���̊ԁA���˂��邩�̓ǂݍ���
			data.laserFireFrame = std::stoi(strvec[8]);
		}

		// �f�[�^�̒ǉ�
		dataTable.push_back(data);
	}
	return dataTable;
}
