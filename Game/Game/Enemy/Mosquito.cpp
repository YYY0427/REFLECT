#include "Mosquito.h"
#include "../../Model.h"

// �R���X�g���N�^
Mosquito::Mosquito(int modelHandle)
{
	// ���f���̃C���X�^���X�̍쐬
	m_pModel = std::make_shared<Model>(modelHandle);
}

// �f�X�g���N�^
Mosquito::~Mosquito()
{
}

// �X�V
void Mosquito::Update()
{
	m_pModel->Update();
}

// �`��
void Mosquito::Draw()
{
	m_pModel->Draw();
}