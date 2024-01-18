#include "Mosquito.h"
#include "../../../Model.h"
#include "../../Player.h"
#include <DxLib.h>

namespace
{
	// �A�j���[�V�����ԍ�
	constexpr int idle_anim_num = 1;	// �ҋ@

	// �ړI�n�ɓ��B�������ǂ����̔���
	// �����臒l�i�K�؂Ȓl�ɒ�������K�v�j
	constexpr float distance_thres_hold = 5.0f;  

	// 
	constexpr float afisajf = 0.9f;

	// ���f���̏����̌����Ă������
	const Vector3 init_model_direction = { 0, 0, -1 };
}

// �R���X�g���N�^
Mosquito::Mosquito(int modelHandle, 
	EnemyData data, 
	std::shared_ptr<Player> pPlayer, 
	std::shared_ptr<LaserManager> pLaserManager) :
	m_idleFrame(0),
	m_laserKey(-1)
{
	// ������
	m_pPlayer = pPlayer;
	m_pLaserManager = pLaserManager;
	m_actionDataList = data.actionDataList;
	m_isEnabled = true;
	m_pos = Vector3::FromDxLibVector3(ConvScreenPosToWorldPos({data.pos.x, data.pos.y, afisajf }));
	m_pos.z = m_pPlayer->GetPos().z + data.pos.z;
	m_hp = data.hp;
	m_moveSpeed = data.speed;
	m_attackPower = data.attack;
	m_opacity = 1.0f;

	// �v���C���[�������悤�ɉ�]�s���ݒ�
	Matrix rotMtx = Matrix::GetRotationMatrix(init_model_direction, (m_pPlayer->GetPos() - m_pos).Normalized());

	// �X�e�[�g�}�V���̐ݒ�
	m_state.AddState(State::IDLE, {}, [this](){ UpdateIdle(); }, {});
	m_state.AddState(State::MOVE, [this]() { EntarMove(); }, [this](){ UpdateMove(); }, {});
	m_state.AddState(State::ATTACK, {}, [this](){ UpdateAttack(); }, {});
	m_state.AddState(State::DEAD, {}, [this](){ UpdateDead(); }, {});
	m_state.SetState(State::MOVE);

	// ���f���̃C���X�^���X�̍쐬
	m_pModel = std::make_shared<Model>(modelHandle);

	// ���f���̐ݒ�
	m_pModel->SetOpacity(m_opacity);
	m_pModel->SetRotMtx(rotMtx);
	m_pModel->SetScale({ data.scale, data.scale, data.scale });
	m_pModel->SetPos(m_pos);
	m_pModel->ChangeAnimation(idle_anim_num, true, false, 8);
	m_pModel->Update();
}

// �f�X�g���N�^
Mosquito::~Mosquito()
{
}

// �ړ���Ԃɓ���O�̏���
void Mosquito::EntarMove()
{
	// �ړ��|�C���g�̃C���f�b�N�X���s���f�[�^�̃T�C�Y�𒴂��Ă�����
	if (m_movePointIndex >= m_actionDataList.size())
	{
		// ���݃t���O��������
		m_isEnabled = false;

		// ���[�U�[�𔭎˂��Ă�����
		if (m_laserKey != -1)
		{
			// ���[�U�[�̍폜
			m_pLaserManager->DeleteLaser(m_laserKey);
		}
		return;
	}

	// �ړI�n�̎擾
	GetGoalPos();

	// ������
	m_isGoal = false;
}

// �X�V
void Mosquito::Update()
{
	// �X�e�[�g�}�V���̍X�V
	m_state.Update();

	// ���[�U�[�̔��ˈʒu�̍X�V
	m_laserFirePos = m_pos;

	// �v���C���[�������悤�ɉ�]�s���ݒ�
	Matrix rotMtx = Matrix::GetRotationMatrix(init_model_direction, (m_pPlayer->GetPos() - m_pos).Normalized());

	// ���f���̐ݒ�
	m_pModel->RestoreAllMaterialDifColor();	// �f�B�t���[�Y�J���[�����ɖ߂�
	m_pModel->SetOpacity(m_opacity);
	m_pModel->SetRotMtx(rotMtx);
	m_pModel->SetPos(m_pos);
	m_pModel->Update();
}

