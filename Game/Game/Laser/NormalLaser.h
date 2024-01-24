#pragma once
#include "LaserBase.h"
#include "../../StateMachine.h"
#include "../../Util/Timer.h"
#include "../../Math/Matrix.h"
#include "../../Math/Vector2.h"
#include <vector>

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
	/// <param name="laserChargeFrame">���[�U�[�̃`���[�W�t���[��</param>
	/// <param name="laserFireFrame">���[�U�[�̔��ˎ��ԃt���[��</param>
	/// <param name="laserSpeed">���[�U�[�̈ړ����x</param>
	/// <param name="isPlayerFollowing">�v���C���[��Ǐ]���邩</param>
	NormalLaser(int modelHandle, std::shared_ptr<EnemyBase> pEnemy, std::shared_ptr<Player> pPlayer, int laserChargeFrame, int laserFireFrame, float laserSpeed, bool isPlayerFollowing);

	// �f�X�g���N�^
	~NormalLaser();

	// �X�V
	void Update() override final;

	// �`��
	void Draw() override final;

	// ���[�U�[���~�߂�
	void Stop(Vector3 pos) override final;

	// ���˂��ꂽ��Ԃ��猳�ɖ߂�
	void UndoReflect() override final;

	// �����x�N�g���̃Q�b�^�[
	Vector3 GetDirection() const override final;

private:
	// �X�V
	void UpdateCharge();				// �`���[�W
	void UpdateNormalFire();			// �ʏ픭��
	void UpdateFirePlayerFollowing();	// �v���C���[��Ǐ]���Ĕ���

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

	// ��������
	Vector3 m_directionPos;	// �������W
	Vector3 m_directionVec; // �x�N�g��

	// ��ԃ}�V��
	StateMachine<State> m_stateMachine;	

	// ��]�s��
	Matrix m_rotMtx;	

	// ���[�U�[�̃G�t�F�N�g�̃n���h��
	int m_laserEffectHandle;

	// �t���[��
	int m_laserFireFrame;		// ���[�U�[�̔��˃t���[��
	int m_chargeEffectFrame;	// �G�t�F�N�g�`���[�W�t���[��

	// �v���C���[��Ǐ]���邩
	bool m_isPlayerFollowing;

	// �ʏ픭�ˎ�
	int m_normalFireMovePointIndex;		// �ړ��|�C���g�C���f�b�N�X
	Vector3 m_normalFireGoalPos;		// �ړ��|�C���g�̍��W
	std::vector<Vector2> m_normalFireMovePointList;	// �ړ��|�C���g�̍��W�̃��X�g
};