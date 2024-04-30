#pragma once
#include <array>

// �X�R�A�̎��
enum class ScoreType
{
	// ��������
	ENEMY,		// �G��|�����X�R�A
	BOSS,		// �{�X��|�����X�R�A
	ITEM,		// �A�C�e�����擾�����X�R�A

	// ��������
	DAMAGE,		// �_���[�W���X�R�A

	// �X�R�A�̎�ނ̐�
	NUM			
};

/// <summary>
/// �X�R�A���Ǘ�����V���O���g���N���X
/// </summary>
class Score
{
public:
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Score();

	/// <summary>
	/// �X�R�A�̒ǉ�
	/// </summary>
	/// <param name="type">�X�R�A�̎��</param>
	void AddScore(const ScoreType type);

	/// <summary>
	/// �X�R�A�̕`��
	/// </summary>
	void DrawScore();

	/// <summary>
	/// �C���X�^���X�̎擾
	/// </summary>
	/// <returns>Score�N���X�̃C���X�^���X</returns>
	static Score& GetInstance(); 

	/// <summary>
	/// �X�R�A�̎擾
	/// </summary>
	/// <param name="type">�X�R�A�̎��</param>
	/// <returns>�X�R�A</returns>
	int GetScore(const ScoreType type) const;	

	/// <summary>
	/// ���v�X�R�A�̎擾
	/// </summary>
	/// <returns>���v�X�R�A</returns>
	int GetTotalScore() const;			

	/// <summary>
	/// �X�R�A�̃��Z�b�g
	/// </summary>
	void Reset();

private:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Score();

	// �R�s�[�A����֎~
	Score(const Score&) = delete;
	void operator=(const Score&) = delete;

private:
	// �X�R�A
	std::array<int, static_cast<int>(ScoreType::NUM)> m_score;
};