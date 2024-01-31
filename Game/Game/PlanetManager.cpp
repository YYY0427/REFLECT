#include "PlanetManager.h"
#include "Planet.h"
#include "../Editor/DataReaderFromUnity.h"
#include "../Util/DrawFunctions.h"
#include <string>

namespace
{
	// ���z�̃��f���̃t�@�C���p�X
	const std::string sun_model_file_path = "Data/Model/Sun.mv1";

	// �n���̃��f���̃t�@�C���p�X
	const std::string earth_model_file_path = "Data/Model/Earth.mv1";

	// ���̃��f���̃t�@�C���p�X
	const std::string moon_model_file_path = "Data/Model/Moon.mv1";
}

// �R���X�g���N�^
PlanetManager::PlanetManager()
{
	// ���f���̃��[�h
	m_modelHandleTable["Earth"] = my::MyLoadModel(earth_model_file_path.c_str());
//	m_modelHandleTable["Sun"] = my::MyLoadModel(sun_model_file_path.c_str());
//	m_modelHandleTable["Moon"] = my::MyLoadModel(moon_model_file_path.c_str());

	// �C���X�^���X�̎擾
	auto& dataReader = DataReaderFromUnity::GetInstance();

	// ���z�̃C���X�^���X�̍쐬
	/*auto& sunData = dataReader.GetData("Sun");
	for (auto& sun : sunData)
	{
		m_pPlanet.push_back(std::make_shared<Planet>(m_modelHandleTable["Sun"], sun));
	}*/

	// �n���̃C���X�^���X�̍쐬
	auto& earthData = dataReader.GetData("Earth");
	for (auto& earth : earthData)
	{
		m_pPlanet.push_back(std::make_shared<Planet>(m_modelHandleTable["Earth"], earth));
	}

	// ���̃C���X�^���X�̍쐬
	/*auto& moonData = dataReader.GetData("Moon");
	for (auto& moon : moonData)
	{
		m_pPlanet.push_back(std::make_shared<Planet>(m_modelHandleTable["Moon"], moon));
	}*/
}

// �f�X�g���N�^
PlanetManager::~PlanetManager()
{
}

// �X�^�[�g���o�̍X�V
void PlanetManager::UpdateStart(Vector3 playerVec)
{
	for (auto& planet : m_pPlanet)
	{
		planet->UpdateStart(playerVec);
	}
}

// �X�V
void PlanetManager::Update()
{
	for (auto& planet : m_pPlanet)
	{
		planet->Update();
	}
}

// �`��
void PlanetManager::Draw()
{
	for (auto& planet : m_pPlanet)
	{
		planet->Draw();
	}
}