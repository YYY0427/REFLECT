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
	void Update(Vector3 cameraPos);

	// �`��
	void Draw();

	// 覐΂̐���
	void CreateMeteor(int createIntervalFrame, Vector3 playerPos);

	// �X���[�̒l�̐ݒ�
	void SetSlowValue(float slowValue);

	// 覐΂̎擾
	const std::list<std::shared_ptr<Meteor>>& GetMeteor() const;

private:
	// 覐�
	std::list<std::shared_ptr<Meteor>> m_pMeteorList;

	// 覐΂̃��f���n���h��
	int m_modelHandle;	

	// �����Ԋu
	int m_createIntervalFrameTimer;
};