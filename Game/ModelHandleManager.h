#pragma once
#include <string>
#include <map>

/// <summary>
/// ���f���̃n���h�����Ǘ�����V���O���g���N���X
/// </summary>
class ModelHandleManager
{
public:
	/// <summary>
	/// �C���X�^���X�̎擾
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static ModelHandleManager& GetInstance();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ModelHandleManager();

	/// <summary>
	/// �n���h���̉��
	/// </summary>
	void ReleaseHandle();

	/// <summary>
	/// ���f���̓ǂݍ���
	/// </summary>
	/// <param name="filePath">�t�@�C���p�X</param>
	/// <returns>���f���n���h��</returns>
	int LoadModel(const std::string& filePath);

	/// <summary>
	/// �n���h���̎擾
	/// </summary>
	/// <param name="id">�O���t�@�C���Őݒ肵��ID</param>
	/// <returns>���f���n���h��</returns>
	int GetHandle(const std::string& id);

	/// <summary>
	/// �n���h���̍폜
	/// </summary>
	/// <param name="id">�O���t�@�C���Őݒ肵��ID</param>
	void DeleteHandle(const std::string& id);

private:
	/// <summary>
	/// �R���X�g���N�^
	/// �V���O���g���̂���private
	/// </summary>
	ModelHandleManager();

	/// <summary>
	/// �R�s�[�R���X�g���N�^�֎~
	/// </summary>
	/// <param name=""></param>
	ModelHandleManager(const ModelHandleManager&) = delete;

	/// <summary>
	/// ������Z�q�֎~
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	ModelHandleManager& operator=(const ModelHandleManager&) = delete;

private:
	// ���f���̃t�@�C���^�C�v
	enum class ModelFileType
	{
		ID,			// ID
		FILE_PATH,	// �t�@�C���p�X
	};

private:
	// ���f���f�[�^
	struct ModelData
	{
		int modelHandle = -1; // ���f���n���h��
		std::string filePath; // �t�@�C���p�X
	};

private:
	// �n���h���̃}�b�v
	std::map<std::string, ModelData> m_handleMap;
};