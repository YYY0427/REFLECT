#pragma once
#include <string>

namespace DataType
{
	// �G�t�F�N�g�̃p�����[�^�̎��
	enum class EffectType
	{
		SCALE_X,
		SCALE_Y,
		SCALE_Z,
		ROTATION_X,
		ROTATION_Y,
		ROTATION_Z,
		NUM
	};

	// �G�t�F�N�g�̃p�����[�^�̃L�[
	static const std::string EffectKey[static_cast<int>(EffectType::NUM)] =
	{
		"scaleX",
		"scaleY",
		"scaleZ",
		"rotationX",
		"rotationY",
		"rotationZ"
	};
}