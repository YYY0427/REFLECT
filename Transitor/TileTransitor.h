#pragma once
#include "TransitorBase.h"
#include <vector>
#include <random>

/// <summary>
/// ��ʐ؂�ւ����o
/// �^�C����ɉ�ʂ��؂�ւ��
/// </summary>
class TileTransitor final : public TransitorBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="cellSize">�^�C���̑傫��</param>
    /// <param name="interval">�؂�ւ�鎞��</param>
    TileTransitor(int cellSize = 50, int interval = 60);

    // �X�V
    void Update() override final;

    // �`��
    void Draw() override final;

private:
    // �^�C����XY�C���f�b�N�X
    struct XYIdx 
    {
        int xIdx, yIdx;
    };

private:
    // �����G���W��
    std::mt19937 m_mt;

    // �^�C����XY�C���f�b�N�X�e�[�u��
    std::vector<XYIdx> m_tiles;

    // �^�C���̑傫��
    int m_cellSize;
};