#pragma once

/// <summary>
/// �C�[�W���O�֐����܂Ƃ߂��N���X
/// https://easings.net/ja
/// </summary>
class Easing
{
public:
	/// <summary>
	/// �C�[�W���O�֐�
	/// </summary>
	/// <param name="time">���݂̎���</param>
	/// <param name="totalTime">������</param>
	/// <param name="max">�I���l</param>
	/// <param name="min">�J�n�l</param>
	/// <returns></returns>
	static float EaseOutCubic(float time, float totalTime, float max, float min);
};
