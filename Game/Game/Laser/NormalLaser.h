#pragma once
#include "LaserBase.h"
#include "../../StateMachine.h"
#include "../../Util/Timer.h"
#include "../../Math/Matrix.h"

// �v���g�^�C�v�錾
class EnemyBase;
class Player;

/// <summary>
/// �ʏ탌�[�U�[�N���X
/// </summary>
class NormalLaser final : public LaserBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="modelHandle">���f���n���h��</param>
	/// <param name="pEnemy">���ˌ��̓G�̃|�C���^</param>
	/// <param name="pPlayer">�v���C���[�̃|�C���^</param>
	/// <param name="laserFireFrame">���[�U�[�̔��ˎ��ԃt���[��</param>
	/// <param name="laserSpeed">���[�U�[�̈ړ����x</param>
	/// <param name="isPlayerFollowing">�v���C���[��Ǐ]���邩</param>
	NormalLaser(int modelHandle, std::shared_ptr<EnemyBase> pEnemy, std::shared_ptr<Player> pPlayer, int laserFireFrame, float laserSpeed, bool isPlayerFollowing);

	// �f�X�g���N�^
	~NormalLaser();

	// �X�V
	void Update() override final;
	void UpdateCharge();
	void UpdateNormalFire();
	void UpdateFirePlayerFollowing();

	// �`��
	void Draw() override final;

private:
	// ���
	enum class State
	{
		CHARGE,					// �`���[�W
		FIRE_PLYER_FOLLOWING,	// �v���C���[��Ǐ]���Ĕ���
		NORMAL_FIRE,			// �ʏ픭��
		NUM
	};

private:
	// �|�C���^
	std::shared_ptr<EnemyBase> m_pEnemy;	// ���ˌ��̃|�C���^
	std::shared_ptr<Player> m_pPlayer;		// �v���C���[�̃|�C���^

	// ��ԃ}�V��
	StateMachine<State> m_stateMachine;	

	// ��]�s��
	Matrix m_rotMtx;	

	// ���[�U�[�̃G�t�F�N�g�̃n���h��
	int m_laserEffectHandle;

	// ���[�U�[�̔��ˎ��ԃt���[��
	int m_laserFireFrame;	

	// �^�C�}�[
	Timer<int> m_chargeEffectTimer;	// �`���[�W�G�t�F�N�g�̃^�C�}�[

	// �v���C���[��Ǐ]���邩
	bool m_isPlayerFollowing;	
};