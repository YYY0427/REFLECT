#pragma once
#include <vector>
#include <string>
#include <cassert>
#include <DxLib.h>

/// <summary>
/// �����񃆁[�e�B���e�B
/// </summary>
namespace StringUtil
{
	/// <summary>
	/// ������𕪊�����
	/// </summary>
	/// <param name="str">�������镶����</param>
	/// <param name="delim">��؂蕶��</param>
	/// <returns>�������ꂽ������̔z��</returns>
	std::vector<std::string> Split(std::string& str, char delimiter);

	/// <summary>
	/// �w�肵�����W�𒆐S�ɕ������`�悷��
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="x">X��</param>
	/// <param name="y">Y��</param>
	/// <param name="color">�F</param>
	/// <param name="str">������</param>
	/// <param name="fontHandle">�t�H���g�n���h��</param>
	void DrawStringCenter(int x, int y, unsigned int color, std::string str, int fontHandle, unsigned int edgeColor = 0x000000);
}