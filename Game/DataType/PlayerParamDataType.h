#pragma once
#include <string>

namespace DataType
{
	// �v���C���[�̃p�����[�^�̎��
	enum class PlayerParamType
	{
		MAX_HP,
		BOOST_EFFECT_SCALE_X,
		BOOST_EFFECT_SCALE_Y,
		BOOST_EFFECT_SCALE_Z,
		BOOST_EFFECT_SPEED,
		PlAYER_WIDTH,
		PlAYER_HEIGHT,
		COLLISION_RADIUS,
		START_MOVE_SPEED_Z,
		MOVE_SPEED_XY,
		MOVE_SPEED_Z,
		NUM
	};

	// �v���C���[�̃p�����[�^�̃L�[
	static const std::string PlayerParamKey[static_cast<int>(PlayerParamType::NUM)] =
	{
		"maxHp",
		"boostEffectScaleX",
		"boostEffectScaleY",
		"boostEffectScaleZ",
		"boostEffectSpeed",
		"playerWidth",
		"playerHeight",
		"collisionRadius",
		"startMoveSpeed",
		"moveSpeedXY",
		"moveSpeedZ"
	};
}