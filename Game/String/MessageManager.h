#pragma once
#include <DxLib.h>
#include <string>
#include <vector>
#include <cassert>
#include <map>
#include "StringUtil.h"

// ������̃f�[�^
struct MessageData
{
	int fontHandle = -1;
	std::string string;
};

/// <summary>
/// ��������Ǘ�����N���X
/// </summary>
class MessageManager
{
public:
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~MessageManager();

	/// <summary>
	/// �B��̃C���X�^���X��Ԃ�
	/// </summary>
	/// <returns>�B��̎��Ԃ̎Q��</returns>
	static MessageManager& GetInstance();

	/// <summary>
	/// ���b�Z�[�W�t�@�C���̃f�[�^��ǂݍ���
	/// </summary>
	void LoadMessageFileData();

	/// <summary>
	/// �I������
	/// </summary>
	void End();

	/// <summary>
	/// �t�@�C���ɓǂݍ��񂾕�����̕\��
	/// </summary>
	/// <param name="id">�\���������������ID</param>
	/// <param name="x">Y���̍��W</param>
	/// <param name="y">Y���̍��W</param>
	/// <param name="color">�����̕`��F</param>
	void DrawString(const std::string& id, const int x, const int y, const unsigned int color);

	/// <summary>
	/// �t�@�C���ɓǂݍ��񂾕�������w�肵�����W�𒆐S�Ƃ����ʒu�ɕ\��
	/// </summary>
	/// <param name="id">�\���������������ID</param>
	/// <param name="x">�^�񒆂Ɏw�肵����X���̍��W</param>
	/// <param name="y">Y���̍��W</param>
	/// <param name="color">�����̕`��F</param>
	void DrawStringCenter(const std::string& id, const int x, const int y, const unsigned int color, const unsigned int edgeColor = 0x000000);

	/// <summary>
	/// �t�H���g�ɓǂݍ��񂾃f�[�^����쐬�����t�H���g�f�[�^���g����
	/// �w�肵�����W�𒆐S�Ƃ����ʒu�ɐ����̕\��
	/// </summary>
	/// <param name="id">�g�������t�H���g��ID</param>
	/// <param name="num">�\������������</param>
	/// <param name="x">�^�񒆂Ɏw�肵����X���̍��W</param>
	/// <param name="y">Y���̍��W</param>
	/// <param name="color">�����̕`��F</param>
	template<typename T>
	void DrawNumberCenter(const std::string& id, const T value, const int x, const int y, const unsigned const int color, const unsigned int edgeColor = 0x000000)
	{
		// ���[�h���Ă��Ȃ��ꍇ�͎~�߂�
		assert(m_messageDataTable.find(id) != m_messageDataTable.end());

		// �����𕶎���ɕϊ�
		std::string str = std::to_string(value);

		// �����̕`��
		StringUtil::DrawStringCenter(x, y, color, str, m_messageDataTable[id].fontHandle, edgeColor);
	}

	/// <summary>
	/// ���b�Z�[�W�̃f�[�^�̎擾
	/// </summary>
	/// <param name="id">���b�Z�[�WID</param>
	/// <returns>���b�Z�[�W�f�[�^</returns>
	const MessageData& GetMessageData(const std::string& id);

	/// <summary>
	/// ���b�Z�[�W�̕��̎擾
	/// </summary>
	/// <param name="id">���b�Z�[�WID</param>
	/// <returns>���b�Z�[�W�̕�</returns>
	int GetMessageWidth(const std::string& id);

	/// <summary>
	/// ���b�Z�[�W�̍����̎擾
	/// </summary>
	/// <param name="id">���b�Z�[�WID</param>
	/// <returns>���b�Z�[�W�̍���</returns>
	int GetMessageHeight(const std::string& id);

private:
	/// <summary>
	/// �R���X�g���N�^
	/// �V���O���g���̂���private
	/// </summary>
	MessageManager();

	/// <summary>
	/// �R�s�[�R���X�g���N�^�֎~
	/// </summary>
	/// <param name="">�R�s�[���̃C���X�^���X</param>
	MessageManager(const MessageManager&) = delete;			

	/// <summary>
	/// ����֎~
	/// </summary>
	/// <param name="">������̃C���X�^���X</param>
	void operator = (const MessageManager&) = delete;		

private:
	// ������f�[�^�̎��
	enum class MessageDataType
	{
		ID,
		STRING,
		FONT,
		SIZE,
		THICK
	};

private:
	// CSV�t�@�C���Ŏw�肵���������ID�Ƃ���������̃f�[�^�e�[�u��
	std::map<std::string, MessageData> m_messageDataTable;
};