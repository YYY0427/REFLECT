#pragma once
#include "UIBase.h"
#include "../Util/Range.h"
#include <array>

/// <summary>
/// �{�X�o�ꎞ�̌x��UI
/// </summary>
class Warning final : public UIBase
{
public:
	// �R���X�g���N�^
	Warning(int drawFrame);

	// �f�X�g���N�^
	~Warning();

	// �X�V
	void Update() override final;

	// �`��
	void Draw() override final;

	// �I�����Ă��邩�ǂ���
	bool IsEnd() const;

private:
	// ���ʗp
	enum class ID
	{
		CENTER,		// ����
		UP,			// ��
		DOWN,		// ��
	};

private:
	// UI�f�[�^
	struct Data
	{
		int imgHandle;
		Vector2 pos;
		int scrollDirection;
		int imgWidth;
		int imgHeight;
	};

private:
	// UI�f�[�^�̔z��
	std::array<Data, 3> m_uiDataTable;	

	// �I���t���O
	bool m_isEnd;	

	// �X�N���[��
	int m_scroll;

	// �`��t���[��
	int m_drawFrame;

	// �x�����̃A���t�@�l
	int m_stringAlphaParam;

	// �x���摜�̃A���t�@�l
	int m_imgAlphaParam;

	// �x���摜�̃A���t�@�l�̑����l
	int m_addImgAlphaParam;

	// �x���摜�̃A���t�@�l�͈̔�
	Range<int> m_ImgAlphaParamRange;
};