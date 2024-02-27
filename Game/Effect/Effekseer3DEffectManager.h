#pragma once
#include "../Math/Vector3.h"
#include <string>
#include <map>
#include <list>

/// <summary>
/// Effekseer���g����3D�G�t�F�N�g�̊Ǘ����s���V���O���g���N���X
/// </summary>
class Effekseer3DEffectManager
{
private:
	// �G�t�F�N�g�̍Đ��^�C�v
	enum class PlayType
	{
		NORMAL,
		FOLLOW,
		LOOP,
		LOOP_AND_FOLLOW,
	};

	// �G�t�F�N�g�̃t�@�C���^�C�v
	enum class EffectFileType
	{
		ID,			// �G�t�F�N�g��ID
		FILE_PATH,	// �G�t�F�N�g�̃t�@�C���p�X
	};

private:
	// �G�t�F�N�g�f�[�^
	struct EffectData
	{
		std::string effectId;				// �G�t�F�N�g��ID
		int* playingEffectHandle;			// �G�t�F�N�g�̃n���h��
		PlayType	type;					// �Đ��^�C�v
		Vector3		pos;					// �ʒu	
		Vector3		rot;					// ��]
		Vector3		scale;					// �g�嗦
		float		speed;					// �Đ����x
	};

	// �Ǐ]�G�t�F�N�g�f�[�^
	struct FollowEffectData
	{
		std::string effectId;				// �G�t�F�N�g��ID
		int* playingEffectHandle;	// �G�t�F�N�g�̃n���h��
		PlayType    type;					// �Đ��^�C�v
		Vector3* pos;					// �Ǐ]�������ʒu���ϐ��̃A�h���X
		Vector3     rot;					// ��]
		Vector3		scale;					// �g�嗦
		float		speed;					// �Đ����x
	};

	// �G�t�F�N�g���\�[�X�f�[�^
	struct EffectResourceData
	{
		std::string effectFilePath;		// �G�t�F�N�g�̃t�@�C���p�X
		int         effectHandle;		// �G�t�F�N�g�̃n���h��
	};

public:
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Effekseer3DEffectManager();

	/// <summary>
	/// Effekseer3DEffectManager�̗B��̃C���X�^���X��Ԃ�
	/// </summary>
	/// <returns>�B��̎��Ԃ̎Q��</returns>
	static Effekseer3DEffectManager& GetInstance();

	// Effekseer�̏������ƃG�t�F�N�g�̃��[�h
	// �������Ɏ��s������~�߂�
	void Init();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �I������
	/// </summary>
	void End();

	/// <summary>
	/// �w��̃G�t�F�N�g�̍Đ�
	/// </summary>
	/// <param name="playingEffectHandle">�G�t�F�N�g�̃n���h��(�Ԃ��Ă����G�t�F�N�g�n���h�����g���Ēl�̕ύX���s��)</param>
	/// <param name="id">�O���t�@�C���Őݒ肵��ID</param>
	/// <param name="pos">�ʒu</param>
	/// <param name="scale">�g�嗦</param>
	/// <param name="speed">�Đ����x</param>
	/// <param name="rot">��]��</param>
	void PlayEffect(int& playingEffectHandle, 
					const std::string& id, 
					const Vector3& pos, 
					const Vector3& scale = { 1.0f, 1.0f, 1.0f }, 
					float speed = 1.0f, 
					const Vector3& rot = { 0.0f, 0.0f, 0.0f });

	/// <summary>
	/// �w��̃G�t�F�N�g�̃��[�v�Đ�
	/// </summary>
	/// <param name="playingEffectHandle">�G�t�F�N�g�̃n���h��(�Ԃ��Ă����G�t�F�N�g�n���h�����g���Ēl�̕ύX���s��)</param>
	/// <param name="id">�O���t�@�C���Őݒ肵��ID</param>
	/// <param name="pos">�ʒu</param>
	/// <param name="scale">�g�嗦</param>
	/// <param name="speed">�Đ����x</param>
	/// <param name="rot">��]��</param>
	void PlayEffectLoop(int& playingEffectHandle, 
						const std::string& id, 
						const Vector3& pos,
						const Vector3& scale = { 1.0f, 1.0f, 1.0f }, 
						float speed = 1.0f, 
						const Vector3& rot = { 0.0f, 0.0f, 0.0f });

	/// <summary>
	/// �w��̃G�t�F�N�g�̒Ǐ]�Đ�
	/// </summary>
	/// <param name="playingEffectHandle">�G�t�F�N�g�̃n���h��(�Ԃ��Ă����G�t�F�N�g�n���h�����g���Ēl�̕ύX���s��)</param>
	/// <param name="id">�O���t�@�C���Őݒ肵��ID</param>
	/// <param name="pos">�Ǐ]�������ʒu���ϐ��̃A�h���X</param>
	/// <param name="scale">�g�嗦</param>
	/// <param name="speed">�Đ����x</param>
	/// <param name="rot">��]��</param>
	void PlayEffectFollow(int& playingEffectHandle, 
						  const std::string& id, 
						  Vector3* pos, 
						  const Vector3& scale = { 1.0f, 1.0f, 1.0f }, 
						  const float speed = 1.0f, 
						  const Vector3& rot = { 0.0f, 0.0f, 0.0f });

