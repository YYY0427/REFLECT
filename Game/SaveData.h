#pragma once

// �v���g�^�C�v�錾
class SoundManager;

/// <summary>
/// �Z�[�u�f�[�^�̊Ǘ����s���V���O���g���N���X
/// </summary>
class SaveData
{
private:
	// �Z�[�u�f�[�^
	struct Data
	{
		int version = 0;		// �f�[�^�̃o�[�W����
		int masterVolume = 5;	// �S�̂̉���
		int bgmVolume = 5;		// BGM����	
		int seVolume = 5;		// SE����	
		int padStickSensitivityX = 6;	// �p�b�h�̃X�e�B�b�N�̊��xX
		int padStickSensitivityY = 3;	// �p�b�h�̃X�e�B�b�N�̊��xY
		bool padStickReverseX = false;	// �p�b�h�̃X�e�B�b�N�̉��̃��o�[�X
		bool padStickReverseY = false;	// �p�b�h�̃X�e�B�b�N�̏c�̃��o�[�X
		bool windowMode = false;		// �E�B���h�E���[�h�̐؂�ւ�	
	};
public:
	// �f�X�g���N�^
	~SaveData();

	/// <summary>
	/// �B��̃C���X�^���X��Ԃ�
	/// </summary>
	/// <returns>�B��̎��Ԃ̎Q��</returns>
	static SaveData& GetInstance();

	// �Z�[�u�f�[�^�̓ǂݍ���
	void Load();

	// �Z�[�u�f�[�^�̏�������
	// �Z�[�u�f�[�^�̃o�[�W��������v���Ȃ��ꍇ�͎~�߂�
	void Write();

	// �Z�[�u�f�[�^��V�K�쐬���ď㏑��
	void CreateNewData();

	Data GetSaveData() const;
	template<class T> void SetConfigValue(T& configValue, int splitNum);
	void SetConfigSwitch(bool& config);

	// ���ʐݒ�
	// ���ʂ̐ݒ�(�ő�l�𒴂����0�ɖ߂�)
	void SetMasterVolume(int configNum);	// �S�̉���
	void SetBgmVolume(int configNum);		// BGM
	void SetSeVolume(int configNum);		// SE

	// �p�b�h�̃X�e�B�b�N�̊��x�̐ݒ�
	// ���x�̐ݒ�(�ő�l�𒴂����0�ɖ߂�)
	void SetPadStickSensitivityX(int configNum);
	void SetPadStickSensitivityY(int configNum);

	// �p�b�h�̃X�e�B�b�N�̃��o�[�X�̐ݒ�
	void SetPadStickReverseX();
	void SetPadStickReverseY();

	// �E�B���h�E���[�h�̐؂�ւ�
	void SetWindowMode();

private:
	// �R���X�g���N�^
	// �V���O���g���p�^�[���Ȃ̂�private
	SaveData();

	// �R�s�[�Ƒ���̋֎~
	SaveData(const SaveData&) = delete;			// �R�s�[�R���X�g���N�^�֎~
	void operator = (const SaveData&) = delete;	// ����֎~

	// �f�[�^�̍폜
	void InitData();

private:
	// �Z�[�u�f�[�^
	Data m_saveData;

	// �T�E���h�}�l�[�W���[
	SoundManager& m_soundManger;
};