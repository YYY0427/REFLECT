#pragma once
#include "../Util/Range.h"

/// <summary>
/// �t�F�[�h
/// </summary>
class Fade
{
public:
	// �R���X�g���N�^
	Fade();

	// �f�X�g���N�^
	~Fade();

	// �X�V
	void Update();

	// �ʏ�t�F�[�h�̕`��
	void DrawFade(bool isDraw);

	// ���U�C�N�t�F�[�h�̕`��
	void DrawGaussFade(bool isDraw);

	/// <summary>
	/// �t�F�[�h�C���J�n
	/// </summary>
	/// <param name="fadeBrightUpperLimitValue">�t�F�[�h�C���̏���l 0~255</param>
	/// <param name="fadeSpeed">�t�F�[�h�̑��x</param>
	void StartFadeIn(int fadeBrightUpperLimitValue, int fadeSpeed = 8);

	/// <summary>
	/// �t�F�[�h�A�E�g�J�n
	/// </summary>
	/// <param name="fadeBrightUpperLimitValue">�t�F�[�h�A�E�g�̏���l 0~255</param>
	/// <param name="fadeSpeed">�t�F�[�h�̑��x</param>
	void StartFadeOut(int fadeBrightUpperLimitValue, int fadeSpeed = 8);

	/// <summary>
	/// �t�F�[�h�C�������ǂ���
	/// </summary>
	/// <returns>true : �t�F�[�h�C����, false : �t�F�[�h�C�����Ă��Ȃ�</returns>
	bool IsFadingIn() const;

	/// <summary>
	/// �t�F�[�h�A�E�g�����ǂ���
	/// </summary>
	/// <returns>true : �t�F�[�h�A�E�g��, false : �t�F�[�h�A�E�g���Ă��Ȃ�</returns>
	bool IsFadingOut() const;

	/// <summary>
	/// �t�F�[�h�����ǂ���
	/// </summary>
	/// <returns>true : �t�F�[�h��, false : �t�F�[�h���ĂȂ�</returns>
	bool IsFading() const;

	// �t�F�[�h�A�E�g���s��ꂽ��ŏI���������ǂ���
	bool IsFadeOutEnd() const;

	// �t�F�[�h�̖��邳�̎擾
	int GetFadeBright() const;

	/// <summary>
	/// �t�F�[�h�̖��邳�̐ݒ�
	/// </summary>
	/// <param name="fadeBright">�ݒ肵�������邳�̒l</param>
	void SetFadeBright(int fadeBright);

private:
	// �t�F�[�h�̖��邳�͈̔�
	Range<int> m_fadeBrightRange;

	// �t�F�[�h�̐F
	unsigned int m_fadeColor;

	// �t�F�[�h�̖��邳
	// 0(�t�F�[�h���Ă��Ȃ�)�`255(�^����)
	int m_fadeBright;

	// �t�F�[�h���鑬�x
	// �����̏ꍇ�t�F�[�h�A�E�g�A�����̏ꍇ�t�F�[�h�C��
	int m_fadeSpeed;

	// �t�F�[�h�A�E�g�������Ȃ������ǂ���
	bool m_isFadeOut;

	// ���U�C�N�t�F�[�h�p�̕`��O���t�B�b�N
	int m_gaussScreen;
};