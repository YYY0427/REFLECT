#include "PlanetManager.h"
#include "Planet.h"
#include "../Editor/DataReaderFromUnity.h"
#include "../Util/DrawFunctions.h"
#include "../ModelHandleManager.h"
#include <string>

// �R���X�g���N�^
PlanetManager::PlanetManager(std::string objectDataFileName)
{
	// �C���X�^���X�̎擾
	auto& dataReader = DataReaderFromUnity::GetInstance();

	// �n���̃C���X�^���X�̍쐬
	auto& earthData = dataReader.GetData(objectDataFileName, "Earth");
	for (auto& earth : earthData)
	{
		m_planetData[PlanetType::EARTH].modelHandle = ModelHandleManager::GetInstance().GetHandle(ModelType::EARTH);
		m_planetData[PlanetType::EARTH].pPlanet = std::make_shared<Planet>(m_planetData[PlanetType::EARTH].modelHandle, earth);
	}

	// ���̃C���X�^���X�̍쐬
	auto& moonData = dataReader.GetData(objectDataFileName, "Moon");
	for (auto& moon : moonData)
	{
		m_planetData[PlanetType::MOON].modelHandle = ModelHandleManager::GetInstance().GetHandle(ModelType::MOON);
		m_planetData[PlanetType::MOON].pPlanet = std::make_shared<Planet>(m_planetData[PlanetType::MOON].modelHandle, moon);
	}
}

// �f�X�g���N�^
PlanetManager::~PlanetManager()
{
	m_planetData.clear();
}

// �X�^�[�g���o�̍X�V
void PlanetManager::UpdateStart(Vector3 playerVec)
{
	for (auto& planet : m_planetData)
	{
		planet.second.pPlanet->UpdateStart(playerVec);
	}
}

// �X�V
void PlanetManager::Update()
{
	for (auto& planet : m_planetData)
	{
		planet.second.pPlanet->Update();
	}
}

// �`��
void PlanetManager::Draw()
{
	for (auto& planet : m_planetData)
	{
		planet.second.pPlanet->Draw();
	}
}

// �^�C�v����f���̃|�C���^���擾
std::shared_ptr<Planet> PlanetManager::GetPlanet(PlanetType type) const
{
	return m_planetData.at(type).pPlanet;
}