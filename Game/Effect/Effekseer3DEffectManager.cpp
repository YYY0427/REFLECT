#include "Effekseer3DEffectManager.h"
#include "EffekseerForDXLib.h"
#include "../Util/DrawFunctions.h"
#include <cassert>



namespace
{
	// �G�t�F�N�g�̃t�@�C���p�X
	const std::string sound_resourse_file_path = "Data/Effect/";

	// �G�t�F�N�g�̊g���q
	const std::string data_extension = ".efk";
}

// �R���X�g���N�^
Effekseer3DEffectManager::Effekseer3DEffectManager():
	m_imgHandle(-1)
{
	
}

// �f�X�g���N�^
Effekseer3DEffectManager::~Effekseer3DEffectManager()
{
}

// Effekseer3DEffectManager�̗B��̃C���X�^���X��Ԃ�
Effekseer3DEffectManager& Effekseer3DEffectManager::GetInstance()
{
	// �B��̎���
	static Effekseer3DEffectManager instance;

	// �B��̎��ԎQ�Ƃ�Ԃ�
	return instance;
}

// Effekseer�̏������ƃG�t�F�N�g�̃��[�h
void Effekseer3DEffectManager::Init()
{
	// Effekseer������������
	// �����ɂ͉�ʂɕ\������ő�p�[�e�B�N������ݒ肷��
	if (Effkseer_Init(8000) == -1)
	{
		// �������̎��s
		assert(0);
	}

	// �摜�̃��[�h
	m_imgHandle = my::MyLoadGraph("Data/Effect/background.png");

	// Effect�̃��[�h
	for (auto& filePath : EffectID::effect_file_path)
	{
		LoadEffectFile(filePath.c_str());
	}
}

// �X�V
void Effekseer3DEffectManager::Update()
{
	for (auto& effect : m_effectDataTable)
	{
		// �Đ��^�C�v�����[�v�����ʂ�Ȃ�
		if (effect.type != PlayType::LOOP) continue;

		// �Đ�������Ȃ��ꍇ�����ʂ�Ȃ�
		if (IsPlayingEffect(*effect.playingEffectHandle)) continue;

		// �G�t�F�N�g�̍čĐ�
		PlayEffectLoop(*effect.playingEffectHandle, effect.effectFileName);

		// �G�t�F�N�g�̃p�����[�^�[�̐ݒ�
		SetEffectAllParam(*effect.playingEffectHandle, effect.pos, effect.scale, effect.speed, effect.rot);
	}
	for (auto& effect : m_followEffectDataTable)
	{
		// �Đ��^�C�v�����[�v��
		bool isLoop = effect.type == PlayType::LOOP_AND_FOLLOW;

		// �Đ�����
		bool isPlay = IsPlayingEffect(*effect.playingEffectHandle);

		// �Đ��^�C�v�����[�v�A�Đ����ł͂Ȃ��ꍇ
		if (isLoop && !isPlay)
		{
			// �G�t�F�N�g�̍čĐ�
			PlayEffectLoop(*effect.playingEffectHandle, effect.effectFileName);
		}

		// �Đ����̏ꍇ�G�t�F�N�g�̃p�����[�^�[�̍X�V
		if (isPlay)
		{
			SetEffectAllParam(*effect.playingEffectHandle, *effect.pos, effect.scale, effect.speed, effect.rot);
		}
	}

	// �Đ����I�������G�t�F�N�g���������ꍇ�폜
	m_effectDataTable.remove_if([this](EffectData data) { return !IsPlayingEffect(*data.playingEffectHandle); });
	m_followEffectDataTable.remove_if([this](FollowEffectData data) { return !IsPlayingEffect(*data.playingEffectHandle); });

	// DX���C�u�����̃J������Effekseer�̃J�����𓯊�����
	Effekseer_Sync3DSetting();

	// Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����
	UpdateEffekseer3D();
}

// �`��
void Effekseer3DEffectManager::Draw()
{
	// ���ł������̂ŉ摜��`�悷��
	// �������ĕ`�悵����łȂ��ƁAEffekseer�͕`��ł��Ȃ�
	DrawGraph(0, 0, m_imgHandle, true);

	// Effekseer�ɂ��Đ����̃G�t�F�N�g��`�悷�� 
	DrawEffekseer3D();
}

