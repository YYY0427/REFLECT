#pragma once
#include "../Math/Vector3.h"
#include "../Math/Vector2.h"
#include "../Util/Timer.h"
#include <deque>
#include <memory>
#include <string>
#include <map>

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
	Player(const std::string& objectDataFileName);

	// �f�X�g���N�^
	~Player();

	// �X�V
	void UpdateStart(const Vector3& cameraPos);
	void Update(float cameraHorizon);
	void UpdateGameClear();
	bool UpdateGameOver();

	// �`��
	void Draw();
	void DrawShield();

	/// <summary>
	/// �O���t�@�C������p�����[�^��ǂݍ���
	/// </summary>
	/// <param name="fileName">�t�@�C����</param>
	void LoadParameter(const std::string& fileName);

	/// <summary>
	/// �_���[�W���󂯂����̏���
	/// </summary>
	/// <param name="damage">�_���[�W��</param>
	void OnDamage(int damage);

	/// <summary>
	/// �V�[���h�����˂������̏���
	/// </summary>
	void OnReflect();

	// �Q�b�^�[
	int     GetModelHandle() const;			// ���f���n���h��
	float   GetCollisionRadius() const;		// �����蔻��̔��a
	bool    IsStartAnimation() const;		// �X�^�[�g���o���������t���O
	bool    IsLive() const;					// �����t���O
	const Vector3& GetPos() const;			// �ʒu
	const Vector3& GetMoveVec() const;		// �ړ��x�N�g��
	const std::shared_ptr<Shield>& GetShield() const;		// �V�[���h�̃|�C���^
	const std::deque<Vector3>&     GetPosLogTable() const;	// �ʒu���̃e�[�u��

	/// <summary>
	/// �p�����[�^�̎擾
	/// </summary>
	/// <param name="key">�L�[</param>
	/// <returns>�p�����[�^</returns>
	float GetParameter(const std::string& key) const;	

private:
	// �|�C���^
	std::shared_ptr<Model> m_pModel;		// ���f��
	std::shared_ptr<Shield> m_pShield;		// �V�[���h
	std::shared_ptr<Gauge> m_pHPbar;		// HP�o�[
	std::shared_ptr<StatusBack> m_pBackUI;	// �X�e�[�^�X�o�b�NUI

	// �p�����[�^�[
	Vector3 m_pos;				// �ʒu
	Vector3 m_rot;				// ��]
	Vector3 m_scale;			// �g�嗦
	Vector3 m_moveVec;			// �ړ��x�N�g��
	Vector2 m_playerSize;		// �v���C���[�̃T�C�Y
	float   m_moveSpeedXY;		// �ړ����x
	float   m_startMoveSpeedZ;	// �X�^�[�g���̑��x
	float   m_moveSpeedZ;		// Z�������̈ړ����x
	float   m_opacity;			// �����x
	float   m_collisionRadius;	// �����蔻��̔��a

	// HP
	int m_hp;
	int m_maxHp;

	// �t���O
	bool m_isInputLeftStick;	// ���X�e�B�b�N�̓��̓t���O
	bool m_isReflect;			// ���˒���
	bool m_isStartAnimation;	// �X�^�[�g���o���������t���O

	// �G�t�F�N�g
	int		m_boostEffectHandle;		// �u�[�X�g�G�t�F�N�g�n���h��
	Vector3 m_boostEffectScale;			// �u�[�X�g�G�t�F�N�g�̊g�嗦
	float	m_boostEffectSpeed;			// �u�[�X�g�G�t�F�N�g�̑��x
	int		m_damageEffectHandle;		// �_���[�W�G�t�F�N�g�n���h��
	int		m_playerDeadEffectHandle;	// �v���C���[���S�G�t�F�N�g�n���h��
	bool	m_isPlayerDeadEffect;		// �v���C���[���S�G�t�F�N�g�̍Đ��t���O

	// �^�C�}�[
	int		   m_waitFrame;					// �ҋ@�t���[��
	int		   m_ultimateTimer;				// ���G���Ԃ̃^�C�}�[
	Timer<int> m_dieEffectIntervalTimer;	// ���S�G�t�F�N�g�̃C���^�[�o���^�C�}�[
	Timer<int> m_waitTimer;					// �ҋ@���Ԃ̃^�C�}�[

	// �O���t�@�C������ǂݍ��񂾃p�����[�^
	std::map<std::string, float> m_parameterTable;

	// ���߂�ꂽ�t���[���O�܂ňʒu����ۑ����Ă���e�[�u��
	std::deque<Vector3> m_posLogTable;
};