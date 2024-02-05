#include "MessageManager.h"
#include "StringUtil.h"
#include <fstream>
#include <sstream>

// �R���X�g���N�^
MessageManager::MessageManager()
{
}

// �f�X�g���N�^
MessageManager::~MessageManager()
{
}

// �B��̃C���X�^���X��Ԃ�
MessageManager& MessageManager::GetInstance()
{
	// �B��̎���
	static MessageManager instance;

	// �B��̎��ԎQ�Ƃ�Ԃ�
	return instance;
}

// �t�@�C�����當����̃f�[�^��ǂݎ���ăf�[�^�e�[�u���Ɋi�[
void MessageManager::LoadAndStoreStringFileData()
{
	// �t�@�C�����̓ǂݍ���(�ǂݍ��݂Ɏ��s������~�߂�)
	std::ifstream ifs("Data/Csv/Message.csv");
	assert(ifs);

	// csv�f�[�^��1�s���ǂݎ��
	bool isFirst = false;
	std::string line;
	while (getline(ifs, line))
	{
		// 1�s�ڂ͓ǂݍ��܂Ȃ�
		// 1�s�ڂɂ͍��ڂ������Ă��邽��
		if (!isFirst)
		{
			isFirst = true;
			continue;
		}

		// csv�f�[�^�P�s��','�ŕ����̕�����ɕϊ�
		std::vector<std::string> strvec = StringUtil::Split(line, ',');

		// csv�f�[�^����擾�����f�[�^����t�H���g�n���h���̍쐬���Ċi�[
		MessageData data;
		std::string font = strvec[static_cast<int>(MessageDataType::FONT)];		
		int size = std::stoi(strvec[static_cast<int>(MessageDataType::SIZE)]);
		int thick = std::stoi(strvec[static_cast<int>(MessageDataType::THICK)]);
		data.fontHandle = CreateFontToHandle(font.c_str(), size, thick, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

		// ������̊i�[
		data.string = strvec[static_cast<int>(MessageDataType::STRING)];	

		// �f�[�^�̊i�[
		m_messageDataTable[strvec[static_cast<int>(MessageDataType::ID)]] = data;
	}
}

// �I������
void MessageManager::End()
{
	// �t�H���g�f�[�^�̍폜
	for (auto& font : m_messageDataTable)
	{
		DeleteFontToHandle(font.second.fontHandle);
	}
}

// �t�@�C���ɓǂݍ��񂾕�����̕\��
void MessageManager::DrawString(std::string id, int x, int y, unsigned int color)
{
	// ���[�h���Ă��Ȃ��ꍇ�͎~�߂�
	assert(m_messageDataTable.find(id) != m_messageDataTable.end());	

	DrawStringToHandle(x, y, m_messageDataTable[id].string.c_str(), color, m_messageDataTable[id].fontHandle);
}

// �t�@�C���ɓǂݍ��񂾕�������w�肵�����W�𒆐S�Ƃ����ʒu�ɕ\��
void MessageManager::DrawStringCenter(std::string id, int x, int y, unsigned int color)
{
	// ���[�h���Ă��Ȃ��ꍇ�͎~�߂�
	assert(m_messageDataTable.find(id) != m_messageDataTable.end());	

	// �t�H���g�T�C�Y�A�A������̒������當����̉����̎擾
	std::string string = m_messageDataTable[id].string;
	int fontHandle = m_messageDataTable[id].fontHandle;
	int width = GetDrawStringWidthToHandle(string.c_str(), static_cast<int>(strlen(string.c_str())), fontHandle);
	int height = GetFontSizeToHandle(fontHandle);

	// �擾����������̉������當������������ʒu�ɕ\��
	DrawStringToHandle(x - width / 2, y - height / 2, string.c_str(), color, fontHandle);
}

// ���b�Z�[�W�̃f�[�^�̎擾
MessageData MessageManager::GetMessageData(std::string id)
{
	// ���[�h���Ă��Ȃ��ꍇ�͎~�߂�
	assert(m_messageDataTable.find(id) != m_messageDataTable.end());
	return m_messageDataTable[id];
}