// �I������
void Effekseer3DEffectManager::End()
{
	// �摜�̍폜
	DeleteGraph(m_imgHandle);

	// �G�t�F�N�g���\�[�X���폜����(Effekseer�I�����ɔj�������̂ō폜���Ȃ��Ă��������ꉞ)
	for (auto& effectResource : m_effectResourceHandleTable)
	{
		DeleteEffekseerEffect(effectResource.second);
	}

	// �z��̍폜
	m_effectResourceHandleTable.clear();
	m_effectDataTable.clear();
	m_followEffectDataTable.clear();

	// Effekseer���I������
	Effkseer_End();
}

// �G�t�F�N�g�̃��[�h
void Effekseer3DEffectManager::LoadEffectFile(std::string fileName)
{
	// �G�t�F�N�g�̃t�@�C���p�X�̐���
	std::string path = sound_resourse_file_path;
	path += fileName;
	path += data_extension;

	// �G�t�F�N�g�̃��[�h(���s������~�߂�)
	int handle = LoadEffekseerEffect(path.c_str());
	assert(handle != -1);	// -1�ȊO����Ȃ�������~�߂�

	// ���[�h�����G�t�F�N�g�̃n���h���̕ۑ�
	m_effectResourceHandleTable[fileName] = handle;
}

// ���[�v�G�t�F�N�g�̍Đ�
void Effekseer3DEffectManager::PlayEffectLoop(int& playingEffectHandle, std::string fileName)
{
	// �G�t�F�N�g���\�[�X�Ɏw�肵���G�t�F�N�g�����[�h����Ă��Ȃ��ꍇ�~�߂�
	assert(m_effectResourceHandleTable.find(fileName) != m_effectResourceHandleTable.end());

	// �G�t�F�N�g�̍čĐ�
	playingEffectHandle = PlayEffekseer3DEffect(m_effectResourceHandleTable[fileName]);
}

// �w��̃G�t�F�N�g�̍Đ�
void Effekseer3DEffectManager::PlayEffect(int& playingEffectHandle, std::string fileName, Vector3 pos, Vector3 scale, float speed, Vector3 rot)
{
	// �G�t�F�N�g���\�[�X�Ɏw�肵���G�t�F�N�g�����[�h����Ă��Ȃ��ꍇ�~�߂�
	assert(m_effectResourceHandleTable.find(fileName) != m_effectResourceHandleTable.end());

	// �G�t�F�N�g�̍Đ�
	playingEffectHandle = PlayEffekseer3DEffect(m_effectResourceHandleTable[fileName]);

	// �G�t�F�N�g�̃p�����[�^�[�̐ݒ�
	SetEffectAllParam(playingEffectHandle, pos, scale, speed, rot);

	// �f�[�^��ۑ�
	EffectData effect{};
	effect.playingEffectHandle = &playingEffectHandle;
	effect.type = PlayType::NORMAL;
	m_effectDataTable.push_back(effect);
}

// �w��̃G�t�F�N�g�̃��[�v�Đ�
void Effekseer3DEffectManager::PlayEffectLoop(int& playingEffectHandle, std::string fileName, Vector3 pos, Vector3 scale, float speed, Vector3 rot)
{
	// �G�t�F�N�g���\�[�X�Ɏw�肵���G�t�F�N�g�����[�h����Ă��Ȃ��ꍇ�~�߂�
	assert(m_effectResourceHandleTable.find(fileName) != m_effectResourceHandleTable.end());

	// �G�t�F�N�g�̍Đ�
	playingEffectHandle = PlayEffekseer3DEffect(m_effectResourceHandleTable[fileName]);

	// �G�t�F�N�g�̃p�����[�^�[�̐ݒ�
	SetEffectAllParam(playingEffectHandle, pos, scale, speed, rot);

	// �f�[�^��ۑ�
	EffectData effect{};
	effect.playingEffectHandle = &playingEffectHandle;
	effect.effectFileName = fileName;
	effect.pos = pos;
	effect.scale = scale;
	effect.speed = speed;
	effect.rot = rot;
	effect.type = PlayType::LOOP;
	m_effectDataTable.push_back(effect);
}

