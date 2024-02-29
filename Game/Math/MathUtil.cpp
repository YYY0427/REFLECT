#include "MathUtil.h"
#include <DxLib.h>

// ���W�A������x�ɕϊ�
float MathUtil::ToDegree(float radian)
{
	return radian * 180.0f / DX_PI_F;
}

// �x���烉�W�A���ɕϊ�
float MathUtil::ToRadian(float degree)
{
	return degree * DX_PI_F / 180.0f;
}

// �����̃����_���Ȓl���擾
int MathUtil::GetRandInt(const int min, const int max)
{
	return GetRand(max - min) + min;
}

// �����̃����_���Ȓl���擾
float MathUtil::GetRandFloat(const float min, const float max)
{
	int   randInt  = GetRand(static_cast<int>(max * 1000) - static_cast<int>(min * 1000));
	float randFlot = static_cast<float>(randInt + static_cast<int>(min * 1000)) / 1000.0f;
	return randFlot;
}