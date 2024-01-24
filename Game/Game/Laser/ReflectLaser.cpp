#include "ReflectLaser.h"
#include "../../Math/Matrix.h"
#include "../../Effect/Effekseer3DEffectManager.h"
#include "../../Model.h"
#include "../Shield.h"

namespace
{
	// ��������
	const Vector3 init_model_direction = { 1.0f, 0.0f, 0.0f };			// ���f��
	const Vector3 init_laser_effect_direction = { 0.0f, 0.0f, -1.0f };	// �G�t�F�N�g

	// �g�嗦
	const Vector3 model_scale = { 1.0f, 0.1f, 0.1f };		// ���f��
	const Vector3 effect_scale = { 40.0f, 40.0f, 40.0f };	// �G�t�F�N�g
}

// �R���X�g���N�^
ReflectLaser::ReflectLaser(int modelHandle, std::shared_ptr<Shield> pShield, std::shared_ptr<LaserBase> pLaser)
{
	// ������
	m_pShield = pShield;
	m_pLaser = pLaser;
	m_isReflect = true;
	m_isEnabled = true;

	// �ʒu���V�[���h�ɍ��킹��
	m_pos = m_pShield->GetPos();

	// ���˃x�N�g�����쐬
	m_vec = Vector3::Reflect(m_pLaser->GetDirection(), Vector3::FromDxLibVector3(m_pShield->GetVertex()[0].norm));

	// �w�肵���x�N�g�������Ɍ�����s��̍쐬
	Matrix rotEffectMtx = Matrix::GetRotationMatrix(init_laser_effect_direction, m_vec);
	Matrix rotMtx = Matrix::GetRotationMatrix(init_model_direction, -m_vec);

	// ���[�U�[�G�t�F�N�g�̍Đ�
	Effekseer3DEffectManager::GetInstance().PlayEffectLoopAndFollow(
		m_laserEffectHandle, EffectID::refrect_laser, &m_pos, effect_scale, 1.0f, rotEffectMtx.ToEulerAngle());

	// ���f���̐ݒ�
	m_pModel = std::make_shared<Model>(modelHandle);	// �C���X�^���X����
	m_pModel->SetUseCollision(true);					// �����蔻��ݒ�
	m_pModel->SetScale(model_scale);					// �g�嗦
	m_pModel->SetRotMtx(rotMtx);						// ��]�s��
	m_pModel->SetPos(m_pos);							// �ʒu
	m_pModel->Update();									// �����蔻��̍X�V
}

// �f�X�g���N�^
ReflectLaser::~ReflectLaser()
{
	// �G�t�F�N�g�̍폜
	Effekseer3DEffectManager::GetInstance().DeleteEffect(m_laserEffectHandle);
}

// �X�V
void ReflectLaser::Update()
{
	// ���ˌ��̃��[�U�[���V�[���h�ɔ��˂��Ă��Ȃ����������
	if (!m_pLaser->IsReflect() || !m_pLaser->IsEnabled())
	{
		m_isEnabled = false;
		return;
	}

	// �ʒu���V�[���h�ɍ��킹��
	m_pos = m_pShield->GetPos();
	m_vec = Vector3::Reflect(m_pLaser->GetDirection(), Vector3::FromDxLibVector3(m_pShield->GetVertex()[0].norm));

	// �w�肵���x�N�g�������Ɍ�����s��̍쐬
	Matrix rotEffectMtx = Matrix::GetRotationMatrix(init_laser_effect_direction, m_vec);
	Matrix rotMtx = Matrix::GetRotationMatrix(init_model_direction, -m_vec);

	// �G�t�F�N�g�̉�]����ݒ�
	Effekseer3DEffectManager::GetInstance().SetEffectRot(m_laserEffectHandle, rotEffectMtx.ToEulerAngle());

	// ���f���̐ݒ�
	m_pModel->SetRotMtx(rotMtx);						// ��]�s��
	m_pModel->SetPos(m_pos);							// �ʒu
	m_pModel->Update();									// �����蔻��̍X�V
}

// �`��
void ReflectLaser::Draw()
{
#ifdef _DEBUG
	// ���f���̕`��
	m_pModel->Draw();
#endif 
}