// �w��̃G�t�F�N�g�̒Ǐ]�Đ�
void Effekseer3DEffectManager::PlayEffectFollow(int& playingEffectHandle, std::string fileName, Vector3* pos, Vector3 scale, float speed, Vector3 rot)
{
	// �G�t�F�N�g���\�[�X�Ɏw�肵���G�t�F�N�g�����[�h����Ă��Ȃ��ꍇ�~�߂�
	assert(m_effectResourceHandleTable.find(fileName) != m_effectResourceHandleTable.end());

	// �G�t�F�N�g�̍Đ�
	playingEffectHandle = PlayEffekseer3DEffect(m_effectResourceHandleTable[fileName]);

	// �G�t�F�N�g�̃p�����[�^�[�̐ݒ�
	SetEffectAllParam(playingEffectHandle, *pos, scale, speed, rot);

	// �f�[�^��ۑ�
	FollowEffectData effect{};
	effect.playingEffectHandle = &playingEffectHandle;
	effect.effectFileName = fileName;
	effect.pos = pos;
	effect.scale = scale;
	effect.speed = speed;
	effect.rot = rot;
	effect.type = PlayType::FOLLOW;
	m_followEffectDataTable.push_back(effect);
}

// �w��̃G�t�F�N�g�̒Ǐ]�ƃ��[�v�Đ�
void Effekseer3DEffectManager::PlayEffectLoopAndFollow(int& playingEffectHandle, std::string fileName, Vector3* pos, Vector3 scale, float speed, Vector3 rot)
{
	// �G�t�F�N�g���\�[�X�Ɏw�肵���G�t�F�N�g�����[�h����Ă��Ȃ��ꍇ�~�߂�
	assert(m_effectResourceHandleTable.find(fileName) != m_effectResourceHandleTable.end());

	// �G�t�F�N�g�̍Đ�
	playingEffectHandle = PlayEffekseer3DEffect(m_effectResourceHandleTable[fileName]);

	// �G�t�F�N�g�̃p�����[�^�[�̐ݒ�
	SetEffectAllParam(playingEffectHandle, *pos, scale, speed, rot);

	// �f�[�^��ۑ�
	FollowEffectData effect{};
	effect.playingEffectHandle = &playingEffectHandle;
	effect.effectFileName = fileName;
	effect.pos = pos;
	effect.scale = scale;
	effect.speed = speed;
	effect.rot = rot;
	effect.type = PlayType::LOOP_AND_FOLLOW;
	m_followEffectDataTable.push_back(effect);
}

// �G�t�F�N�g�̑S�Ă̒l�̕ύX
void Effekseer3DEffectManager::SetEffectAllParam(int playingEffectHandle, Vector3 pos, Vector3 scale, float speed, Vector3 rot)
{
	// �Đ����x
	SetEffectSpeed(playingEffectHandle, speed);

	// �g�嗦
	SetEffectScale(playingEffectHandle, scale);

	// ��]��
	SetEffectRot(playingEffectHandle, rot);

	// �ʒu
	SetEffectPos(playingEffectHandle, pos);
}

// �G�t�F�N�g�̊g�嗦�̕ύX
void Effekseer3DEffectManager::SetEffectScale(int playingEffectHandle, Vector3 scale)
{
	// �G�t�F�N�g�̊g�嗦�̐ݒ�
	int result = SetScalePlayingEffekseer3DEffect(playingEffectHandle, scale.x, scale.y, scale.z);

	// ���s������~�߂�
	assert(result != -1);
	
	// �G�t�F�N�g�̃f�[�^��ۑ����Ă���e�[�u���̒l��ύX����
	// �ǂ����̃e�[�u���Ɋi�[����Ă��邩������Ȃ����ߗ����̃e�[�u�����m�F����
	for (auto& effect : m_effectDataTable)
	{
		if (*effect.playingEffectHandle == playingEffectHandle)
		{
			effect.scale = scale;
		}
	}
	for (auto& effect : m_followEffectDataTable)
	{
		if (*effect.playingEffectHandle == playingEffectHandle)
		{
			effect.scale = scale;
		}
	}
}

// �G�t�F�N�g�̍Đ����x�̕ύX
void Effekseer3DEffectManager::SetEffectSpeed(int playingEffectHandle, float speed)
{
	// �G�t�F�N�g�̍Đ����x�̐ݒ�
	int result = SetSpeedPlayingEffekseer3DEffect(playingEffectHandle, speed);

	// ���s������~�߂�
	assert(result != -1);

	// �G�t�F�N�g�̃f�[�^��ۑ����Ă���e�[�u���̒l��ύX����
	// �ǂ����̃e�[�u���Ɋi�[����Ă��邩������Ȃ����ߗ����̃e�[�u�����m�F����
	for (auto& effect : m_effectDataTable)
	{
		if (*effect.playingEffectHandle == playingEffectHandle)
		{
			effect.speed = speed;
		}
	}
	for (auto& effect : m_followEffectDataTable)
	{
		if (*effect.playingEffectHandle == playingEffectHandle)
		{
			effect.speed = speed;
		}
	}
}

