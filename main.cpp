#include "DxLib.h"
#include "Application.h"

// �G���g���[�|�C���g
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	// �A�v���P�[�V�����̃C���X�^���X���擾
	auto& app = Application::GetInstance();

	// ������
	if (!app.Init())
	{
		// �������Ɏ��s������I��
		return -1;
	}

	// ���s
	app.Run();

	// �\�t�g�̏I�� 
	return 0;				
}