#pragma once
#include <algorithm>

// �^�C�}�[�N���X
template<class T>
class Timer
{
public: 
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Timer() :
		m_time(0),
		m_limitTime(0)
	{
	}

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="limitTime">��������</param>
	Timer(const T limitTime) :
		m_time(0),
		m_limitTime(limitTime)
	{
	}

	// �f�X�g���N�^
	virtual ~Timer() {};

	/// <summary>
	/// �^�C�}�[�̍X�V
	/// </summary>
	/// <param name="deltaTime">�^�C�}�[��1�t���[�����ɍX�V����l</param>
	void Update(const T deltaTime)
	{
		// �X�V
		m_time += deltaTime;

		//if (limitTime_ > 0)
		//{
		//	// �������Ԃ͒����Ȃ�
		//	time_ = (std::min)(time_, limitTime_);
		//}
	}

	// �^�C�}�[�̏�����
	void Reset()
	{
		m_time = 0;
	}

	/// <summary>
	/// �^�C���A�E�g���ǂ���
	/// �������Ԃ�ݒ肵�Ă��Ȃ��ꍇ�A���false��Ԃ�
	/// </summary>
	/// <returns>true : �^�C���A�E�g, false : �^�C����</returns>
	bool IsTimeOut() const
	{
		// �������Ԃ�ݒ肵�Ă��Ȃ��ꍇ�A�^�C���A�E�g����ɕԂ�
		if (m_limitTime <= 0)
		{
			return true;
		}

		return m_time >= m_limitTime;
	}

	/// <summary>
	/// �^�C���̎擾
	/// </summary>
	/// <returns>�^�C��</returns>
	T GetTime() const { return m_time; }

	/// <summary>
	/// �^�C���̐ݒ�
	/// </summary>
	/// <param name="limitTime">�ݒ肵�����^�C��</param>
	void SetTime(const T time) { m_time = time; }

	/// <summary>
	/// �������Ԃ̎擾
	/// </summary>
	/// <returns>��������</returns>
	T GetLimitTime() const { return m_limitTime; }
	
	/// <summary>
	/// �������Ԃ̐ݒ� 
	/// </summary>
	/// <param name="limitTime">�ݒ肵������������</param>
	void SetLimitTime(const T limitTime) { m_limitTime = limitTime; }

private:
	// ���݂̎���
	T m_time;

	// ��������
	T m_limitTime;
};