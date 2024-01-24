#include "ScreenShaker.h"
#include "../Game/Camera.h"
#include "../Application.h"
#include <DxLib.h>
#include <cassert>

// �R���X�g���N�^
ScreenShaker::ScreenShaker(std::shared_ptr<Camera> pCamera) :
	m_pCamera(pCamera),
	m_quakeSize(0, 0),
	m_isPreDraw(false),
	m_screenHandle(-1)
{
	// ������
	m_quakeTimer.SetTime(0);

	// ��ʂ̃T�C�Y���擾
	auto& screenSize = Application::GetInstance().GetWindowSize();

	// ��ʂ̃T�C�Y�ŉ�ʂ��쐬
	m_screenHandle = MakeScreen(screenSize.width, screenSize.height, true);
}

// �f�X�g���N�^
ScreenShaker::~ScreenShaker()
{
}

// �X�V
void ScreenShaker::Update()
{
	// �h��̏���
	if (m_quakeTimer.GetTime() > 0)
	{
		// ��ʂ�h�炷
		m_quakeSize.x *= -0.95f;
		m_quakeSize.y *= -0.95f;
		m_quakeTimer.Update(-1);
	}
	else
	{
		m_quakeSize.x = 0.0f;
		m_quakeSize.y = 0.0f;
	}
}

// �`��O
void ScreenShaker::PreDraw()
{
	// �t���O�𗧂Ă�
	m_isPreDraw = true;

	// �`����؂�ւ�
	SetDrawScreen(m_screenHandle);

	// �`����؂�ւ�����J���������Z�b�g�����̂ōĐݒ�
	m_pCamera->SetCamera();
}

// �`��
void ScreenShaker::Draw()
{
	// PreDraw()���Ă�ł��Ȃ�������G���[
	if (!m_isPreDraw)
	{
		assert(!"ScreenShaker::PreDraw()���Ă�ł�������");
	}

	// �`���𗠉�ʂɖ߂�
	SetDrawScreen(DX_SCREEN_BACK);

	// �`����؂�ւ�����J���������Z�b�g�����̂ōĐݒ�
	m_pCamera->SetCamera();

	// ������
	m_isPreDraw = false;

	// ��ʂ̗h��𔽉f���ĕ`��
	DrawGraph(static_cast<int>(m_quakeSize.x), static_cast<int>(m_quakeSize.y), m_screenHandle, false);
}

// ��ʂ�h�炷
void ScreenShaker::StartShake(Vector2 quakeSize, int frame)
{
	// ���łɗh��Ă����牽�����Ȃ�
	if (m_quakeTimer.GetTime() > 0) return;

	// �h��̑傫����ݒ�
	m_quakeSize = quakeSize;

	// �^�C�}�[��ݒ�
	m_quakeTimer.SetTime(frame);
}