#pragma once
#include <DxLib.h>

// �v���g�^�C�v�錾
class Vector3;

/// <summary>
/// �s��N���X
/// </summary>
class Matrix
{
public:
	Matrix();
	Matrix(float m00, float m01, float m02, float m03,
		   float m10, float m11, float m12, float m13,
		   float m20, float m21, float m22, float m23,
		   float m30, float m31, float m32, float m33);

	// �s��̊|���Z
	Matrix operator*(const Matrix& rval) const;
	Matrix operator*=(const Matrix& rval);

	// �s��̃X�J���[�{
	Matrix operator*(float scale) const;
	Matrix operator*=(float scale);

	// �s��̃X�J���[���Z
	Matrix operator/(float div) const;
	Matrix operator/=(float div);

	// �s��̓]�u
	Matrix Transpose() const;

	// �s�񂩂�I�C���[�p�ɕϊ�
	Vector3 ToEulerAngle() const;

	// DX���C�u�����̍s��ɕϊ�
	MATRIX ToDxLibMatrix() const;

	/* �ÓI�����o�֐� */
	// ����������炠������֕ϊ������]�s����擾����
	static Matrix GetRotationMatrix(const Vector3& from, const Vector3& to);

	// ���s�ړ��s����擾����
	static Matrix GetTranslate(const Vector3& v);

	// �g��k���s����擾����
	static Matrix GetScale(const Vector3& v);

	// x����]�s����擾����
	static Matrix GetRotationX(float angle);

	// y����]�s����擾����
	static Matrix GetRotationY(float angle);

	// z����]�s����擾����
	static Matrix GetRotationZ(float angle);

	// �s�񂩂�I�C���[�p�ɕϊ�
	static Vector3 ToEulerAngle(const Matrix& m);

public:
	float m[4][4];
};