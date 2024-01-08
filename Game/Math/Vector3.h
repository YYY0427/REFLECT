#pragma once
#include <DxLib.h>

class Matrix;

/// <summary>
/// Vector3
/// </summary>
class Vector3
{
public:
	// �R���X�g���N�^
	Vector3();
	Vector3(float x, float y, float z);

	// Vec3 = Vec3 + Vec3
	Vector3 operator+ (const Vector3& rval) const;

	// Vec3 = Vec3 - Vec3
	Vector3 operator- (const Vector3& rval) const;

	// Vec3 = (Vec3 += Vec3)
	void operator+= (const Vector3& rval);

	// Vec3 = (Vec3 -= Vec3)
	void operator-= (const Vector3& rval);

	// Vec3 = Vec3 * float
	Vector3 operator*(float scale)const;

	// Vec3 = Vec3 / floats
	Vector3 operator/(float div)const;

	// Vec3 = (Vec3 *= float)
	void operator*=(float scale);

	// Vec3 = (Vec3 /= float)
	void operator/=(float div);

	// �x�N�^�[�t�](-)
	Vector3 operator-() const;

	// �x�N�g�����
	Vector3 operator=(const Vector3& vec);

	// �x�N�g�����m�̔�r
	bool operator==(const Vector3& vec);

	// �x�N�g�����m�̔�r
	bool operator!=(const Vector3& vec);

	/// �x�N�g���̑傫����Ԃ�
	float Length() const;

	// �x�N�g���̑傫����2���Ԃ�
    float SQLength() const;

	// �x�N�g���̐��K��
	void Normalize();

	// ���K�������x�N�g����Ԃ�
	Vector3 Normalized() const;

	// DX���C�u�����̃x�N�g���ɕϊ�
	VECTOR ToDxLibVector3() const;

	/* �ÓI�����o�[�֐� */ 
	// DX���C�u�����̃x�N�g������x�N�g���ɕϊ�
	static Vector3 FromDxLibVector3(const VECTOR& vec);

	// �O��
	static Vector3 Cross(const Vector3& v1, const Vector3& v2);

	// ����
	static float Dot(const Vector3& v1, const Vector3& v2);

	// ���˃x�N�g��
	static Vector3 Reflect(const Vector3& vec, const Vector3& normal);

	// �X���C�h�x�N�g��
	static Vector3 Slide(const Vector3& vec, const Vector3& normal);

	// ���`���
	static Vector3 Lerp(const Vector3& start, const Vector3& end, float value);

	// �G���~�[�g���
	static Vector3 Hermite(const Vector3& startPos, const Vector3& startTangent, const Vector3& endPos, const Vector3& endTangent, float value);
	
	// �s����g�����x�N�g���̕ϊ�
	static Vector3 Transform(const Vector3& vec, const Matrix& mat);

public:
	float x, y, z;
};