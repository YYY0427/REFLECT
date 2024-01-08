#pragma once
#include "UIBase.h"
#include "../Math/Vector2.h"
#include "../Util/Timer.h"
#include <string>

/// <summary>
/// �Q�[�W�N���X
/// HP,MP�Ȃǂ̃Q�[�W�Ȃ�
/// </summary>
class Gauge final : public UIBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="gaugeImgFilePath">�Q�[�W�̃t�@�C���p�X</param>
	/// <param name="gaugeBackImgFilePath">�Q�[�W�w�i�̃t�@�C���p�X</param>
	/// <param name="gaugeFrameImgFilePath">�Q�[�W�t���[���̃t�@�C���p�X</param>
	/// <param name="maxValue">�Q�[�W�̍ő�l</param>
	/// <param name="pos">�Q�[�W�̈ʒu</param>
	/// <param name="dimensions">�Q�[�W�̃T�C�Y</param>
	/// <param name="isBurst">�o�[�X�g���o���s�����ǂ���</param>
	/// <param name="addGaugeSpeed">�o�[�X�g���o�̃Q�[�W�̑����鑬�x</param>
	/// <param name="isDelayedDamage">�Q�[�W�̃f�B���C���o���s�����ǂ���</param>
	/// <param name="aimGaugeSpeed">�f�B���C���o�̌��鑬�x</param>
	Gauge(
		const std::string gaugeImgFilePath, 
		const std::string gaugeBackImgFilePath,
		const std::string gaugeFrameImgFilePath,
		float maxValue,
		Vector2 pos,
		Vector2 dimensions,
		bool isGaugeBurst,
		float addGaugeSpeed,
		bool isDelayed,
		float aimGaugeSpeed);

	// �f�X�g���N�^
	~Gauge();

	// �X�V
	void Update() override final;

	// �`��
	void Draw() override final;

	// �_���[�W���󂯂����̏���
	void SetValue(float afterHp);

private:
	// �ʏ펞�̍X�V
	void NormalUpdate();	

	// �o�[�X�g���o���̍X�V
	void BurstUpdate();

private:
	// �Q�[�W�̍X�V�֐�
	void(Gauge::*m_updateFunc)();

	// �摜�n���h��
	int m_gaugeImgH;		// �Q�[�W
	int m_gaugeBackImgH;	// �Q�[�W�̔w�i
	int m_gaugeFrameImgH;	// �Q�[�W�̘g

	// �Q�[�W�̒l
	float m_currentValue;	// ���݂̒l
	float m_backValue;		// �w�i�̒l
	float m_aimValue;		// �ڕW�̒l
	float m_maxValue;		// �ő�l

	Vector2 m_pos;			// �Q�[�W�̈ʒu
	Vector2 m_dimensions;	// �Q�[�W�̑傫��

	float m_addGaugeSpeed;	// �Q�[�W�������鑬�x
	float m_aimGaugeSpeed;	// �Q�[�W�����鑬�x

	// �t���O
	bool isDelayed;	// �_���[�W���󂯂Ă���Q�[�W������܂ł̎��Ԃ����邩

	// �_���[�W���󂯂Ă���̃t���[����
	Timer<int> m_damageFrameCount;
};

