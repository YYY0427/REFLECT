#pragma once
#include <DxLib.h>
#include <memory>
#include <deque>
#include "../Math/Vector3.h"
#include "../Util/Timer.h"
#include <string>

// �v���g�^�C�v�錾
class Model;
class Shield;
class Gauge;
class StatusBack;

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player
{
public:
	// �R���X�g���N�^
	Player(std::string objectDataFileName);

	// �f�X�g���N�^
	~Player();

	// �X�V
	void UpdateStart(Vector3 cameraPos);
	void Update(float cameraHorizon);
	void UpdateGameClear();
	void UpdateGameOver();

	// �`��
	void Draw();
	void DrawShield();

	// �v���C���[�̃_���[�W����
	void OnDamage(int damage);

	// �V�[���h�����˂������̏���
	void OnReflect();

	// �v���C���[�������Ă��邩
	bool IsLive() const;

	// �ʒu���̎擾
	Vector3 GetPos() const;

	// �ړ��x�N�g���̎擾
	Vector3 GetMoveVec() const;

	// �v���C���[�̓����蔻��̔��a�̎擾
	float GetCollsionRadius() const;

	// �v���C���[���f���̃n���h���̎擾
	int GetModelHandle() const;

	// �X�^�[�g���o���������t���O�̎擾
	bool GetIsStartAnimation() const;

	// �V�[���h�̃C���X�^���X�̎擾
	std::shared_ptr<Shield> GetShield() const;

	// ���߂�ꂽ�t���[���̐������ʒu����ۑ�����e�[�u���̎擾
	std::deque<Vector3> GetPosLogTable() const;

	// �X���[�̒l�̐ݒ�
	void SetSlowValue(float slowValue);

private:
	// �|�C���^
	std::shared_ptr<Model> m_pModel;
	std::shared_ptr<Shield> m_pShield;
	std::shared_ptr<Gauge> m_pHPbar;
	std::shared_ptr<StatusBack> m_pBackUI;

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

	// �s�����x
	float m_opacity;

	// �v���C���[�̈ړ����x
	float m_moveSpeed;

	// ��
	int m_hp;

	// �X���[�̒l
	float m_slowValue;

	// �t���O
	bool m_isInputLeftStick;	// ���X�e�B�b�N�̓��̓t���O
	bool m_isReflect;			// ���˒���
	bool m_isStartAnimation;	// �X�^�[�g���o���������t���O

	// �G�t�F�N�g
	int m_windEffectHandle;			// ���G�t�F�N�g�̃n���h��
	int m_boostEffectHandle;		// �u�[�X�g�G�t�F�N�g�n���h��
	int m_damageEffectHandle;		// �_���[�W�G�t�F�N�g�n���h��
//	Vector3 m_boostEffectScale;		// �u�[�X�g�G�t�F�N�g�̊g�嗦
//	float m_boostEffectSpeed;		// �u�[�X�g�G�t�F�N�g�̍Đ����x
	int m_playerDeadEffectHandle;	// �v���C���[���S�G�t�F�N�g�n���h��
	bool m_isPlayerDeadEffect;		// �v���C���[���S�G�t�F�N�g�̍Đ��t���O

	// �^�C�}�[
	int m_ultimateTimer;		// ���G���Ԃ̃^�C�}�[
	Timer<int> m_waitTimer;		// �ҋ@���Ԃ̃^�C�}�[
};