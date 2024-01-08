#include "MathUtil.h"
#include "DxLib.h"

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