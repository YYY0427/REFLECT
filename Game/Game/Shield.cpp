#include "Shield.h"
#include "Player.h"
#include "../Effekseer3DEffectManager.h"
#include "../Image3D.h"
#include "../UI/Gauge.h"
#include "../UI/UIManager.h"
#include "../Util/InputState.h"
#include "../Util/Range.h"
#include "../Util/Timer.h"
#include "../Math/MathUtil.h"
#include "../Math/Matrix.h"
#include "../Math/Vector2.h"
#include <string>

namespace
{
	// �V�[���h�摜�̃t�@�C���p�X
	const std::string img_file_path = "Data/Image/Shield.png";	

	// �V�[���h�摜�̃T�C�Y
	constexpr float shield_width = 70.0f;	// �����T�C�Y
	constexpr float shield_height = 70.0f;	// �c���T�C�Y

	// �V�[���h�̃G�t�F�N�g�̊g�嗦
	const Vector3 effect_scale = { 80.0f,  80.0f, 80.0f, };	

	// �G�l���M�[�Q�[�WUI�̉摜�̃t�@�C���p�X
	const std::string enerugy_gage_ui_file_path = "Data/Image/EnerugyBar.png";	

	// �G�l���M�[�Q�[�WUI�̔w�i�摜�̃t�@�C���p�X
	const std::string enerugy_gage_ui_back_file_path = "Data/Image/StatusBase.png";

	// �G�l���M�[�Q�[�WUI�̈ʒu
	const Vector2 enerugy_gage_ui_pos = { 200, 600 };

	// �G�l���M�[�Q�[�WUI�̃T�C�Y
	const Vector2 enerugy_gage_ui_size = { 300, 13 };

	// �ő�G�l���M�[�Q�[�W��
	constexpr int max_enerugy_gage = 300;

	// �v���C���[����̃V�[���h�̋���
	constexpr float player_distance = 70.0f;
}

// �R���X�g���N�^
Shield::Shield(Player& player) :
	m_player(player),
	m_isInput(false),
	m_effectHandle(-1),
	m_enerugyGage(max_enerugy_gage)
{
	// 3D�摜�̃C���X�^���X�̍쐬
	m_pImage = std::make_shared<Image3D>(img_file_path);

	// �G�l���M�[�Q�[�WUI�̃C���X�^���X�̍쐬
	m_pEnergyGage = std::make_shared<Gauge>(
		enerugy_gage_ui_file_path,
		enerugy_gage_ui_back_file_path,
		"",
		max_enerugy_gage,
		enerugy_gage_ui_pos,
		enerugy_gage_ui_size,
		true,
		3.0f,
		false,
		0.0f);

	// UI�̓o�^a
	UIManager::GetInstance().AddUI("EnerugyGage", m_pEnergyGage, 0, { 0, 1 });

	// �V�[���h�摜�̏�����
	m_pImage->SetPos(m_player.GetPos());		 // �ʒu	
	m_pImage->SetImgWidth(shield_width);		 // ����
	m_pImage->SetImgHeight(shield_height);		 // �c��
}

// �f�X�g���N�^
Shield::~Shield()
{
}

// �X�V
void Shield::Update()
{
	// �v���C���[�������Ă��邩
	if (m_player.IsLive())
	{
		// ������
		auto& effectManager = Effekseer3DEffectManager::GetInstance();
		effectManager.DeleteEffect(m_effectHandle);

		m_isInput = false;
		const Range<int> enerugyGageRange(0, max_enerugy_gage);

		// ���͂���Ă��邩
		if (InputState::IsPressed(InputType::SHIELD))
		{
			// ���͂���Ă���
			m_isInput = true;
		}

		// �E�X�e�B�b�N�̓��͏��̎擾
		int up = InputState::IsPadStick(PadLR::RIGHT, PadStickInputType::UP);
		int down = InputState::IsPadStick(PadLR::RIGHT, PadStickInputType::DOWN);
		int right = InputState::IsPadStick(PadLR::RIGHT, PadStickInputType::RIGHT);
		int left = InputState::IsPadStick(PadLR::RIGHT, PadStickInputType::LEFT);

		// �V�[���h�̈ʒu�̌v�Z
		Vector3 tempVec = { (right + -left) * 10.0f, (up + -down) * 10.0f, player_distance };

		// �v���C���[�̕��s�ړ��s��̎擾
		Matrix playerMtx = Matrix::GetTranslate(m_player.GetPos());

		// �V�[���h�̑��Έʒu�ƃv���C���[�̕��s�s�񂩂�ʒu�����쐬
		m_pos = Vector3::Transform(tempVec, playerMtx);
		//	pos_ = { player_.GetPos().x, player_.GetPos().y, player_.GetPos().z + player_distance };

		// �x�N�g������p�x�����߂�
		m_rot = Matrix::ToEulerAngle(Matrix::GetRotationMatrix({0, 0, 1}, tempVec));

		// ���͂���Ă�����
		if (m_isInput)
		{
			// �G�l���M�[�Q�[�W���c���Ă�����
			if (m_enerugyGage > 0)
			{
				// �V�[���h���o���Ă���Ԃ͏�ɃG�l���M�[�Q�[�W�����炷
				m_enerugyGage--;

				// �V�[���h�G�t�F�N�g�̍Đ�
				effectManager.PlayEffect(
					m_effectHandle, 
					EffectID::player_shield, 
					{ m_pos.x, m_pos.y - 100.0f, m_pos.z },
					effect_scale, 
					1.0f, 
					m_rot);
			}
		}
		else
		{
			// ���͂���Ă��Ȃ��Ȃ�G�l���M�[�Q�[�W���񕜂�����
			m_enerugyGage++;
		}

		// �G�l���M�[�Q�[�W�͈̔͂𐧌�
		m_enerugyGage = enerugyGageRange.Clamp(m_enerugyGage);

		// �摜�̐ݒ�
		m_pImage->SetPos(m_pos); // �ʒu
		m_pImage->SetRot(m_rot); // ��]
		m_pImage->Update();		 // �X�V

		// �G�l���M�[�Q�[�W�̐ݒ�
		m_pEnergyGage->SetValue(m_enerugyGage);
	}
	else
	{
		// �v���C���[������ł�����G�t�F�N�g������
		auto& effectManager = Effekseer3DEffectManager::GetInstance();
		effectManager.DeleteEffect(m_effectHandle);
	}
}

// �`��
void Shield::Draw()
{
	// �v���C���[�������Ă�����
	// �V�[���h���o���Ă�����
	if (IsShield() && m_player.IsLive())
	{
#ifdef _DEBUG
		m_pImage->Draw();
#endif
	}
}

// �ʒu�̎擾
Vector3 Shield::GetPos() const
{
	return m_pos;
}

// �V�[���h���g�p���Ă��邩
bool Shield::IsShield() const
{
	return (m_enerugyGage > 0) && (m_isInput);
}

// �V�[���h�̒��_���̎擾
std::array<VERTEX3D, 6> Shield::GetVertex() const
{
	return m_pImage->GetVertex();
}