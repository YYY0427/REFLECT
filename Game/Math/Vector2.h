#pragma once

/// <summary>
/// Vector2
/// </summary>
class Vector2
{
public:
	// �R���X�g���N�^
	Vector2();
	Vector2(float x, float y);

	// Vec2 = Vec2 + Vec2
	Vector2 operator+ (const Vector2& rval) const
	{
		return { x + rval.x, y + rval.y };
	}

	// Vec2 = Vec2 - Vec2
	Vector2 operator- (const Vector2& rval) const
	{
		return { x - rval.x, y - rval.y };
	}

	// Vec2 = (Vec2 += Vec2)
	void operator+= (const Vector2& rval);

	// Vec2 = (Vec2 -= Vec2)
	void operator-= (const Vector2& rval);

	// Vec2 = Vec2 * float
	Vector2 operator*(float scale)const;

	// Vec2 = Vec2 / floats
	Vector2 operator/(float div)const;

	// Vec2 = (Vec2 *= float)
	void operator*=(float scale);

	// Vec2 = (Vec2 /= float)
	void operator/=(float div);

	// Vec2 == Vec2
	bool operator==(const Vector2& rval) const;

	// Vec2 != Vec2
	bool operator!=(const Vector2& rval) const;

	// �x�N�^�[�t�](-)
	Vector2 operator-() const;

	/// �x�N�g���̑傫����Ԃ�
	float Length() const;

	// �x�N�g���̑傫����2���Ԃ�
	float SQLength() const;

	// �x�N�g���̐��K��
	void Normalize();

	// ���K�������x�N�g����Ԃ�
	Vector2 Normalized() const;

public:
	float x, y;
};