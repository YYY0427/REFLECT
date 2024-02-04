#pragma once
#include "../Editor/DataReaderFromUnity.h"
#include <memory>
#include <vector>
#include <map>

// �v���g�^�C�v�錾
 class Planet;

 // �f���̎��
 enum class PlanetType
 {
	 MOON,
	 EARTH,
	 MARS,
	 JUPITER,
	 SATURN,
	 URANUS,
	 NEPTUNE,
	 PLUTO,
	 NUM
 };	

/// <summary>
/// �f�����Ǘ�����N���X
/// </summary>
class PlanetManager
{
public:
	// �R���X�g���N�^
	PlanetManager(std::string objectDataFileName);

	// �f�X�g���N�^
	~PlanetManager();

	// �X�V
	void UpdateStart(Vector3 playerVec);
	void Update();

	// �`��
	void Draw();

	// �Q�b�^�[
	std::shared_ptr<Planet> GetPlanet(PlanetType type) const;

private:
	// �f���̃f�[�^
	struct PlanetData
	{
		// ���f���n���h��
		int modelHandle;

		// ���O
		std::string name;

		// �|�C���^
		std::shared_ptr<Planet> pPlanet;
	};

private:
	// �f���̃f�[�^
	std::map<PlanetType, PlanetData> m_planetData;
};