	/// <summary>
	/// �w��̃G�t�F�N�g�̒Ǐ]�ƃ��[�v�Đ�
	/// </summary>
	/// <param name="playingEffectHandle">�G�t�F�N�g�̃n���h��(�Ԃ��Ă����G�t�F�N�g�n���h�����g���Ēl�̕ύX���s��)</param>
	/// <param name="id">�O���t�@�C���Őݒ肵��ID</param>
	/// <param name="pos">�Ǐ]�������ʒu���ϐ��̃A�h���X</param>
	/// <param name="scale">�g�嗦</param>
	/// <param name="speed">�Đ����x</param>
	/// <param name="rot">��]��</param>
	void PlayEffectLoopAndFollow(int& playingEffectHandle, 
								 const std::string& id, 
								 Vector3* pos, 
								 const Vector3& scale = { 1.0f, 1.0f, 1.0f }, 
								 const float speed = 1.0f, 
								 const Vector3& rot = { 0.0f, 0.0f, 0.0f });

	/// <summary>
	/// �G�t�F�N�g�̑S�Ă̒l�̕ύX
	/// </summary>
	/// <param name="playingEffectHandle">�G�t�F�N�g�̃n���h��</param>
	/// <param name="pos">�ʒu</param>
	/// <param name="scale">�g�嗦</param>
	/// <param name="speed">�Đ����x</param>
	/// <param name="rot">��]��</param>
	void SetEffectAllParam(const int playingEffectHandle, const Vector3& pos, const Vector3& scale, const float speed, const Vector3& rot);

	/// <summary>
	/// �G�t�F�N�g�̊g�嗦�̕ύX
	/// </summary>
	/// <param name="playingEffectHandle">�G�t�F�N�g�̃n���h��</param>
	/// <param name="scale">�g�嗦</param>
	void SetEffectScale(const int playingEffectHandle, const Vector3& scale);

	/// <summary>
	/// �G�t�F�N�g�̍Đ����x�̕ύX
	/// </summary>
	/// <param name="playingEffectHandle">�G�t�F�N�g�̃n���h��</param>
	/// <param name="speed">�Đ����x</param>
	void SetEffectSpeed(const int playingEffectHandle, const float speed);

	/// <summary>
	/// �G�t�F�N�g�̉�]���̕ύX
	/// </summary>
	/// <param name="playingEffectHandle">�G�t�F�N�g�̃n���h��</param>
	/// <param name="rot">��]��</param>
	void SetEffectRot(const int playingEffectHandle, const Vector3& rot);

	/// <summary>
	/// �G�t�F�N�g�̈ʒu�̕ύX
	/// </summary>
	/// <param name="playingEffectHandle">�G�t�F�N�g�̃n���h��</param>
	/// <param name="pos">�ʒu</param>
	void SetEffectPos(const int playingEffectHandle, const Vector3& pos);

	/// <summary>
	/// ����̃G�t�F�N�g���Đ�����
	/// </summary>
	/// <param name="playingEffectHandle">�G�t�F�N�g�̃n���h��</param>
	/// <returns>true : �Đ����Afalse : �Đ����Ă��Ȃ�</returns>
	bool IsPlayingEffect(const int playingEffectHandle);

	/// <summary>
	/// ����̃G�t�F�N�g�̍Đ����X�g�b�v
	/// �Đ��^�C�v�����[�v�̃G�t�F�N�g�̏ꍇ�͎~�܂�����A���̃t���[���ōĐ������
	/// </summary>
	/// <param name="playingEffectHandle">�G�t�F�N�g�̃n���h��</param>
	void StopEffect(const int playingEffectHandle);

	// �G�t�F�N�g�S�Ă̍Đ����X�g�b�v
	// �Đ��^�C�v�����[�v�̃G�t�F�N�g�̏ꍇ�͎~�܂�����A���̃t���[���ōĐ������
	void StopAllEffect();

	/// <summary>
	/// ����̃G�t�F�N�g�̍폜
	/// �ۑ����Ă���f�[�^�e�[�u������폜����
	/// ��ɍĐ��^�C�v�����[�v�̃G�t�F�N�g���폜����̂Ɏg��
	/// </summary>
	/// <param name="playingEffectHandle">�G�t�F�N�g�̃n���h��</param>
	void DeleteEffect(const int playingEffectHandle);

	/// <summary>
	/// �S�ẴG�t�F�N�g�̍폜
	/// </summary>
	void DeleteAllEffect();

private:
	/// <summary>
	/// �R���X�g���N�^
	/// �V���O���g���p�^�[���Ȃ̂�private</summary>
	Effekseer3DEffectManager();

	/// <summary>
	/// �R�s�[�R���X�g���N�^�֎~
	/// </summary>
	/// <param name=""></param>
	Effekseer3DEffectManager(const Effekseer3DEffectManager&) = delete;	

	/// <summary>
	/// ����֎~
	/// </summary>
	/// <param name=""></param>
	void operator = (const Effekseer3DEffectManager&) = delete;			

	/// <summary>
	/// �G�t�F�N�g��CSV�t�@�C���̓ǂݍ���
	/// </summary>
	/// <param name="filePath">�t�@�C���p�X</param>
	void LoadCsvEffectFile(const std::string& filePath);

	/// <summary>
	/// ���[�v�G�t�F�N�g�̍čĐ�
	/// ���[�v�G�t�F�N�g�̍Đ����I�����Ă�����G�t�F�N�g���Đ�����
	/// </summary>
	/// <param name="playingEffectHandle">�G�t�F�N�g�̃n���h��</param>
	/// <param name="id">�O���t�@�C���Őݒ肵����ID</param>
	void PlayEffectLoop(int& playingEffectHandle, const std::string& id);

private:
	// �G�t�F�N�g�̃��\�[�X�e�[�u��
	std::map<std::string, EffectResourceData> m_effectResourceTable;

	// �G�t�F�N�g�̃f�[�^��ۑ������e�[�u��
	std::list<EffectData> m_effectDataTable;

	// �Ǐ]�G�t�F�N�g�̃f�[�^��ۑ������e�[�u��
	std::list<FollowEffectData> m_followEffectDataTable;

	// �摜�n���h��
	int m_imgHandle;
};