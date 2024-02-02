#pragma once
#include <string>
#include <vector>

// �X�R�A�̕ۑ��f�[�^
struct ScoreSaveData
{
	// �v���C���[��(20�����܂�)
	char playerName[20];

	// �X�R�A
	int score;
};

// �X�e�[�W���Ƃ̃X�R�A
struct StageScore
{
	// �X�e�[�W��
	std::string stageName;

	// �X�R�A
	std::vector<ScoreSaveData> scoreSaveData;
};

/// <summary>
/// �X�R�A�����L���O
/// </summary>
class ScoreRanking
{
public:
	// �f�X�g���N�^
	~ScoreRanking();

	// �t�@�C������X�R�A�̓ǂݍ���
	void LoadScore();

	// �X�R�A�̃f�[�^���o�C�i���t�@�C���ɕۑ�����
	void SaveScore();

	// �V�K�쐬
	void CreateNewScoreData(const std::string& stageName, std::string playerName = "", int score = 0);

	// �X�R�A�̃f�[�^��ǉ�
	void AddScore(const std::string& stageName, const char* playerName, int score);

	// �Q�b�^�[
	static ScoreRanking& GetInstance();					 // �C���X�^���X�̎擾
	const std::vector<StageScore>& GetScoreData() const; // �X�R�A�f�[�^�̎擾

private:
	// �R���X�g���N�^
	ScoreRanking();

	// �R�s�[�A����֎~
	ScoreRanking(const ScoreRanking&) = delete;
	void operator=(const ScoreRanking&) = delete;

private:
	// �X�R�A�̕ۑ��f�[�^
	std::vector<StageScore> m_scoreSaveData;	
};