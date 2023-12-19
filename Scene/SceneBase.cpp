#include "SceneBase.h"
#include "../UI/Fade.h"
#include <cmath>

// �R���X�g���N�^
SceneBase::SceneBase(SceneManager& manager) :
	m_manager(manager),
	m_pFade(std::make_unique<Fade>())
{
}

// �f�X�g���N�^
SceneBase::~SceneBase()
{
}
