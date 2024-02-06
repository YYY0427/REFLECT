#pragma once
#include <string>
#include <map>

// ���f���̎��
enum class ModelType
{
	PLAYER,
	MOSQUITO,
	MATRIX,
	MOON,
	EARTH,
	METEOR,
	SKYDOME,
	LASER,
	CUBE_LASER,
	NUM
};

/// <summary>
/// ���f���Ȃǂ̃n���h�����Ǘ�����V���O���g���N���X
/// </summary>
class ModelHandleManager
{
public:
	// �C���X�^���X�̎擾
	static ModelHandleManager& GetInstance();

	// �f�X�g���N�^
	~ModelHandleManager();

	// �n���h���̉��
	void ReleaseHandle();

	int LoadModel(const std::string& filePath);

	// �n���h���̎擾
	int GetHandle(ModelType type);

	// �n���h���̍폜
	void DeleteHandle(ModelType type);

private:
	// �R���X�g���N�^
	ModelHandleManager();

	// �R�s�[�A����֎~
	ModelHandleManager(const ModelHandleManager&) = delete;
	ModelHandleManager& operator=(const ModelHandleManager&) = delete;

private:
	struct ModelData
	{
		// ���f���n���h��
		int modelHandle = -1;

		// �t�@�C���p�X
		std::string filePath;
	};

private:
	// �n���h���̃}�b�v
	std::map<ModelType, ModelData> m_handleMap;
};