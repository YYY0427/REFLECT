#pragma once
#include <DxLib.h>
#include <memory>
#include <deque>
#include "../Math/Vector3.h"
#include "../Util/Timer.h"
#include "../Editor/DataReaderFromUnity.h"

// �v���g�^�C�v�錾
class Model;
class Shield;
class Gauge;

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player
{
public:
	// �R���X�g���N�^
	Player(UnityGameObject data);

	// �f�X�g���N�^
	~Player();

	// �X�V
	void Update(float cameraHorizon);
	void GameOverUpdate();

	// �`��
	void Draw();

	// �v���C���[�̃_���[�W����
	void OnDamage();

	/// <summary>
	/// �v���C���[�������Ă��邩
	/// </summary>
	/// <returns>true : �����Ă���, false : ����ł���</returns>
	bool IsLive() const;

	// �ʒu���̎擾
	Vector3 GetPos() const;

	// �v���C���[�̓����蔻��̔��a�̎擾
	float GetCollsionRadius() const;

	// �v���C���[���f���̃n���h���̎擾
	int GetModelHandle() const;

	// �V�[���h�̃C���X�^���X�̎擾
	std::shared_ptr<Shield> GetShield() const;

	// ���߂�ꂽ�t���[���̐������ʒu����ۑ�����e�[�u���̎擾
	std::deque<Vector3> GetPosLogTable() const;

private:
	// �|�C���^
	std::shared_ptr<Model> m_pModel;
	std::shared_ptr<Shield> m_pShield;
	std::shared_ptr<Gauge> m_pHPbar;

	// ���߂�ꂽ�t���[���O�܂ňʒu����ۑ����Ă���e�[�u��
	std::deque<Vector3> m_posLogTable;

	// �ʒu���
	Vector3 m_pos;

	// ��]���
	Vector3 m_rot;

	// �g�嗦
	Vector3 m_scale;

	// �ړ��x�N�g��
	Vector3 m_moveVec;

	// �v���C���[�̈ړ����x
	float m_moveSpeed;

	// ��
	int m_hp;

	// ���X�e�B�b�N�����͂��ꂽ��
	bool m_isInputLeftStick;

	// �G�t�F�N�g
	int m_boostEffectHandle;		// �u�[�X�g�G�t�F�N�g�n���h��
	Vector3 m_boostEffectScale;		// �u�[�X�g�G�t�F�N�g�̊g�嗦
	float m_boostEffectSpeed;		// �u�[�X�g�G�t�F�N�g�̍Đ����x
	int m_playerDeadEffectHandle;	// �v���C���[���S�G�t�F�N�g�n���h��
	bool m_isPlayerDeadEffect;		// �v���C���[���S�G�t�F�N�g�̍Đ��t���O

	// �^�C�}�[
	int m_ultimateTimer;		// ���G���Ԃ̃^�C�}�[
	Timer<int> m_waitTimer;		// �ҋ@���Ԃ̃^�C�}�[
};