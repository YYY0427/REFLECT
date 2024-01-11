#pragma once
#include "../Editor/DataReaderFromUnity.h"
#include <memory>
#include <vector>
#include <map>

// �v���g�^�C�v�錾
 class Planet;

/// <summary>
/// �f�����Ǘ�����N���X
/// </summary>
class PlanetManager
{
public:
	// �R���X�g���N�^
	PlanetManager();

	// �f�X�g���N�^
	~PlanetManager();

	// �X�V
	void UpdateStart(Vector3 playerVec);
	void Update();

	// �`��
	void Draw();

private:
	// �f��
	std::vector<std::shared_ptr<Planet>> m_pPlanet;

	// ���f���̃f�[�^
	std::map<std::string, int> m_modelHandleTable;
};