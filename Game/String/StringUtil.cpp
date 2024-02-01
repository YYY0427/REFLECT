#include "StringUtil.h"
#include <fstream>
#include <sstream>

namespace StringUtil
{
	// ������𕪊�����
	std::vector<std::string> StringUtil::Split(std::string& str, char delimiter)
	{
		// string��getline�Ŏg����f�[�^�ɕϊ�
		std::istringstream stream(str);

		// ��������������1�����i�[
		std::string field;

		// ������̕�����̔z��
		std::vector<std::string> result;

		// ��؂蕶�����Ȃ��Ȃ�܂Ń��[�v
		while (getline(stream, field, delimiter))
		{
			// ��������������1�����i�[����
			result.push_back(field);
		}
		return result;
	}

	// �w�肵�����W�𒆐S�ɕ������`�悷�� 
	void DrawStringCenter(int x, int y, unsigned int color, std::string str, int fontHandle)
	{
		// ������̕��ƒ������擾
		int width = -1;
		int height = -1;
		if (fontHandle == -1)
		{
			// �t�H���g�n���h�����w�肳��Ă��Ȃ��ꍇ
			width = GetDrawStringWidth(str.c_str(), static_cast<int>(strlen(str.c_str())));
			height = GetFontSize();

			// �G���[���N���Ă��Ȃ����`�F�b�N
			assert(width != -1 && "������̒����̎擾�Ɏ��s");
			assert(height != -1 && "������̍����̎擾�Ɏ��s");

			// �t�H���g�n���h�����w�肹���ɕ`��
			DrawString(x - width / 2, y - height / 2, str.c_str(), color);
		}
		else
		{
			// �t�H���g�n���h�����w�肳��Ă���ꍇ
			width = GetDrawStringWidthToHandle(str.c_str(), static_cast<int>(strlen(str.c_str())), fontHandle);
			height = GetFontSizeToHandle(fontHandle);

			// �G���[���N���Ă��Ȃ����`�F�b�N
			assert(width != -1 && "������̒����̎擾�Ɏ��s");
			assert(height != -1 && "������̍����̎擾�Ɏ��s");

			// �t�H���g�n���h�����w�肵�ĕ`��
			DrawStringToHandle(x - width / 2, y - height / 2, str.c_str(), color, fontHandle);
		}
	}
}