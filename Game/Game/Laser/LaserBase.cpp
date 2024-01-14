#include "LaserBase.h"

// �R���X�g���N�^
LaserBase::LaserBase() :
	m_isEnabled(true),
	m_isReflect(false)
{
}

// �f�X�g���N�^
LaserBase::~LaserBase()
{
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
