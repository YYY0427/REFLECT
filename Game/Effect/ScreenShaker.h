#pragma once
#include "../Util/Timer.h"
#include "../Math/Vector2.h"
#include <memory>

// �v���g�^�C�v�錾
class Camera;

/// <summary>
/// ��ʂ�h�炷�N���X
/// </summary>
class ScreenShaker
{
public:
	// �R���X�g���N�^
	ScreenShaker(std::shared_ptr<Camera> pCamera);

	// �f�X�g���N�^
	~ScreenShaker();

	// �X�V
	void Update();

	// �`��O�ɕK���Ă�
	void PreDraw();

	// �`��
	void Draw();

	// ��ʗh��̊J�n
	void StartShake(Vector2 quakeSize, int frame);

private:
	// �|�C���^
	std::shared_ptr<Camera> m_pCamera;

	// �h��鎞��
	Timer<int> m_quakeTimer;	

	// �h��鋭��
	Vector2 m_quakeSize;

	// PreDraw��������
	bool m_isPreDraw;

	// ��ʃn���h��
	int m_screenHandle;
};