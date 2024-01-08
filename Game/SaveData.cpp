#include "SaveData.h"
#include "SoundManager.h"
#include "Util/Range.h"
#include "Util/InputState.h"
#include <string>
#include <cassert>
#include <fstream>
#include <DxLib.h>

namespace
{
	// �t�@�C���̃p�X
	const std::string data_file_path = "Data/Save/SaveData.dat";

	// �Z�[�u�f�[�^�o�[�W�����@
	constexpr int current_save_version = 0;
}

// �R���X�g���N�^
SaveData::SaveData() :
	m_soundManger(SoundManager::GetInstance())
{
	
}

// �f�X�g���N�^
SaveData::~SaveData()
{
}

// �B��̃C���X�^���X��Ԃ�
SaveData& SaveData::GetInstance()
{
	// �B��̎���
	static SaveData instance;

	// �B��̎��ԎQ�Ƃ�Ԃ�
	return instance;
}

// �Z�[�u�f�[�^�̓ǂݍ���
void SaveData::Load()
{
	// �Z�[�u�f�[�^�̏�����
	InitData();

	std::ifstream ifs;
	ifs.open(data_file_path, std::ios_base::binary);

	// �t�@�C���ǂݍ��ݎ��s
	if (ifs.fail())
	{
		// �Z�[�u�f�[�^�����
		CreateNewData();
		return;
	}
	else
	{
		// �Z�[�u�f�[�^�̓ǂݍ���
		Data data;
		ifs.read(reinterpret_cast<char*>(&data), sizeof(Data));
		ifs.close();

		if (data.version == current_save_version)
		{
			// �ǂݍ��񂾃f�[�^�����ۂɎg�p����f�[�^�ɃR�s�[
			m_saveData = data;
		}
		else
		{
			// �����[�X��ɃZ�[�u�f�[�^�̃o�[�W�������ς���������
			assert(0);
		}
	}
}

// �Z�[�u�f�[�^�̏�������
void SaveData::Write()
{
	assert(m_saveData.version == current_save_version);
	std::ofstream ofs(data_file_path, std::ios_base::binary);
	ofs.write(reinterpret_cast<char*>(&m_saveData), sizeof(Data));
}

// �Z�[�u�f�[�^��V�K�쐬���ď㏑��
void SaveData::CreateNewData()
{
	// �Z�[�u�f�[�^�̏�����
	InitData();

	std::ofstream ofs(data_file_path, std::ios_base::binary);
	ofs.write(reinterpret_cast<char*>(&m_saveData), sizeof(SaveData));
}

// �Z�[�u�f�[�^�̏�����
void SaveData::InitData()
{
	m_saveData.version = current_save_version;
	m_saveData.bgmVolume = 5;
	m_saveData.seVolume = 5;
	m_saveData.masterVolume = 5;
	m_saveData.padStickSensitivityX = 6;
	m_saveData.padStickSensitivityY = 3;
	m_saveData.padStickReverseX = false;	
	m_saveData.padStickReverseY = false;	
	m_saveData.windowMode = false;
}

template<class T> void SaveData::SetConfigValue(T& configValue, int splitNum)
{
	if (InputState::IsTriggered(InputType::RIGHT))
	{
		configValue++;
	}
	if (InputState::IsTriggered(InputType::LEFT))
	{
		configValue--;
	}

	const Range<T> configValueRange(0, splitNum + 1);

	configValue = configValueRange.Wrap(configValue);

	// �Z�[�u�f�[�^�ɏ�������
	SaveData::GetInstance().Write();
}

// �S�̂̉��ʂ̐ݒ�
// �ő�l�𒴂����0�ɖ߂�
void SaveData::SetMasterVolume(int configNum)
{
	SetConfigValue(m_saveData.masterVolume, configNum);

	if (InputState::IsTriggered(InputType::RIGHT) ||
		InputState::IsTriggered(InputType::LEFT))
	{
		m_soundManger.SetVolume("bgmTest", 255);
	}
}

// BGM�̉��ʂ̐ݒ�
// �ő�l�𒴂����0�ɖ߂�
void SaveData::SetBgmVolume(int configNum)
{
	SetConfigValue(m_saveData.bgmVolume, configNum);

	if (InputState::IsTriggered(InputType::RIGHT) ||
		InputState::IsTriggered(InputType::LEFT))
	{
		m_soundManger.SetVolume("bgmTest", 255);
	}
}

// SE�̉��ʂ̐ݒ�
// �ő�l�𒴂����0�ɖ߂�
void SaveData::SetSeVolume(int configNum)
{
	SetConfigValue(m_saveData.seVolume, configNum);

	if (InputState::IsTriggered(InputType::RIGHT) ||
		InputState::IsTriggered(InputType::LEFT))
	{
		m_soundManger.Play("cursorTest");
	}
}

// �p�b�h�̃X�e�B�b�N��X�����x�̐ݒ�
// �ő�l�𒴂����0�ɖ߂�
void SaveData::SetPadStickSensitivityX(int configNum)
{
	SetConfigValue(m_saveData.padStickSensitivityX, configNum);
}

// �p�b�h�̃X�e�B�b�N��Y�����x�̐ݒ�
// �ő�l�𒴂����0�ɖ߂�
void SaveData::SetPadStickSensitivityY(int configNum)
{
	SetConfigValue(m_saveData.padStickSensitivityY, configNum);
}

// �p�b�h�̃X�e�B�b�N��X�����o�[�X�̐ݒ�
void SaveData::SetPadStickReverseX()
{
	SetConfigSwitch(m_saveData.padStickReverseX);
}

// �p�b�h�̃X�e�B�b�N��Y�����o�[�X�̐ݒ�
void SaveData::SetPadStickReverseY()
{
	SetConfigSwitch(m_saveData.padStickReverseY);
}

void SaveData::SetWindowMode()
{
	SetConfigSwitch(m_saveData.windowMode);
}

SaveData::Data SaveData::GetSaveData() const
{
	return m_saveData;
}

void SaveData::SetConfigSwitch(bool& config)
{
	if (InputState::IsTriggered(InputType::RIGHT) ||
		InputState::IsTriggered(InputType::LEFT))
	{
		if (config)
		{
			config = false;
		}
		else
		{
			config = true;
		}
	}

	// �Z�[�u�f�[�^�ɏ�������
	SaveData::GetInstance().Write();
}