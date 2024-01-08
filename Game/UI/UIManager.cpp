#include "UIManager.h"
#include "UIBase.h"
#include <algorithm>

// �R���X�g���N�^
UIManager::UIManager()
{
}

// �f�X�g���N�^
UIManager::~UIManager()
{
}

// �X�V
void UIManager::Update()
{
	// �X�V
	for (auto& ui : m_uiTable)
	{
		ui.ui->Update();
	}
}

// �`��
void UIManager::Draw()
{
	// �`��
	for (auto& ui : m_uiTable)
	{
		ui.ui->Draw();
	}
}

// �C���X�^���X�̎擾
UIManager& UIManager::GetInstance()
{
	// �B��̎���
	static UIManager instance;

	// �B��̎��ԎQ�Ƃ�Ԃ�
	return instance;
}

// UI�̒ǉ�
void UIManager::AddUI(std::string key, std::shared_ptr<UIBase> ui, int drawOrder, Vector2 storeVec)
{
	// ���łɃL�[���o�^����Ă���ꍇ�͒ǉ����Ȃ�
	for (auto& uiT : m_uiTable)
	{
		if(uiT.ui == ui) return;
	}

	// �f�[�^�̍쐬
	UIData data;
	data.drawOrder = drawOrder;	// �`�揇��ݒ�
	data.key = key;				// �L�[��ݒ�
	data.ui = ui;				// UI��ݒ�
	data.storeVec = storeVec;	// UI���i�[����x�N�g��

	// �f�[�^��ǉ�
	m_uiTable.push_back(data);	

	// �`�揇�Ƀ\�[�g
	std::sort(m_uiTable.begin(), m_uiTable.end(),
		[](const UIData& a, const UIData& b) { return a.drawOrder < b.drawOrder; });
}

// UI�̊i�[
void UIManager::Store()
{
	for (auto& ui : m_uiTable)
	{
		ui.ui->Store(ui.storeVec);
	}
}