// �G�t�F�N�g�̉�]���̕ύX
void Effekseer3DEffectManager::SetEffectRot(int playingEffectHandle, Vector3 rot)
{
	// �G�t�F�N�g�̉�]���̐ݒ�
	int result = SetRotationPlayingEffekseer3DEffect(playingEffectHandle, rot.x, rot.y, rot.z);

	// ���s������~�߂�
	assert(result != -1);

	// �G�t�F�N�g�̃f�[�^��ۑ����Ă���e�[�u���̒l��ύX����
	// �ǂ����̃e�[�u���Ɋi�[����Ă��邩������Ȃ����ߗ����̃e�[�u�����m�F����
	for (auto& effect : m_effectDataTable)
	{
		if (*effect.playingEffectHandle == playingEffectHandle)
		{
			effect.rot = rot;
		}
	}
	for (auto& effect : m_followEffectDataTable)
	{
		if (*effect.playingEffectHandle == playingEffectHandle)
		{
			effect.rot = rot;
		}
	}
}

// �G�t�F�N�g�̈ʒu�̕ύX
void Effekseer3DEffectManager::SetEffectPos(int playingEffectHandle, Vector3 pos)
{
	// �G�t�F�N�g�̈ʒu�̐ݒ�
	int result = SetPosPlayingEffekseer3DEffect(playingEffectHandle, pos.x, pos.y, pos.z);

	// ���s������~�߂�
	assert(result != -1);

	// �G�t�F�N�g�̃f�[�^��ۑ����Ă���e�[�u���̒l��ύX����
	// �Ǐ]�G�t�F�N�g�͕K�v�Ȃ��̂ŕύX���Ȃ�
	for (auto& effect : m_effectDataTable)
	{
		if (*effect.playingEffectHandle == playingEffectHandle)
		{
			effect.pos = pos;
		}
	}
}

// ����̃G�t�F�N�g���Đ�����
bool Effekseer3DEffectManager::IsPlayingEffect(int effectPlayingHandle)
{
	if (IsEffekseer3DEffectPlaying(effectPlayingHandle) == 0)
	{
		return true;
	}
	return false;
}

// ����̃G�t�F�N�g�̍Đ����X�g�b�v
void Effekseer3DEffectManager::StopEffect(int effectPlayingHandle)
{
	int result = StopEffekseer3DEffect(effectPlayingHandle);
	assert(result != -1);
}

// �G�t�F�N�g�S�Ă̍Đ����X�g�b�v
void Effekseer3DEffectManager::StopAllEffect()
{
	for (auto& effect : m_effectDataTable)
	{
		StopEffect(*effect.playingEffectHandle);
	}
	for (auto& effect : m_followEffectDataTable)
	{
		StopEffect(*effect.playingEffectHandle);
	}
}

// ����̃G�t�F�N�g�̍폜
void Effekseer3DEffectManager::DeleteEffect(int effectPlayingHandle)
{
	// �G�t�F�N�g�̍Đ����~�߂�
	StopEffect(effectPlayingHandle);

	// �ǂ����̃e�[�u���Ɋi�[����Ă��邩������Ȃ����ߗ����̃e�[�u�����m�F���n���h������v�����f�[�^���폜
	m_effectDataTable.remove_if(
		[effectPlayingHandle](EffectData data) 
		{ return *data.playingEffectHandle == effectPlayingHandle; });
	m_followEffectDataTable.remove_if(
		[effectPlayingHandle](FollowEffectData data) 
		{ return *data.playingEffectHandle == effectPlayingHandle; });
}

// �S�ẴG�t�F�N�g�̍폜
void Effekseer3DEffectManager::DeleteAllEffect()
{
	// �S�ẴG�t�F�N�g�̍Đ����~�߂�
	StopAllEffect();

	// �S�Ẵf�[�^�̍폜
	m_effectDataTable.clear();
	m_followEffectDataTable.clear();
}