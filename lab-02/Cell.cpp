#include "Cell.hpp"
#include <iostream>

namespace minesweeper
{

    Cell::Cell(RowType row, ColType col, bool hasMine)
        : m_row{ row }
        , m_col{ col }
        , m_hasMine{ hasMine }
    {
        std::cout << "Cell(" << m_row << "," << m_col << ") создан" << std::endl;
    }

    void Cell::Open()
    {
        if (m_state == CellState::eFlagged)
        {
            std::cout << "[" << TAG << "] Ошибка: нельзя открыть клетку с флагом" << std::endl;
            return;
        }
        if (m_state == CellState::eOpened)
        {
            std::cout << "[" << TAG << "] Клетка уже открыта" << std::endl;
            return;
        }

        m_state = CellState::eOpened;
        std::cout << "[" << TAG << "] Клетка(" << m_row << "," << m_col << ") открыта";
        if (m_hasMine)
        {
            std::cout << " — БУМ! Мина!" << std::endl;
        }
        else
        {
            std::cout << ", соседних мин: " << static_cast<int>(m_neighborMineCount) << std::endl;
        }
    }

    void Cell::SetFlag()
    {
        if (m_state == CellState::eOpened)
        {
            std::cout << "[" << TAG << "] Ошибка: нельзя поставить флаг на открытую клетку" << std::endl;
            return;
        }
        m_state = CellState::eFlagged;
        std::cout << "[" << TAG << "] Флаг поставлен на клетку(" << m_row << "," << m_col << ")" << std::endl;
    }

    void Cell::RemoveFlag()
    {
        if (m_state == CellState::eFlagged)
        {
            m_state = CellState::eClosed;
            std::cout << "[" << TAG << "] Флаг снят с клетки(" << m_row << "," << m_col << ")" << std::endl;
        }
    }

    void Cell::SetNeighborMineCount(MineCountType count)
    {
        if (count > 8)
        {
            std::cout << "[" << TAG << "] Ошибка: число соседних мин должно быть от 0 до 8" << std::endl;
            return;
        }
        m_neighborMineCount = count;
    }

}