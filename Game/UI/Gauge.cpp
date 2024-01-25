#include "Gauge.h"
#include "../Util/DrawFunctions.h"
#include <DxLib.h>

namespace
{
	// �Q�[�W�̃t���[���̃T�C�Y
	constexpr float gauge_frame_size = 3.0f;
}

// �R���X�g���N�^
Gauge::Gauge(
	const std::string gaugeImgFilePath, 
	const std::string gaugeBackImgFilePath, 
	const std::string gaugeFrameImgFilePath, 
	float maxValue, 
	Vector2 pos, 
	Vector2 dimensions, 
	bool isGaugeBurst, 
	float addGaugeSpeed, 
	bool isDelayedDamage, 
	float aimGaugeSpeed) :
	m_maxValue(maxValue),
	m_aimValue(maxValue),
	m_backValue(maxValue),
	m_pos(pos),
	m_dimensions(dimensions),
	m_isDelayed(isDelayedDamage),
	m_aimGaugeSpeed(aimGaugeSpeed),
	m_addGaugeSpeed(addGaugeSpeed)
{
	// �o�[�X�g���o���s�����ǂ���
	if (isGaugeBurst)
	{
		m_currentValue = 0.0f;
		m_backValue = 0.0f;
		m_updateFunc = &Gauge::BurstUpdate;
		m_isEndBurst = false;
	}
	else
	{
		m_currentValue = m_maxValue;
		m_updateFunc = &Gauge::NormalUpdate;
		m_isEndBurst = true;
	}

	// �摜�̓ǂݍ���
	// �摜���w�肳��Ă��Ȃ��ꍇ��-1��������
	(gaugeImgFilePath == "") ? 
		m_gaugeImgH = -1 : m_gaugeImgH = my::MyLoadGraph(gaugeImgFilePath.c_str());
	(gaugeBackImgFilePath == "") ?
		m_gaugeBackImgH = -1 : m_gaugeBackImgH = my::MyLoadGraph(gaugeBackImgFilePath.c_str());
	(gaugeFrameImgFilePath == "") ?
		m_gaugeFrameImgH = -1 : m_gaugeFrameImgH = my::MyLoadGraph(gaugeFrameImgFilePath.c_str());
}

// �f�X�g���N�^
Gauge::~Gauge()
{
	// �摜�̍폜
	DeleteGraph(m_gaugeImgH);
	DeleteGraph(m_gaugeBackImgH);
	DeleteGraph(m_gaugeFrameImgH);
}

// �X�V
void Gauge::Update()
{
	// �X�V�֐����Ă�
	(this->*m_updateFunc)();
}

// �`��
void Gauge::Draw()
{
	// �Q�[�W��0��菬����������`�悵�Ȃ�
	if (m_backValue > 0.0f)
	{
		// �w�i�̃Q�[�W�̕`��
		DrawExtendGraph(
			m_pos.x - m_dimensions.x / 2,
			m_pos.y - m_dimensions.y / 2,
			m_pos.x - (m_dimensions.x / 2) + ((m_dimensions.x) * (static_cast<float>(m_backValue / m_maxValue))),
			m_pos.y + m_dimensions.y / 2,
			m_gaugeBackImgH,
			true);

		// �Q�[�W�̕`��
		DrawExtendGraph(
			m_pos.x - m_dimensions.x / 2,
			m_pos.y - m_dimensions.y / 2,
			m_pos.x - (m_dimensions.x / 2) + ((m_dimensions.x) * (static_cast<float>(m_currentValue / m_maxValue))),
			m_pos.y + m_dimensions.y / 2,
			m_gaugeImgH,
			true);
	}
	// �t���[���̕`��
	DrawExtendGraph(
		m_pos.x - (m_dimensions.x / 2),
		m_pos.y - m_dimensions.y / 2 - gauge_frame_size,
		m_pos.x + (m_dimensions.x / 2),
		m_pos.y - m_dimensions.y / 2,
		m_gaugeFrameImgH,
		true);
	DrawExtendGraph(
		m_pos.x - (m_dimensions.x / 2),
		m_pos.y + m_dimensions.y / 2,
		m_pos.x + (m_dimensions.x / 2),
		m_pos.y + m_dimensions.y / 2 + gauge_frame_size,
		m_gaugeFrameImgH,
		true);
	DrawExtendGraph(
		m_pos.x - (m_dimensions.x / 2) - gauge_frame_size,
		m_pos.y - m_dimensions.y / 2 - gauge_frame_size,
		m_pos.x - (m_dimensions.x / 2),
		m_pos.y + m_dimensions.y / 2 + gauge_frame_size,
		m_gaugeFrameImgH,
		true);
	DrawExtendGraph(
		m_pos.x + (m_dimensions.x / 2),
		m_pos.y - m_dimensions.y / 2 - gauge_frame_size,
		m_pos.x + (m_dimensions.x / 2) + gauge_frame_size,
		m_pos.y + m_dimensions.y / 2 + gauge_frame_size,
		m_gaugeFrameImgH,
		true);
}

void Gauge::SetValue(float afterValue)
{
	if (m_isDelayed)
	{
		// �f�B���C�^�C���̐ݒ�
		m_damageFrameCount.SetTime(60);
	}

	// �ڕW�l��ݒ�
	m_aimValue = afterValue;
	m_aimValue = (std::max)(m_aimValue, 0.0f);
}

// �o�[�X�g���o���I��������
bool Gauge::IsEndBurst() const
{
	return m_isEndBurst;
}

// �ʏ펞�̍X�V
void Gauge::NormalUpdate()
{
	// �ڕW�l�����݂̒l�ɍ��킹��
	m_currentValue = m_aimValue;
	m_currentValue = (std::max)(m_currentValue, 0.0f);

	m_damageFrameCount.Update(-1);
	if (m_damageFrameCount.GetTime() <= 0)
	{
		// �w�i�̃Q�[�W�ƖڕW�l����v���Ă��Ȃ��ꍇ
		if (m_backValue != m_aimValue)
		{
			// ���t���[���ɂ₩�ɖڕW�ɋ߂Â�
			m_backValue -= m_aimGaugeSpeed;

			// �ڕW�ɍ��v������~�߂�
			if (m_backValue < m_aimValue)
			{
				m_backValue = m_aimValue;
			}
		}
	}
}

// �o�[�X�g���o�̍X�V
void Gauge::BurstUpdate()
{
	// �ڕW�l�Ɍ������ăQ�[�W�𑝂₷
	m_currentValue += m_addGaugeSpeed;
	m_backValue += m_addGaugeSpeed;

	// �ڕW�l�𒴂�����
	if (m_currentValue >= m_maxValue && m_backValue >= m_maxValue)
	{
		// �o�[�X�g���o���I���������Ƃ������t���O�𗧂Ă�
		m_isEndBurst = true;

		// �ڕW�l�ɂ���
		m_currentValue = m_maxValue;
		m_backValue = m_maxValue;

		// �X�V�֐���ʏ펞�̍X�V�ɖ߂�
		m_updateFunc = &Gauge::NormalUpdate;
	}
}