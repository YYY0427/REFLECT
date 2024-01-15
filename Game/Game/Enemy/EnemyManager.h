#pragma once
#include <memory>
#include <list>
#include <vector>
#include <string>
#include <map>
#include "../../Math/Vector3.h"

// �v���g�^�C�v�錾
class EnemyBase;
class BossEnemyBase;
class Player;

// �G�̎��
enum class EnemyType
{
	// �ʏ�̓G
	MOSQUITO,		// ��
};

// �{�X�G�̎��
enum class BossEnemyType
{
	// �{�X�G
	MOSQUITO,		// ��
	NONE,			// �Ȃ�
};

// �G�̍s���̃f�[�^
struct EnemyActionData
{
	Vector3 goalPos;	// �ړI�n
	int idleFrame;		// �ړI�n�ɓ��B���Ă��玟�̖ړI�n�Ɍ������܂ł̑ҋ@�t���[��
	bool isLaser;		// �ړI�n�ɓ��B�����烌�[�U�[������
	int laserType;		// ���[�U�[�����ꍇ�A�ǂ̃��[�U�[������
	int laserIdleFrame;	// ���[�U�[�����ꍇ�A�ړI�n�ɓ��B���Ă��烌�[�U�[�����܂ł̑ҋ@�t���[��
	float laserSpeed;	// ���[�U�[�����ꍇ�A���[�U�[�̈ړ����x
	int laserFireFrame; // ���[�U�[�����t���[�����˂������邩
};

// �G�̃f�[�^
struct EnemyData
{
	Vector3 pos;	// �G�̏����ʒu
	EnemyType type;	// �G�̎��
	int hp;			// �G�̗̑�
	int attack;		// �G�̍U����
	float speed;		// �G�̈ړ����x
	float scale;		// �G�̑傫��
	std::vector<EnemyActionData> actionDataList;	// �G�̍s���f�[�^���X�g
};

// �E�F�[�u�f�[�^
struct WaveData
{
	std::vector<EnemyData> enemyDataList;	// �G�̃f�[�^���X�g
	BossEnemyType bossType;						// �{�X�̎��
};

/// <summary>
/// �G�̊Ǘ��N���X
/// </summary>
class EnemyManager
{
public:
	// �R���X�g���N�^
	EnemyManager(std::shared_ptr<Player> pPlayer);

	// �f�X�g���N�^
	~EnemyManager();

	// �X�V
	void Update();

	// �`��
	void Draw();

	// �E�F�[�u�X�^�[�g
	void StartWave();

	// ���̃E�F�[�u��
	void NextWave();

	// �G���G�̒ǉ�
	void AddEnemy(EnemyData data);

	// �{�X�G�̒ǉ�
	void AddBossEnemy(BossEnemyType type);

	// �t�@�C���f�[�^�̓ǂݍ���
	void LoadWaveFileData(std::string filePath);		// �E�F�[�u
	EnemyData LoadEnemyFileData(std::string filePath);	// �G
	std::vector<EnemyActionData> LoadEnemyActionFileData(std::string filePath);	// �G�̍s��

private:
	// �|�C���^
	std::shared_ptr<Player> m_pPlayer;						// �v���C���[
	std::list<std::shared_ptr<EnemyBase>> m_pEnemyList;		// �G���G���X�g
	std::shared_ptr<BossEnemyBase> m_pBossEnemy;			// �{�X�G

	// ���f���n���h���e�[�u��
	std::map<EnemyType, int> m_modelHandleTable;			// �G���G
	std::map<BossEnemyType, int> m_bossModelHandleTable;	// �{�X�G

	// �E�F�[�u
	std::vector<WaveData> m_waveTable;	// �E�F�[�u�f�[�^
	int m_waveNow;		// ���݂̃E�F�[�u��
	bool m_isNextWave;	// ���̃E�F�[�u�Ɉڍs���邩�ǂ���
	bool m_isLoadWave;	// �E�F�[�u�f�[�^��ǂݍ��񂾂��ǂ���
};