#pragma once
#include <DxLib.h>
#include <string>
#include <map>
#include <list>
#include "Math/Vector3.h"

// �G�t�F�N�g�̃t�@�C���p�X
namespace EffectID
{
	const std::string test = "Test";
	const std::string player_dead = "Explosion";		// �v���C���[���S���ɏo���G�t�F�N�g
	const std::string player_shield = "MagicShield";	// �v���C���[�̃V�[���h	
	const std::string player_boost = "Boost";			// �v���C���[�ɏ�ɏo���G�t�F�N�g
	const std::string infinity_laser = "ContinueLaser";	// �G�̃��[�U�[�G�t�F�N�g
	const std::string refrect_laser = "RefrectLaser";	// �G�̃��[�U�[�𔽎˂������[�U�[
	const std::string enemy_died = "Explosion";			// �G�̎��S���̃G�t�F�N�g
	const std::string enemy_boss_entry = "EnemyBossEntry";	// �G�̃{�X���o������Ƃ��̃G�t�F�N�g
	const std::string enemy_boss_hit_effect = "BossEnemyHitEffect";
	const std::string wind = "Wind";

	const std::string effect_file_path[] =
	{ 
		test,
		player_dead,
		player_shield,
		player_boost,
		refrect_laser,
		enemy_died,
		enemy_boss_entry,
		wind,
		infinity_laser,
		enemy_boss_hit_effect,
	};
}

/// <summary>
/// Effekseer���g����3D�G�t�F�N�g�̊Ǘ����s���V���O���g���N���X
/// </summary>
class Effekseer3DEffectManager
{
public:
	// �f�X�g���N�^
	~Effekseer3DEffectManager();

	/// <summary>
	/// Effekseer3DEffectManager�̗B��̃C���X�^���X��Ԃ�
	/// </summary>
	/// <returns>�B��̎��Ԃ̎Q��</returns>
	static Effekseer3DEffectManager& GetInstance();

	// Effekseer�̏������ƃG�t�F�N�g�̃��[�h
	// �������Ɏ��s������~�߂�
	void Init();

	// �X�V
	void Update();

	// �`��
	void Draw();

	// �I������
	void End();

	/// <summary>
	/// �w��̃G�t�F�N�g�̍Đ�
	/// </summary>
	/// <param name="playingEffectHandle">�G�t�F�N�g�̃n���h��(�Ԃ��Ă����G�t�F�N�g�n���h�����g���Ēl�̕ύX���s��)</param>
	/// <param name="fileName">�Đ��������G�t�F�N�g�̃t�@�C����(�g���q�͊܂܂Ȃ�)</param>
	/// <param name="pos">�ʒu</param>
	/// <param name="scale">�g�嗦</param>
	/// <param name="speed">�Đ����x</param>
	/// <param name="rot">��]��</param>
	void PlayEffect(int& playingEffectHandle, std::string fileName, Vector3 pos, Vector3 scale = { 1.0f, 1.0f, 1.0f }, float speed = 1.0f, Vector3 rot = { 0.0f, 0.0f, 0.0f });

	/// <summary>
	/// �w��̃G�t�F�N�g�̃��[�v�Đ�
	/// </summary>
	/// <param name="playingEffectHandle">�G�t�F�N�g�̃n���h��(�Ԃ��Ă����G�t�F�N�g�n���h�����g���Ēl�̕ύX���s��)</param>
	/// <param name="fileName">�Đ��������G�t�F�N�g�̃t�@�C����(�g���q�͊܂܂Ȃ�)</param>
	/// <param name="pos">�ʒu</param>
	/// <param name="scale">�g�嗦</param>
	/// <param name="speed">�Đ����x</param>
	/// <param name="rot">��]��</param>
	void PlayEffectLoop(int& playingEffectHandle, std::string fileName, Vector3 pos, Vector3 scale = { 1.0f, 1.0f, 1.0f }, float speed = 1.0f, Vector3 rot = { 0.0f, 0.0f, 0.0f });

