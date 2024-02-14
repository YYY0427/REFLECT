#pragma once
#include <string>
#include <vector>
#include <memory>
#include "UIBase.h"
#include "../Math/Vector2.h"

/// <summary>
/// UI�̊Ǘ��N���X
/// </summary>
class UIManager
{
public:
	// �f�X�g���N�^
	~UIManager();

	// UI�̍X�V
	void Update();

	// UI�̕`��
	void Draw();

	/// <summary>
	/// UIManager�̗B��̃C���X�^���X��Ԃ�
	/// </summary>
	/// <returns>�B��̎��Ԃ̎Q��</returns>
	static UIManager& GetInstance();

	/// <summary>
	/// UI�̒ǉ�
	/// </summary>
	/// <param name="key">�L�[</param>
	/// <param name="ui">UI�̃|�C���^</param>
	/// <param name="drawOrder">�`�揇</param>
	/// <param name="storeVec">UI���i�[����x�N�g��</param>
	void AddUI(std::string key, std::shared_ptr<UIBase> ui, int drawOrder, Vector2 storeVec = {});

	// UI�̍폜
	void DeleteUI(std::string key);

	// ���ׂĂ�UI�̍폜
	void DeleteAllUI();

	// UI�̊i�[
	void Store();

private:
	// �R���X�g���N�^
	// �V���O���g���p�^�[���Ȃ̂�private
	UIManager();

	// �R�s�[��������֎~
	UIManager(const UIManager&) = delete;			// �R�s�[�R���X�g���N�^�֎~
	void operator = (const UIManager&) = delete;	// ����֎~

private:
	// UI�̃f�[�^
	struct UIData
	{
		std::string key;			// �L�[
		std::shared_ptr<UIBase> ui; // UI�̃|�C���^
		int drawOrder;				// �`�揇
		Vector2 storeVec;			// UI���i�[����x�N�g��
	};

private:
	// UI�̃e�[�u��
	std::vector<UIData> m_uiTable;
};