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
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Matrix();
	Matrix(const float m00, const float m01, const float m02, const float m03,
		   const float m10, const float m11, const float m12, const float m13,
		   const float m20, const float m21, const float m22, const float m23,
		   const float m30, const float m31, const float m32, const float m33);

	/// <summary>
	/// �s��̊|���Z
	/// </summary>
	/// <param name="rval">�E�ӂ̍s��</param>
	/// <returns>�|���Z���ʂ̍s��</returns>
	Matrix operator*(const Matrix& rval) const;

	/// <summary>
	/// �s��̊|���Z
	/// </summary>
	/// <param name="rval"></param>
	/// <returns></returns>
	Matrix operator*=(const Matrix& rval);

	// �s��̃X�J���[�{
	Matrix operator*(const float scale) const;
	Matrix operator*=(const float scale);

	// �s��̃X�J���[���Z
	Matrix operator/(const float div) const;
	Matrix operator/=(const float div);

	// �s��̓]�u
	Matrix Transpose() const;

	// �s�񂩂�I�C���[�p�ɕϊ�
	Vector3 ToEulerAngle() const;

	// DX���C�u�����̍s��ɕϊ�
	MATRIX ToDxLibMatrix() const;


	//// �ÓI�����o�֐� ////
	
	// ����������炠������֕ϊ������]�s����擾����
	static Matrix GetRotationMatrix(const Vector3& from, const Vector3& to);

	// ���s�ړ��s����擾����
	static Matrix GetTranslate(const Vector3& v);

	// �g��k���s����擾����
	static Matrix GetScale(const Vector3& v);

	// x����]�s����擾����
	static Matrix GetRotationX(const float angle);

	// y����]�s����擾����
	static Matrix GetRotationY(const float angle);

	// z����]�s����擾����
	static Matrix GetRotationZ(const float angle);

	// �s�񂩂�I�C���[�p�ɕϊ�
	static Vector3 ToEulerAngle(const Matrix& m);

public:
	float m[4][4];
};