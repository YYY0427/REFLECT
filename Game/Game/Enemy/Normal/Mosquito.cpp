#include "Mosquito.h"
#include "../../../Model.h"

namespace
{
	// �A�j���[�V�����ԍ�
	constexpr int idle_anim_num = 1;	// �ҋ@

	// �ړI�n�ɓ��B�������ǂ����̔���
	// �����臒l�i�K�؂Ȓl�ɒ�������K�v�j
	constexpr float distance_thres_hold = 0.1f;  
}

// �R���X�g���N�^
Mosquito::Mosquito(int modelHandle, 
	EnemyData data, 
	std::shared_ptr<Player> pPlayer, 
	std::shared_ptr<LaserManager> pLaserManager) :
	m_idleFrame(0)
	/*m_laserFireFrame(0),
	m_laserFireIdleFrame(0),
	m_laserSpeed(0),
	m_laserType({}),
	m_idleFrame(0)*/
{
	// ������
	m_pPlayer = pPlayer;
	m_pLaserManager = pLaserManager;
	m_actionDataList = data.actionDataList;
	m_isEnabled = true;
	m_pos = data.pos;
	m_hp = data.hp;
	m_moveSpeed = data.speed;
	m_attackPower = data.attack;
	m_opacity = 1.0f;
	m_rot = { 0, 0 ,0 };

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
	m_pModel->SetRot(m_rot);
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
		return;
	}

	// ���݂̈ړ��|�C���g�̃C�e���[�^�[�̎擾
	auto itr = m_actionDataList.begin();
	std::advance(itr, m_movePointIndex);

	// �ړI�n�̐ݒ�
	m_goalPos = itr->goalPos;
	m_isGoal = false;

	// �ړ��x�N�g���̐ݒ�
	m_moveVec = (itr->goalPos - m_pos).Normalized() * m_moveSpeed;
}

// �X�V
void Mosquito::Update()
{
	// �X�e�[�g�}�V���̍X�V
	m_state.Update();

	// ���f���̐ݒ�
	m_pModel->RestoreAllMaterialDifColor();	// �f�B�t���[�Y�J���[�����ɖ߂�
	m_pModel->SetOpacity(m_opacity);
	m_pModel->SetRot(m_rot);
	m_pModel->SetPos(m_pos);
	m_pModel->Update();
}

// �ҋ@��Ԃ̍X�V
void Mosquito::UpdateIdle()
{
	// �ҋ@�t���[���̍X�V
	m_actionData.idleFrame--;

	// �ҋ@�t���[�����I�������
	if (m_actionData.idleFrame <= 0)
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
		/* ���B */

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
			//// ���[�U�[�̐ݒ�
			//m_laserType = static_cast<LaserType>(itr->laserType);	// ���[�U�[�̎��
			//m_laserFireIdleFrame = itr->laserIdleFrame;	// ���[�U�[���˂܂ł̑ҋ@�t���[��
			//m_laserFireFrame = itr->laserFireFrame;		// ���[�U�[���˃t���[��
			//m_laserSpeed = itr->laserSpeed;				// ���[�U�[�̑��x
			//m_idleFrame = itr->idleFrame;				// �ړ��|�C���g�̑ҋ@�t���[��

			// ���[�U�[����
			m_state.SetState(State::ATTACK);
		}
		else
		{
			// �ړ��|�C���g�̑ҋ@�t���[����ݒ�
		//	m_idleFrame = itr->idleFrame;

			// ���[�U�[���˃t���O�������Ă��Ȃ�������
			m_state.SetState(State::IDLE);
		}

		// ���̈ړ��|�C���g��
		m_movePointIndex++;	
	}
	else
	{
		// �ړI�n�ɓ��B���Ă��Ȃ��ꍇ
		m_isGoal = false;
	}
}

// �U����Ԃ̍X�V
void Mosquito::UpdateAttack()
{
	// ���[�U�[���˂܂ł̑ҋ@�t���[���̍X�V
	m_actionData.laserFireFrame--;

	// ���[�U�[���˂܂ł̑ҋ@�t���[�����I�������
	if (m_actionData.laserFireFrame <= 0)
	{
		// ���[�U�[�̔���
		m_pLaserManager->AddLaser(
			m_actionData.laserType,
			static_cast<std::shared_ptr<EnemyBase>>(this), 
			m_actionData.laserFireFrame,
			m_actionData.laserSpeed,
			m_actionData.isPlayerFollowing);

		// �ҋ@��ԂɑJ��
		m_state.SetState(State::IDLE);
	}
}

// ���S��Ԃ̍X�V
void Mosquito::UpdateDead()
{
}

// �`��
void Mosquito::Draw()
{
	m_pModel->Draw();
}