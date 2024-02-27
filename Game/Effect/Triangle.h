#pragma once
#include "../Math/Vector3.h"
#include "../Math/Vector2.h"
#include "../Util/Timer.h"
#include <array>
#include <vector>

/// <summary>
/// �{�X���S���̉��o�Ɏg�p����O�p�`
/// </summary>
class Triangle
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="frame">���t���[���ŉ��o���s����</param>
	Triangle(const int frame);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Triangle();

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="bossEnemyPos">�{�X�G�̈ʒu</param>
	void Update(const Vector3& bossEnemyPos);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �I��������
	/// </summary>
	/// <returns>true : �I���Afalse : �r��</returns>
	bool IsEnd() const;

private:
	// �O�p�`�̃f�[�^
	struct TriangleData
	{
		std::array<Vector2, 3> pos;		// �ʒu
		float alpha;					// �A���t�@�l
	};

private:
	// �O�p�`�̃f�[�^�e�[�u��
	std::vector<TriangleData> m_triangleDataTable;

	// �p�x
	float m_angle;	

	// �O�p�`�̐F
	Vector3 m_color;

	// ���t���[���ŉ��o���s����
	Timer<int> m_frame;	

	// �O�p�`��`�悷��Ԋu�̃t���[��
	Timer<int> m_intervalFrame;	
};