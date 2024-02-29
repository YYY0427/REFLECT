#pragma once
#include <cmath>
#include "Vector2.h"
#include "Vector3.h"

///<summary>
///���w�֘A�̃��[�e�B���e�B�N���X
/// </summary>
namespace MathUtil
{
	/// <summary>
	/// ���W�A������x�ɕϊ�
	/// </summary>
	/// <param name="radian">���W�A��</param>
	/// <returns>�x</returns>
	float ToDegree(float radian);

	/// <summary>
	/// �x���烉�W�A���ɕϊ�
	/// </summary>
	/// <param name="degree">�x</param>
	/// <returns>���W�A��</returns>
	float ToRadian(float degree);

	/// <summary>
	/// �����̃����_���Ȓl���擾
	/// </summary>
	/// <param name="min">�ŏ��l</param>
	/// <param name="max">�ő�l</param>
	/// <returns>�����̃����_���Ȓl</returns>
	int GetRandInt(const int min, const int max);

	/// <summary>
	/// �����̃����_���Ȓl���擾
	/// </summary>
	/// <param name="min">�ŏ��l</param>
	/// <param name="max">�ő�l</param>
	/// <returns>�����̃����_���Ȓl</returns>
	float GetRandFloat(const float min, const float max);
}