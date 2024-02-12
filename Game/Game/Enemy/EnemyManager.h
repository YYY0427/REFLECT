#pragma once
#include <memory>
#include <list>
#include <vector>
#include <string>
#include <map>
#include "../../Math/Vector3.h"
#include "../Laser/LaserManager.h"
#include "../../StateMachine.h"

// �v���g�^�C�v�錾
class EnemyBase;
class Player;
class Warning;
class ScreenShaker;

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
	MATRIX,			// �}�g���b�N�X
	NONE,			// �Ȃ�
};

// �G�̍s���̃f�[�^
struct EnemyActionData
{
	Vector3 goalPos;		// �ړI�n
	int idleFrame;			// �ړI�n�ɓ��B���Ă��玟�̖ړI�n�Ɍ������܂ł̑ҋ@�t���[��
	bool isLaser;			// �ړI�n�ɓ��B�����烌�[�U�[������
	LaserType laserType;	// ���[�U�[�����ꍇ�A�ǂ̃��[�U�[������
	float laserChargeFrame;	// ���[�U�[�����ꍇ�A���[�U�[�����܂ł̃`���[�W�t���[��
	int laserIdleFrame;		// ���[�U�[�����ꍇ�A�ړI�n�ɓ��B���Ă��烌�[�U�[�����܂ł̑ҋ@�t���[��
	float laserSpeed;		// ���[�U�[�����ꍇ�A���[�U�[�̈ړ����x
	int laserFireFrame;		// ���[�U�[�����t���[�����˂������邩
	bool isPlayerFollowing;	// ���[�U�[�����ꍇ�A���[�U�[���v���C���[��Ǐ]���邩�ǂ���
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
};

/// <summary>
/// �G�̊Ǘ��N���X
/// </summary>
class EnemyManager
{
public:
	// �R���X�g���N�^
	EnemyManager(
		std::shared_ptr<Player> pPlayer, 
		std::shared_ptr<LaserManager> pLaserManager,
		std::shared_ptr<ScreenShaker> pScreenShaker);

	// �f�X�g���N�^
	~EnemyManager();

	// �X�V
	void Update();
	void UpdateNormal();
	void UpdateWarning();

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
	std::vector<EnemyData> LoadEnemyFileData(std::string filePath);	// �G
	std::vector<EnemyActionData> LoadEnemyActionFileData(std::string filePath);	// �G�̍s��

	// �Q�b�^�[
	const std::list<std::shared_ptr<EnemyBase>>& GetEnemyList() const;	// �G���G���X�g
	const std::shared_ptr<EnemyBase>& GetBossEnemy() const;				// �{�X�G
	bool IsDeadBoss() const;											// �{�X���|���ꂽ���ǂ���
	bool IsEndWave() const;												// ���݂̃E�F�[�u���I���������ǂ���

private:
	// �X�e�[�g
	enum class State
	{
		NORMAL,
		WARNING,
	};

private:
	// �X�e�[�g�}�V��
	StateMachine<State> m_stateMachine;	

	// �|�C���^
	std::shared_ptr<Player> m_pPlayer;						// �v���C���[
	std::shared_ptr<LaserManager> m_pLaserManager;			// ���[�U�[�Ǘ�
	std::list<std::shared_ptr<EnemyBase>> m_pEnemyList;		// �G���G���X�g
	std::shared_ptr<EnemyBase> m_pBossEnemy;				// �{�X�G
	std::shared_ptr<Warning> m_pWarning;					// �x��
	std::shared_ptr<ScreenShaker> m_pScreenShaker;			// ��ʗh��

	// �t���O
	bool m_isDeadBoss;	// �{�X���|���ꂽ���ǂ���
	bool m_isBoss;		// �{�X���o���������ǂ���
	bool m_isNextWave;	// ���̃E�F�[�u�Ɉڍs���邩�ǂ���
	bool m_isLoadWave;	// �E�F�[�u�f�[�^��ǂݍ��񂾂��ǂ���
	bool m_isStartWave;	// �E�F�[�u���J�n�������ǂ���

	// �E�F�[�u
	std::vector<WaveData> m_waveTable;	// �E�F�[�u�f�[�^
	BossEnemyType m_bossType;			// �{�X�̎��
	int m_waveNow;						// ���݂̃E�F�[�u��
};