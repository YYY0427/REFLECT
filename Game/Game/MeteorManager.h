#pragma once
#include <memory>
#include <list>
#include "Meteor.h"
#include "../Math/Vector3.h"

/// <summary>
/// 覐΂̊Ǘ��N���X
/// </summary>
class MeteorManager
{
public:
	// �R���X�g���N�^
	MeteorManager(std::string objectDataFileName);

	// �f�X�g���N�^
	~MeteorManager();

	// �X�V
	void UpdateStart(Vector3 playerVec);
	void Update(Vector3 cameraPos);

	// �`��
	void Draw();

	// 覐΂̐���
	void SmallMeteorCreate(Vector3 playerPos);
	void CreateMeteor(int createIntervalFrame, Vector3 playerPos);

	// 覐΂̍폜
	void DeleteMeteor();

	// 覐΂̎擾
	const std::list<std::shared_ptr<Meteor>>& GetMeteor() const;

private:
	// 覐�
	std::list<std::shared_ptr<Meteor>> m_pMeteorList;

	// �����Ԋu
	int m_createIntervalFrame;
	int m_smallCreateIntervalFrame;
};