#include "ImageUI.h"
#include "../Util/DrawFunctions.h"
#include <DxLib.h>

// �R���X�g���N�^
ImageUI::ImageUI(std::string filePath) :
	m_rot(0.0f),
	m_scale(1.0f, 1.0f),
	m_alpha(1.0f),
	m_center(0.0f, 0.0f)
{
	// �摜�̓ǂݍ���
	m_imgHandle = my::MyLoadGraph(filePath.c_str());
}

// �f�X�g���N�^
ImageUI::~ImageUI()
{
	// �摜�̍폜
	DeleteGraph(m_imgHandle);
}

// �`��
void ImageUI::Draw()
{
	// �A���t�@�u�����h�̐ݒ�
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);

	// �摜�̕`��
	DrawRotaGraph3(
		m_pos.x, m_pos.y,		// �`�悷����W
		m_center.x, m_center.y, // �摜�̒��S���W
		m_scale.x, m_scale.y,	// �g�嗦
		m_rot,					// ��]�p�x
		m_imgHandle,			// �摜�n���h��
		true);

	// �`��ݒ�����ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
