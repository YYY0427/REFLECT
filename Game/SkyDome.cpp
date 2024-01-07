#include "SkyDome.h"
#include "../Model.h"
#include <string>

namespace
{
	// ���f���̃t�@�C���p�X
	const std::string model_file_path = "Data/Model/Star.mv1";

	// ���f���̊g�嗦
	const Vector3 model_scale = { 80, 80, 80 };
}

// �R���X�g���N�^
SkyDome::SkyDome(Vector3 playerPos)
{
	m_pModel = std::make_unique<Model>(model_file_path);

	// ���f���̈ʒu��ݒ�
	m_pModel->SetPos({ 0, 0, 0 });

	// ���f���̉�]��ݒ�
	m_pModel->SetRot({ 0, 0, 0 });

	// ���f���̊g�嗦��ݒ�
	m_pModel->SetScale(model_scale);
}

// �f�X�g���N�^
SkyDome::~SkyDome()
{
}

// �X�V
void SkyDome::Update(Vector3 playerPos)
{
	// ���f���̈ʒu���v���C���[�̈ʒu�ɍ��킹��
	m_pModel->SetPos(playerPos);
}

// �`��
void SkyDome::Draw()
{
	m_pModel->Draw();
}