	/// <summary>
	/// �w��̃G�t�F�N�g�̒Ǐ]�Đ�
	/// </summary>
	/// <param name="playingEffectHandle">�G�t�F�N�g�̃n���h��(�Ԃ��Ă����G�t�F�N�g�n���h�����g���Ēl�̕ύX���s��)</param>
	/// <param name="fileName">�Đ��������G�t�F�N�g�̃t�@�C����(�g���q�͊܂܂Ȃ�)</param>
	/// <param name="pos">�Ǐ]�������ʒu���ϐ��̃A�h���X</param>
	/// <param name="scale">�g�嗦</param>
	/// <param name="speed">�Đ����x</param>
	/// <param name="rot">��]��</param>
	void PlayEffectFollow(int& playingEffectHandle, std::string fileName, Vector3* pos, Vector3 scale = { 1.0f, 1.0f, 1.0f }, float speed = 1.0f, Vector3 rot = { 0.0f, 0.0f, 0.0f });

	/// <summary>
	/// �w��̃G�t�F�N�g�̒Ǐ]�ƃ��[�v�Đ�
	/// </summary>
	/// <param name="playingEffectHandle">�G�t�F�N�g�̃n���h��(�Ԃ��Ă����G�t�F�N�g�n���h�����g���Ēl�̕ύX���s��)</param>
	/// <param name="fileName">�Đ��������G�t�F�N�g�̃t�@�C����(�g���q�͊܂܂Ȃ�)</param>
	/// <param name="pos">�Ǐ]�������ʒu���ϐ��̃A�h���X</param>
	/// <param name="scale">�g�嗦</param>
	/// <param name="speed">�Đ����x</param>
	/// <param name="rot">��]��</param>
	void PlayEffectLoopAndFollow(int& playingEffectHandle, std::string fileName, Vector3* pos, Vector3 scale = { 1.0f, 1.0f, 1.0f }, float speed = 1.0f, Vector3 rot = { 0.0f, 0.0f, 0.0f });

	/// <summary>
	/// �G�t�F�N�g�̑S�Ă̒l�̕ύX
	/// </summary>
	/// <param name="playingEffectHandle">�G�t�F�N�g�̃n���h��</param>
	/// <param name="pos">�ʒu</param>
	/// <param name="scale">�g�嗦</param>
	/// <param name="speed">�Đ����x</param>
	/// <param name="rot">��]��</param>
	void SetEffectAllParam(int playingEffectHandle, Vector3 pos, Vector3 scale, float speed, Vector3 rot);

	/// <summary>
	/// �G�t�F�N�g�̊g�嗦�̕ύX
	/// </summary>
	/// <param name="playingEffectHandle">�G�t�F�N�g�̃n���h��</param>
	/// <param name="scale">�g�嗦</param>
	void SetEffectScale(int playingEffectHandle, Vector3 scale);

	/// <summary>
	/// �G�t�F�N�g�̍Đ����x�̕ύX
	/// </summary>
	/// <param name="playingEffectHandle">�G�t�F�N�g�̃n���h��</param>
	/// <param name="speed">�Đ����x</param>
	void SetEffectSpeed(int playingEffectHandle, float speed);

	/// <summary>
	/// �G�t�F�N�g�̉�]���̕ύX
	/// </summary>
	/// <param name="playingEffectHandle">�G�t�F�N�g�̃n���h��</param>
	/// <param name="rot">��]��</param>
	void SetEffectRot(int playingEffectHandle, Vector3 rot);

	/// <summary>
	/// �G�t�F�N�g�̈ʒu�̕ύX
	/// </summary>
	/// <param name="playingEffectHandle">�G�t�F�N�g�̃n���h��</param>
	/// <param name="pos">�ʒu</param>
	void SetEffectPos(int playingEffectHandle, Vector3 pos);

