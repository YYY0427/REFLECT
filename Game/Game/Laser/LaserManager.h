#pragma once
#include <memory>
#include <list>
#include <map>

// �v���g�^�C�v�錾
class LaserBase;
class Player;
class EnemyBase;

// ���[�U�[�̎��
enum class LaserType
{
	NORMAL,		// �ʏ탌�[�U�[
	REFLECT,	// ���˃��[�U�[
	NUM
};

// ���[�U�[�̃f�[�^
struct LaserData
{
	int key;		// ���[�U�[�̃L�[
	LaserType type;	// ���[�U�[�̎��
	std::shared_ptr<LaserBase> pLaser;	// ���[�U�[�̃|�C���^
};

/// <summary>
/// ���[�U�[�̊Ǘ��N���X
/// </summary>
class LaserManager
{
public:
	// �R���X�g���N�^
	LaserManager(std::shared_ptr<Player> pPlayer);

	// �f�X�g���N�^
	~LaserManager();

	// �X�V
	void Update();

	// �`��
	void Draw();

	/// <summary>
	/// ���[�U�[�̒ǉ�
	/// </summary>
	/// <param name="type">���[�U�[�̎��</param>
	/// <param name="pEnemy">���ˌ��̃|�C���^</param>
	/// <param name="laserChargeFrame">���[�U�[�̃`���[�W�t���[��</param>
	/// <param name="laserFireFrame">���[�U�[�̔��ˎ��ԃt���[��</param>
	/// <param name="laserSpeed">���[�U�[�̈ړ����x</param>
	/// <param name="isPlayerFollowing">�v���C���[��Ǐ]���邩</param>
	int AddLaser(LaserType type, std::shared_ptr<EnemyBase> pEnemy, int laserChargeFrame, int laserFireFrame, float laserSpeed, bool isPlayerFollowing);
	
	// ���[�U�[�̍폜
	void DeleteLaser(int key);

	// �Q�b�^�[
	const std::list<LaserData>& GetLaserList() const;	// ���[�U�[���X�g

private:
	// �|�C���^
	std::list<LaserData> m_pLaserList;	// ���[�U�[���X�g
	std::shared_ptr<Player> m_pPlayer;	// �v���C���[�̃|�C���^

	// ���f���n���h���e�[�u��
	std::map<LaserType, int> m_modelHandleTable;	
};

