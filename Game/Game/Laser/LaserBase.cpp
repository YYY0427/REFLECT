#include "LaserBase.h"
#include "../../Model.h"
#include "../../Effect/Effekseer3DEffectManager.h"

// �R���X�g���N�^
LaserBase::LaserBase() :
	m_isEnabled(true),
	m_isReflect(false),
	m_speed(0.0f),
	m_opacity(1.0f)
{
}

// �f�X�g���N�^
LaserBase::~LaserBase()
{
}

// ����
void LaserBase::Delete()
{
	m_isEnabled = false;
}

// ���f���n���h���̎擾
int LaserBase::GetModelHandle() const
{
	return m_pModel->GetModelHandle();
}

// �ʒu���̎擾
Vector3 LaserBase::GetPos() const
{
	return m_pos;
}

// �����x�N�g���̎擾
Vector3 LaserBase::GetDirection() const
{
	return Vector3();
}

// ���݃t���O�̎擾
bool LaserBase::IsEnabled() const
{
	return m_isEnabled;
}

// ���˃t���O�̎擾
bool LaserBase::IsReflect() const
{
	return m_isReflect;
}
