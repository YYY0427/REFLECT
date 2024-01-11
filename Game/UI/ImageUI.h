#pragma once
#include "UIBase.h"
#include "../Math/Vector2.h"
#include <string>

/// <summary>
/// UI�̉摜�N���X
/// </summary>
class ImageUI : public UIBase
{
public:
	// �R���X�g���N�^
	ImageUI(std::string filePath);

	// �f�X�g���N�^
	~ImageUI();

	// �X�V
	void Update() override final {};

	// �`��
	void Draw() override final;

	// �Z�b�^�[
	void SetPos(Vector2 pos);		// �ʒu
	void SetRot(float rot);			// ��]
	void SetCenter(Vector2 center);	// ���S���W
	void SetScale(Vector2 scale);	// �g�嗦
	void SetAlpha(float alpha);		// �����x

	// �Q�b�^�[
	Vector2 GetPos() const;		// �ʒu
	float GetRot() const;		// ��]
	Vector2 GetCenter() const;	// ���S���W
	Vector2 GetScale() const;	// �g�嗦
	float GetAlpha() const;		// �����x

private:
	// �摜�n���h��
	int m_imgHandle;

	// �摜�̉�]��
	float m_rot;

	// �摜�̒��S���W
	Vector2 m_center;

	// �摜�̊g�嗦
	Vector2 m_scale;

	// �摜�̓����x
	float m_alpha;
};