	/// <summary>
	/// ����̃G�t�F�N�g���Đ�����
	/// </summary>
	/// <param name="fileName">�G�t�F�N�g�̃n���h��</param>
	/// <returns>true : �Đ����Afalse : �Đ����Ă��Ȃ�</returns>
	bool IsPlayingEffect(int effectPlayingHandle);

	/// <summary>
	/// ����̃G�t�F�N�g�̍Đ����X�g�b�v
	/// �Đ��^�C�v�����[�v�̃G�t�F�N�g�̏ꍇ�͎~�܂�����A���̃t���[���ōĐ������
	/// </summary>
	/// <param name="fileName">�G�t�F�N�g�̃n���h��</param>
	void StopEffect(int effectPlayingHandle);

	// �G�t�F�N�g�S�Ă̍Đ����X�g�b�v
	// �Đ��^�C�v�����[�v�̃G�t�F�N�g�̏ꍇ�͎~�܂�����A���̃t���[���ōĐ������
	void StopAllEffect();

	/// <summary>
	/// ����̃G�t�F�N�g�̍폜
	/// �ۑ����Ă���f�[�^�e�[�u������폜����
	/// ��ɍĐ��^�C�v�����[�v�̃G�t�F�N�g���폜����̂Ɏg��
	/// </summary>
	/// <param name="effectPlayingHandle">�G�t�F�N�g�̃n���h��</param>
	void DeleteEffect(int effectPlayingHandle);

	// �S�ẴG�t�F�N�g�̍폜
	void DeleteAllEffect();

private:
	// �R���X�g���N�^
	// �V���O���g���p�^�[���Ȃ̂�private
	Effekseer3DEffectManager();

	// �R�s�[��������֎~
	Effekseer3DEffectManager(const Effekseer3DEffectManager&) = delete;	// �R�s�[�R���X�g���N�^�֎~
	void operator = (const Effekseer3DEffectManager&) = delete;			// ����֎~

	/// <summary>
	/// �G�t�F�N�g�̃��[�h
	/// </summary>
	/// <param name="fileName">���[�h�������G�t�F�N�g�̃t�@�C����(�g���q�͊܂܂Ȃ�)</param>
	void LoadEffectFile(std::string fileName);

	/// <summary>
	/// ���[�v�G�t�F�N�g�̍čĐ�
	/// ���[�v�G�t�F�N�g�̍Đ����I�����Ă�����G�t�F�N�g���Đ�����
	/// </summary>
	/// <param name="playingEffectHandle">�G�t�F�N�g�̃n���h��</param>
	/// <param name="fileName">�čĐ�����G�t�F�N�g�̃t�@�C����(�g���q�͊܂܂Ȃ�)</param>
	void PlayEffectLoop(int& playingEffectHandle, std::string fileName);

private:
	// �G�t�F�N�g�̍Đ��^�C�v
	enum class PlayType
	{
		NORMAL,
		FOLLOW,
		LOOP,
		LOOP_AND_FOLLOW,
	};

private:
	// �G�t�F�N�g�f�[�^
	struct EffectData
	{
		std::string effectFileName;
		int* playingEffectHandle;
		PlayType type;
		Vector3 pos;
		Vector3 rot;
		Vector3 scale;
		float speed;
	};

	// �Ǐ]�G�t�F�N�g�f�[�^
	struct FollowEffectData
	{
		std::string effectFileName;
		int* playingEffectHandle;
		PlayType type;
		Vector3* pos;
		Vector3 rot;
		Vector3 scale;
		float speed;
	};

private:
	// �G�t�F�N�g�̃t�@�C������ID�Ƃ����G�t�F�N�g���\�[�X�̃n���h���̃e�[�u��
	std::map<std::string, int> m_effectResourceHandleTable;

	// �G�t�F�N�g�̃f�[�^��ۑ������e�[�u��
	std::list<EffectData> m_effectDataTable;

	// �Ǐ]�G�t�F�N�g�̃f�[�^��ۑ������e�[�u��
	std::list<FollowEffectData> m_followEffectDataTable;

	// �摜�n���h��
	int m_imgHandle;
};