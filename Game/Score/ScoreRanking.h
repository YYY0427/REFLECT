#pragma once
#include <string>
#include <vector>

/// <summary>
/// �X�R�A�����L���O
/// </summary>
class ScoreRanking
{
public:
	// �R���X�g���N�^
	ScoreRanking();

	// �f�X�g���N�^
	~ScoreRanking();

	// �t�@�C������X�R�A�̓ǂݍ���
	void LoadScore(std::string fileName);

private:
	// �X�R�A�̕ۑ��f�[�^
	struct ScoreSaveData
	{
		// �v���C���[��(20�����܂�)
		char playerName[20];

		// �X�R�A
		int score;
	};

private:
	// �X�R�A�̕ۑ��f�[�^
	std::vector<std::vector<ScoreSaveData>> m_scoreSaveData;	
};