#pragma once
#include <string>
#include <DxLib.h>
#include <list>

namespace
{
	// �`�悷��X���W
	constexpr int draw_width = 0;

	// �`�悷��X�^�[�gY���W
	constexpr int draw_start_height = 150;

	// �`�悷��Y���W�̊Ԋu
	constexpr int draw_height_interval = 20;

	// �`�悷�镶���̐F
	const unsigned int draw_font_color = 0xffffff;

	// �t�H���g
	const std::string font = "�l�r �S�V�b�N";

	// �����T�C�Y
	constexpr int font_size = 20;

	// �����̑���
	constexpr int font_thickness = 9;

	// �����̔w�i�̐F
	const unsigned int draw_back_color = 0xffffff;

	// �����̔w�i�̓����x
	constexpr int draw_back_alpha = 127;
}

/// <summary>
/// �f�o�b�O�p�̊֐����܂Ƃ߂��N���X
/// </summary>
class DebugText
{
public:
	/// <summary>
	/// ������
	/// </summary>
	static void Init();

	/// <summary>
	/// �I������
	/// </summary>
	static void End();

	/// <summary>
	/// ���O�̃N���A
	/// </summary>
	static void Clear();

	/// <summary>
	/// ���O�̕`��
	/// </summary>
	static void Draw();

	/// <summary>
	/// ���O�̒ǉ�(�����̂�)
	/// </summary>
	/// <param name="string">�o�͂��镶����</param>
	static void AddLog(const std::string& string);

	/// <summary>
	/// ���O�̒ǉ�(�����Ɛ���)
	/// </summary>
	/// <typeparam name="T">�ϐ��̌^</typeparam>
	/// <typeparam name="N">�ϐ��̐�</typeparam>
	/// <param name="string">������</param>
	template <typename T, size_t N>
	static void AddLog(const std::string& string, const T(&array)[N])
	{
#ifdef _DEBUG
		// ��������쐬
		std::string str = string;

		// �z��̒��g�𕶎���ɕϊ�
		for (int i = 0; i < N; i++)
		{
			// 1�ڂ̗v�f�� : �ŋ�؂�
			if (i == 0)
			{
				str += " : " + std::to_string(array[i]);
			}
			// 2�ڈȍ~�̗v�f�� , �ŋ�؂�
			else
			{
				str += ", " + std::to_string(array[i]);
			}
		}
		// ���O���i�[
		m_logList.push_front(str);
#endif
	}

private:
	// ���O�̃��X�g
	static std::list<std::string> m_logList;

	// ���O�̏o�͉�
	static int m_logCount;

	// �t�H���g�n���h��
	static int m_fontHandle;
};