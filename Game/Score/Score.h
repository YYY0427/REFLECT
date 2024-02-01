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
	DEATH,		// ���S���̃X�R�A

	// �X�R�A�̎�ނ̐�
	NUM			
};

/// <summary>
/// �X�R�A�N���X
/// </summary>
class Score
{
public:
	// �f�X�g���N�^
	~Score();

	// �X�R�A�̉��Z
	void AddScore(ScoreType type);

	// �X�R�A�̕`��
	void DrawScore();

	// �Q�b�^�[
	static Score& GetInstance();		// �C���X�^���X�̎擾
	int GetScore(ScoreType type) const;	// �X�R�A�̎擾
	int GetTotalScore() const;			// ���v�X�R�A�̎擾

private:
	// �R���X�g���N�^
	Score();

	// �R�s�[�A����֎~
	Score(const Score&) = delete;
	void operator=(const Score&) = delete;

private:
	// �X�R�A
	std::array<int, static_cast<int>(ScoreType::NUM)> m_score;
};