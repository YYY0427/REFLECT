#pragma once
#include <DxLib.h>
#include <string>
#include <array>
#include "Math/Vector3.h"

/// <summary>
/// 3D�摜�N���X
/// </summary>
class Image3D
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="filePath">�摜�̃t�@�C���p�X</param>
	Image3D(std::string filePath);

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="imgHandle">�摜�n���h��</param>
	Image3D(int imgHandle);

	// �f�X�g���N�^
	~Image3D();

	// �X�V
	void Update();

	// �`��
	void Draw();

	// �摜�n���h���̎擾
	int GetImageHandle() const;

	// �摜�̒��_���̎擾
	std::array<VERTEX3D, 6> GetVertex() const;

	// �ʒu�̐ݒ�
	void SetPos(Vector3 pos);

	// ��]�̐ݒ�
	void SetRot(Vector3 rot);

	// �摜�̉����̐ݒ�
	void SetImgWidth(float width);

	// �摜�̏c���̐ݒ�
	void SetImgHeight(float height);

	// �摜�̓����x�̐ݒ�
	void SetAlpha(int alpha);

	// �摜�̉����Ɨ����̊g�嗦�����̉摜�̃T�C�Y�ɖ߂�
	void SetImgDafualtScale();

private:
	// �摜�̒��_
	std::array<VERTEX3D, 6> m_vertex;

	// �摜�̈ʒu
	Vector3 m_pos;

	// �摜�̉�]
	Vector3 m_rot;

	// �摜�̓����x
	int m_alpha;

	// �摜�̃n���h��
	int m_imgHandle;

	// �摜�̉���
	float m_imgWidth;

	// �摜�̏c��
	float m_imgHeight;
};