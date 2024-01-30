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
	Triangle(int frame);

	// �f�X�g���N�^
	~Triangle();

	// �X�V
	void Update(Vector3 bossEnemyPos);

	// �`��
	void Draw();

	// �I���������ǂ���
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