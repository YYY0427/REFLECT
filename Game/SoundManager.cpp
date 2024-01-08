#include "SoundManager.h"
#include "SaveData.h"
#include "StringManager.h"
#include <cassert>
#include <fstream>
#include <sstream>

namespace
{
	// �T�E���h�̃t�@�C���p�X
	const std::string data_file_path = "Data/Sound/";

	// �ݒ肷�鉹�ʂ����ɕ����邩
	constexpr int config_volume_num = 5;
}

// �R���X�g���N�^
SoundManager::SoundManager()
{
}

// �f�X�g���N�^
SoundManager::~SoundManager()
{
}

// �B��̃C���X�^���X��Ԃ�
SoundManager& SoundManager::GetInstance()
{
	// �B��̎���
	static SoundManager instance;

	// �B��̎��ԎQ�Ƃ�Ԃ�
	return instance;
}

// 2D�T�E���h�̃��[�h
void SoundManager::LoadSoundFile2D(std::string fileName, std::string extension)
{
	std::string path = data_file_path;
	path += fileName;
	path += extension;
	int handle = LoadSoundMem(path.c_str());
	assert(handle != -1);
	m_soundDataTable[fileName].handle = handle;
}

// 3D�T�E���h�̃��[�h
void SoundManager::LoadSoundFile3D(std::string fileName, std::string extension)
{
	std::string path = data_file_path;
	path += fileName;
	path += extension;
	SetCreate3DSoundFlag(TRUE);
	int handle = LoadSoundMem(path.c_str());
	SetCreate3DSoundFlag(FALSE);
	assert(handle != -1);
	m_soundDataTable[fileName].handle = handle;
}

// �t�@�C������T�E���h�̃f�[�^��ǂݎ���ăf�[�^�e�[�u���Ɋi�[
void SoundManager::LoadAndStoreSoundFileData()
{
	// �t�@�C�����̓ǂݍ���(�ǂݍ��݂Ɏ��s������~�߂�)
	std::ifstream ifs("Data/Csv/Sound.csv");
	assert(ifs);

	// csv�f�[�^��1�s���ǂݎ��
	bool isFirst = false;
	std::string line;
	while (getline(ifs, line))
	{
		// 1�s�ڂ͓ǂݍ��܂Ȃ�
		// 1�s�ڂɂ͍��ڂ������Ă��邽��
		if (!isFirst)
		{
			isFirst = true;
			continue;
		}

		// csv�f�[�^�P�s��','�ŕ����̕�����ɕϊ�
		std::vector<std::string> strvec = StringManager::GetInstance().SplitString(line, ',');
		
		// �������K�؂ȃf�[�^�^�ɕϊ����Ċi�[
		SoundData data;
		data.handle = -1;	// ������
		data.volumeRate = std::stof(strvec[static_cast<int>(SoundDataType::VOLUM_RATE)]);	// string�^����float�^�ɕϊ����i�[
		data.extension = strvec[static_cast<int>(SoundDataType::EXTENSION)];				// string�^�Ŋi�[
		
		// �T�E���h�^�C�v�̕ۑ�
		// �ϊ������f�[�^���t�@�C������ID�Ƃ��Ċi�[
		// �T�E���h�̃^�C�v�ɂ���Ă��ꂼ�ꃍ�[�h
		int iSoundType = std::stoi(strvec[static_cast<int>(SoundDataType::SOUND_TYPE)]);	// string�^����int�^�ɕϊ�
		SoundType soundType = static_cast<SoundType>(iSoundType);							// int�^����SoundType�^�ɕϊ�
		switch (soundType)
		{
		case SoundType::BGM:
			data.type = SoundType::BGM;
			m_soundDataTable[strvec[static_cast<int>(SoundDataType::FILE_NAME)]] = data;
			LoadSoundFile2D(strvec[static_cast<int>(SoundDataType::FILE_NAME)], data.extension);
			break;
		case SoundType::SE2D:
			data.type = SoundType::SE2D;
			m_soundDataTable[strvec[static_cast<int>(SoundDataType::FILE_NAME)]] = data;
			LoadSoundFile2D(strvec[static_cast<int>(SoundDataType::FILE_NAME)], data.extension);
			break;
		case SoundType::SE3D:
			data.type = SoundType::SE3D;
			m_soundDataTable[strvec[static_cast<int>(SoundDataType::FILE_NAME)]] = data;
			LoadSoundFile3D(strvec[static_cast<int>(SoundDataType::FILE_NAME)], data.extension);
			break;
		default:
			// ���蓾�Ȃ��l�Ȃ̂Ŏ~�߂�
			assert(0);
			break;
		}
	}
}

