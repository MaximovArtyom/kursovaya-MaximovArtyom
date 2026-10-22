#pragma once

#include <cstdint>
#include <string>
#include <string_view>

namespace minesweeper
{

    enum class CellState
    {
        eClosed = 0,
        eOpened = 1,
        eFlagged = 2,
    };

    class Cell
    {
    public:
        using RowType = std::int32_t;
        using ColType = std::int32_t;
        using MineCountType = std::uint8_t;

    private:
        static constexpr auto TAG = "Cell";

        RowType m_row{ 0 };
        ColType m_col{ 0 };
        bool m_hasMine{ false };
        CellState m_state{ CellState::eClosed };
        MineCountType m_neighborMineCount{ 0 };

    public:
        Cell(RowType row, ColType col, bool hasMine);

        Cell() = delete;
        Cell(const Cell&) = delete;
        Cell(Cell&&) = delete;
        Cell& operator=(const Cell&) = delete;
        Cell& operator=(Cell&&) = delete;
        ~Cell() = default;

        void Open();
        void SetFlag();
        void RemoveFlag();

        [[nodiscard]] auto GetRow() const
        {
            return m_row;
        }

        [[nodiscard]] auto GetCol() const
        {
            return m_col;
        }

        [[nodiscard]] auto HasMine() const
        {
            return m_hasMine;
        }

        [[nodiscard]] auto GetState() const
        {
            return m_state;
        }

        [[nodiscard]] auto GetNeighborMineCount() const
        {
            return m_neighborMineCount;
        }
        void SetNeighborMineCount(MineCountType count);
    };

}