// �ҋ@��Ԃ̍X�V
void Mosquito::UpdateIdle()
{
	// Z���W�̍X�V
	m_pos.z += m_pPlayer->GetMoveVec().z;

	// �ҋ@�t���[�����I�������
	if (m_actionData.idleFrame-- <= 0)
	{
		// �ړ���ԂɑJ��
		m_state.SetState(State::MOVE);
	}
}

// �ړ���Ԃ̍X�V
void Mosquito::UpdateMove()
{
	// �ړI�n�ɓ��B�������̔���
	if (m_pos.Distance(m_goalPos) < distance_thres_hold &&
		!m_isGoal)
	{
		// ���B�����ꍇ�A��񂵂��ʂ��Ăق����Ȃ��ׁA
		// �t���O�𗧂Ă�
		m_isGoal = true;

		// ���݂̈ړ��|�C���g�̃C�e���[�^�[�̎擾
		auto itr = m_actionDataList.begin();
		std::advance(itr, m_movePointIndex);

		// �s���f�[�^�̐ݒ�
		m_actionData = *itr;

		// ���݂̈ړ��|�C���g�̃��[�U�[���˃t���O�������Ă�����
		// ���[�U�[���ˏ�ԂɑJ��
		if (itr->isLaser)
		{
			// ���[�U�[����
			m_state.SetState(State::ATTACK);
		}
		else
		{
			// ���[�U�[���˃t���O�������Ă��Ȃ�������
			m_state.SetState(State::IDLE);
		}
		// ���̈ړ��|�C���g��
		m_movePointIndex++;	
	}
	else
	{
		// �ړI�n�̎擾
		GetGoalPos();

		// ���W�̍X�V
		m_pos += m_moveVec;
	}
}

// �U����Ԃ̍X�V
void Mosquito::UpdateAttack()
{
	// Z���W�̍X�V
	m_pos.z += m_pPlayer->GetMoveVec().z;

	// ���[�U�[���˂܂ł̑ҋ@�t���[�����I�������
	if (m_actionData.laserIdleFrame-- <= 0 && m_actionData.isLaser)
	{
		// ���[�U�[�̔���
		m_laserKey = m_pLaserManager->AddLaser(
			m_actionData.laserType,
			shared_from_this(),
			m_actionData.laserFireFrame,
			m_actionData.laserSpeed,
			m_actionData.isPlayerFollowing);

		// ���[�U�[�𔭎˂����̂Ńt���O��������
		m_actionData.isLaser = false;
	}
	// ���[�U�[���ˌ�A���[�U�[���˒��t���[���̍X�V
	else if (m_actionData.laserIdleFrame <= 0 && !m_actionData.isLaser)
	{
		// ���[�U�[���˒��t���[�����I�������
		if (m_actionData.laserFireFrame-- <= 0)
		{
			// �ҋ@��ԂɑJ��
			m_state.SetState(State::IDLE);
		}
	}
}

// ���S��Ԃ̍X�V
void Mosquito::UpdateDead()
{
}

// �ړI�n�̎擾
void Mosquito::GetGoalPos()
{
	// ���݂̈ړ��|�C���g�̃C�e���[�^�[�̎擾
	auto itr = m_actionDataList.begin();
	std::advance(itr, m_movePointIndex);

	// �ړI�n�̐ݒ�
	m_goalPos = Vector3::FromDxLibVector3(ConvScreenPosToWorldPos({ itr->goalPos.x, itr->goalPos.y, afisajf }));
	m_goalPos.z = m_pPlayer->GetPos().z + itr->goalPos.z;

	// �ړ��x�N�g���̐ݒ�
	m_moveVec = (m_goalPos - m_pos).Normalized() * m_moveSpeed;
}

// �`��
void Mosquito::Draw()
{
	// ���f���̕`��
	m_pModel->Draw();

#ifdef _DEBUG
	// �ړI�n�̕`��
	DrawSphere3D(m_goalPos.ToDxLibVector3(), 10.0f, 10, 0xff0000, 0xff0000, TRUE);
#endif
}