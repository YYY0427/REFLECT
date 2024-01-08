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
}