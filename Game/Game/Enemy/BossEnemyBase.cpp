#include "BossEnemyBase.h"
#include "../../Model.h"
#include "../../Effect/Effekseer3DEffectManager.h"

namespace
{
	// �_���[�W�G�t�F�N�g�̍Đ����x
	constexpr float damage_effect_play_speed = 1.0f;

	// �_���[�W�G�t�F�N�g�̊g�嗦
	const Vector3 damage_effect_scale = { 200.0f, 200.0f, 200.0f };
}

// �R���X�g���N�^
BossEnemyBase::BossEnemyBase() :
	m_isEnabled(true),
	m_pos({ 0, 0, 0 }),
	m_rot({ 0, 0, 0 }),
	m_hp(0),
	m_opacity(0.0f),
	m_damageEffectHandle(-1)
{
}

// �f�X�g���N�^
BossEnemyBase::~BossEnemyBase()
{
}

// �_���[�W����
void BossEnemyBase::OnDamage(int damage, Vector3 pos)
{
	// HP�����炷
	m_hp -= damage;

	// ���f���̃f�B�t���[�Y�J���[�𔽓]
	m_pModel->InversAllMaterialDifColor();

	// �_���[�W�G�t�F�N�g���Đ�
	Effekseer3DEffectManager::GetInstance().PlayEffect(
		m_damageEffectHandle,
		EffectID::enemy_boss_hit_effect,
		pos,
		damage_effect_scale,
		damage_effect_play_speed);

	// HP��0�ȉ��ɂȂ�����
	if (m_hp <= 0)
	{
		// ���S�t���O�𗧂Ă�
		m_isEnabled = false;
	}
}

// �ʒu�̎擾
Vector3 BossEnemyBase::GetPos() const
{
	return m_pos;
}

// ���݃t���O�̎擾
bool BossEnemyBase::IsEnabled() const
{
	return m_isEnabled;
}
