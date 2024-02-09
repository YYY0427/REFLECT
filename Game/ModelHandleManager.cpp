#include "ModelHandleManager.h"
#include "Util/DrawFunctions.h"
#include <DxLib.h>

namespace
{
	// ���f���̃t�@�C���p�X
	const std::string player_model_file_path = "Data/Model/Player.mv1";
	const std::string mosquito_model_file_path = "Data/Model/Mosquito.mv1";
	const std::string matrix_model_file_path = "Data/Model/Matrix.mv1";
	const std::string earth_model_file_path = "Data/Model/Earth.mv1";
	const std::string moon_model_file_path = "Data/Model/Moon.mv1";
	const std::string sky_dome_model_file_path = "Data/Model/SkyDome.mv1";
	const std::string meteorite_model_file_path = "Data/Model/Meteor2.mv1";
	const std::string laser_model_file_path = "Data/Model/Laser.mv1";
	const std::string cube_laser_model_file_path = "Data/Model/CubeLaser.mv1";
}

// �C���X�^���X�̎擾
ModelHandleManager& ModelHandleManager::GetInstance()
{
	static ModelHandleManager instance;
	return instance;
}

// �R���X�g���N�^
ModelHandleManager::ModelHandleManager()
{
	// ���f���̓ǂݍ���
	m_handleMap[ModelType::PLAYER].modelHandle = LoadModel(player_model_file_path.c_str());
	m_handleMap[ModelType::MOSQUITO].modelHandle = LoadModel(mosquito_model_file_path.c_str());
	m_handleMap[ModelType::MATRIX].modelHandle = LoadModel(matrix_model_file_path.c_str());
	m_handleMap[ModelType::EARTH].modelHandle = LoadModel(earth_model_file_path.c_str());
	m_handleMap[ModelType::MOON].modelHandle = LoadModel(moon_model_file_path.c_str());
	m_handleMap[ModelType::METEOR].modelHandle = LoadModel(meteorite_model_file_path.c_str());
	m_handleMap[ModelType::SKYDOME].modelHandle = LoadModel(sky_dome_model_file_path.c_str());
	m_handleMap[ModelType::LASER].modelHandle = LoadModel(laser_model_file_path.c_str());
	m_handleMap[ModelType::CUBE_LASER].modelHandle = LoadModel(cube_laser_model_file_path.c_str());
}

// �f�X�g���N�^
ModelHandleManager::~ModelHandleManager()
{
	// �n���h���̉��
	ReleaseHandle();
}

// �n���h���̉��
void ModelHandleManager::ReleaseHandle()
{
	// ���f���̃n���h�������
	for (auto& handle : m_handleMap)
	{
		MV1DeleteModel(handle.second.modelHandle);
	}
}

// ���f���̓ǂݍ���
int ModelHandleManager::LoadModel(const std::string& filePath)
{
	// ���Ƀt�@�C���p�X���o�^����Ă���ꍇ�̓n���h���Ԃ�
	for (auto& handle : m_handleMap)
	{
		if (handle.second.filePath == filePath)
		{
			return handle.second.modelHandle;
		}
	}

	// ���f���̓ǂݍ���
	return my::MyLoadModel(filePath.c_str());
}

// �n���h���̎擾
int ModelHandleManager::GetHandle(ModelType type)
{
	return m_handleMap[type].modelHandle;
}

// �n���h���̍폜
void ModelHandleManager::DeleteHandle(ModelType type)
{
	MV1DeleteModel(m_handleMap[type].modelHandle);
	m_handleMap.erase(type);
}