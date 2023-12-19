#pragma once
#include <algorithm>
#include <cmath>
#include <cassert>

// �����l�Ə���l���Ǘ�����͈̓N���X
template<class T>
class Range
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// �����l�Ə���l�̐ݒ�
	/// </summary>
	/// <param name="min">�����l</param>
	/// <param name="max">����l</param>
	Range(T min, T max) :
		m_min(min),
		m_max(max)
	{
		// �����l������l�̂ق����������ꍇ�~�߂�
		assert(m_min <= m_max);
	}

	/// <summary>
	/// �l���ݒ肵������l�͈͓̔����ǂ���
	/// </summary>
	/// <param name="value">�͈͓������ׂ����l</param>
	/// <returns> true : �͈͓�, false : �͈͓�����Ȃ� </returns>
	bool IsUpperLimit(T value) const
	{
		return (value <= m_max);
	}

	/// <summary>
	/// �l���ݒ肵�������l�͈͓̔����ǂ���
	/// </summary>
	/// <param name="value">�͈͓������ׂ����l</param>
	/// <returns> true : �͈͓�, false : �͈͓�����Ȃ� </returns>
	bool IsLowerLimit(T value) const
	{
		return (m_min <= value);
	}

	/// <summary>
	/// �l���ݒ肵�������l�Ə���l�͈͓̔����ǂ���
	/// </summary>
	/// <param name="value">�͈͓������ׂ����l</param>
	/// <returns> true : �͈͓�, false : �͈͓�����Ȃ� </returns>
	bool IsInside(T value) const
	{
		return IsLowerLimit(value) && IsUpperLimit(value);
	}

	/// <summary>
	/// �l�������l����������ꍇ�A�l�������l�ɕύX
	/// �l������l���������ꍇ�A�l������l�ɕύX
	/// </summary>
	/// <param name="value">�ύX�������l</param>
	/// <returns>�ύX��̒l</returns>
	T Clamp(T value) const
	{
		return  std::clamp(value, m_min, m_max);
	}

	/// <summary>
	/// �l�������l����������ꍇ�A�l������l�ɕύX
	/// �l������l���������ꍇ�A�l�������l�ɕύX
	/// </summary>
	/// <param name="value">�ύX�������l</param>
	/// <returns>�ύX��̒l</returns>
	T Wrap(T value) const
	{
		const float n = std::fmod(value - m_min, m_max - m_min);
		return (n >= 0) ? (n + m_min) : (n + m_max);
	}

	// �ݒ肵�������l�̎擾
	T GetMinValue() const { return m_min; }

	// �ݒ肵������l�̎擾
	T GetMaxValue() const { return m_max; }

private:
	// �����l
	T m_min;

	// ����l
	T m_max;
};