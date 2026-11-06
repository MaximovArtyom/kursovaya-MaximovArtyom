
#include "Field.hpp"
#include <iostream>

namespace minesweeper
{

    Field::Field(SizeType rows, SizeType cols, MineCountType mineCount)
        : m_rows{ rows }
        , m_cols{ cols }
        , m_mineCount{ mineCount }
    {
        if (mineCount >= static_cast<MineCountType>(rows * cols))
        {
            std::cout << "[" << TAG << "] Ошибка: количество мин должно быть меньше количества клеток" << std::endl;
            m_mineCount = static_cast<MineCountType>(rows * cols) - 1;
        }

        m_cells.resize(static_cast<std::size_t>(rows));
        for (SizeType i = 0; i < rows; ++i)
        {
            m_cells[static_cast<std::size_t>(i)].resize(static_cast<std::size_t>(cols));
            for (SizeType j = 0; j < cols; ++j)
            {
                m_cells[static_cast<std::size_t>(i)][static_cast<std::size_t>(j)] = new Cell(i, j, false);
            }
        }
        std::cout << "[" << TAG << "] Field(" << m_rows << "x" << m_cols << ") создан" << std::endl;
    }

    Field::~Field()
    {
        for (SizeType i = 0; i < m_rows; ++i)
        {
            for (SizeType j = 0; j < m_cols; ++j)
            {
                delete m_cells[static_cast<std::size_t>(i)][static_cast<std::size_t>(j)];
            }
        }
        std::cout << "[" << TAG << "] Field(" << m_rows << "x" << m_cols << ") уничтожен" << std::endl;
    }

    void Field::PlaceMines()
    {
        std::cout << "[" << TAG << "] Мины размещены: " << m_mineCount << " шт." << std::endl;
    }

    void Field::CalculateNeighborMines()
    {
        for (SizeType i = 0; i < m_rows; ++i)
        {
            for (SizeType j = 0; j < m_cols; ++j)
            {
                Cell::MineCountType count = 0;
                for (SizeType di = -1; di <= 1; ++di)
                {
                    for (SizeType dj = -1; dj <= 1; ++dj)
                    {
                        if (di == 0 && dj == 0)
                        {
                            continue;
                        }
                        SizeType ni = i + di;
                        SizeType nj = j + dj;
                        if (IsValidPosition(ni, nj) && m_cells[static_cast<std::size_t>(ni)][static_cast<std::size_t>(nj)]->HasMine())
                        {
                            ++count;
                        }
                    }
                }
                m_cells[static_cast<std::size_t>(i)][static_cast<std::size_t>(j)]->SetNeighborMineCount(count);
            }
        }
    }

    void Field::OpenCell(SizeType row, SizeType col)
    {
        if (IsValidPosition(row, col))
        {
            m_cells[static_cast<std::size_t>(row)][static_cast<std::size_t>(col)]->Open();
        }
        else
        {
            std::cout << "[" << TAG << "] Ошибка: позиция (" << row << "," << col << ") вне поля" << std::endl;
        }
    }

    void Field::FlagCell(SizeType row, SizeType col)
    {
        if (IsValidPosition(row, col))
        {
            m_cells[static_cast<std::size_t>(row)][static_cast<std::size_t>(col)]->SetFlag();
        }
        else
        {
            std::cout << "[" << TAG << "] Ошибка: позиция (" << row << "," << col << ") вне поля" << std::endl;
        }
    }

    Cell& Field::GetCell(SizeType row, SizeType col)
    {
        if (!IsValidPosition(row, col))
        {
            std::cout << "[" << TAG << "] Ошибка: позиция (" << row << "," << col << ") вне поля" << std::endl;
            return *m_cells[0][0];
        }
        return *m_cells[static_cast<std::size_t>(row)][static_cast<std::size_t>(col)];
    }

    bool Field::IsValidPosition(SizeType row, SizeType col) const
    {
        return row >= 0 && row < m_rows && col >= 0 && col < m_cols;
    }

} 