// �w���2DSE��炷
void SoundManager::Play(std::string fileName)
{
	assert(m_soundDataTable.find(fileName) != m_soundDataTable.end());	// ���[�h���Ă��Ȃ��ꍇ�͎~�߂�
	assert(m_soundDataTable[fileName].type == SoundType::SE2D);					// 2DSE�ȊO�̏ꍇ�͎~�߂�
	PlaySoundMem(m_soundDataTable[fileName].handle, DX_PLAYTYPE_BACK);
	SetVolume(fileName, 255);
}

// �w���3DSE��炷
void SoundManager::Play3D(std::string fileName, VECTOR soundPos, float soundRadius)
{
	assert(m_soundDataTable.find(fileName) != m_soundDataTable.end());	// ���[�h���Ă��Ȃ��ꍇ�͎~�߂�
	assert(m_soundDataTable[fileName].type == SoundType::SE3D);					// 3DSE�ȊO�̏ꍇ�͎~�߂�
	Set3DPositionSoundMem(soundPos, m_soundDataTable[fileName].handle);
	Set3DRadiusSoundMem(soundRadius, m_soundDataTable[fileName].handle);
	PlaySoundMem(m_soundDataTable[fileName].handle, DX_PLAYTYPE_BACK);
	SetVolume(fileName, 255);
}

// �w���BGM��炷
void SoundManager::PlayBGM(std::string fileName)
{
	assert(m_soundDataTable.find(fileName) != m_soundDataTable.end());	// ���[�h���Ă��Ȃ��ꍇ�͎~�߂�
	assert(m_soundDataTable[fileName].type == SoundType::BGM);					// BGM�ȊO�̏ꍇ�͎~�߂�
	PlaySoundMem(m_soundDataTable[fileName].handle, DX_PLAYTYPE_LOOP);
	SetVolume(fileName, 255);
}

// ����̃T�E���h���Đ������`�F�b�N
bool SoundManager::PlayingCheckSound(std::string fileName)
{
	assert(m_soundDataTable.find(fileName) != m_soundDataTable.end());	// ���[�h���Ă��Ȃ��ꍇ�͎~�߂�
	bool sound = CheckSoundMem(m_soundDataTable[fileName].handle);
	return sound;
}

// ����̃T�E���h���~�߂�
void SoundManager::StopSound(std::string fileName)
{
	assert(m_soundDataTable.find(fileName) != m_soundDataTable.end());	// ���[�h���Ă��Ȃ��ꍇ�͎~�߂�
	StopSoundMem(m_soundDataTable[fileName].handle);
}

// ���ׂẴT�E���h���~�߂�
void SoundManager::StopAllSound()
{
	for (auto& sound : m_soundDataTable)
	{
		StopSoundMem(sound.second.handle);
	}
}

// ���ʒ���
void SoundManager::SetVolume(std::string fileName, int volume)
{
	// �T�E���h�ɐݒ肳�ꂽ���ʒ���
	int setVolume = volume;
	setVolume = static_cast<int>(volume * m_soundDataTable[fileName].volumeRate);

	// �R���t�B�O�Őݒ肵���T�E���h�̑S�̉��ʒ���
	int configWholeVolume = SaveData::GetInstance().GetSaveData().masterVolume;
	float configWholeRate = static_cast<float>(configWholeVolume) / config_volume_num;

	// �R���t�B�O�Őݒ肵���T�E���h�^�C�v�ʉ��ʒ���
	int configVolume = 0;
	if (m_soundDataTable[fileName].type == SoundType::BGM)
	{
		// BGM
		configVolume = SaveData::GetInstance().GetSaveData().bgmVolume;
	}
	else
	{
		// SE
		configVolume = SaveData::GetInstance().GetSaveData().seVolume;
	}

	// �ݒ肵�������ʂƃT�E���h�ɐݒ肳�ꂽ���ʂƃR���t�B�O�Őݒ肳�ꂽ���ʂ��狁�߂��ŏI�I�ȉ��ʂɐݒ�
	float configRate = static_cast<float>(configVolume) / config_volume_num;
	setVolume = static_cast<int>(setVolume * configRate * configWholeRate);
	ChangeVolumeSoundMem(setVolume, m_soundDataTable[fileName].handle);
}

// 3D�T�E���h�̃��X�i�[�̈ʒu�ƃ��X�i�[�̑O���ʒu��ݒ肷��
void SoundManager::Set3DSoundListenerPosAndFrontPos_UpVecY(VECTOR pos, VECTOR angle)
{
	DxLib::Set3DSoundListenerPosAndFrontPos_UpVecY(pos, VAdd(pos, angle));
}