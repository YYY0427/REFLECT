#include "LaserBase.h"
#include "../../Model.h"

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

// ���f���n���h���̎擾
int LaserBase::GetModelHandle() const
{
	return m_pModel->GetModelHandle();
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
