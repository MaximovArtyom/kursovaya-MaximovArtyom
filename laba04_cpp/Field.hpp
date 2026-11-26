#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <string_view>
#include <memory>
#include "Cell.hpp"

namespace minesweeper
{

    class Field
    {
    public:
        using SizeType = std::int32_t;
        using MineCountType = std::uint32_t;

    private:
        static constexpr auto TAG = "Field";

        SizeType m_rows{ 0 };
        SizeType m_cols{ 0 };
        MineCountType m_mineCount{ 0 };
        std::vector<std::vector<std::unique_ptr<Cell>>> m_cells;  
    public:
        Field(SizeType rows, SizeType cols, MineCountType mineCount);
        ~Field();

        void PlaceMines();
        void CalculateNeighborMines();
        void OpenCell(SizeType row, SizeType col);
        void FlagCell(SizeType row, SizeType col);

        [[nodiscard]] auto GetRows() const
        {
            return m_rows;
        }

        [[nodiscard]] auto GetCols() const
        {
            return m_cols;
        }

        [[nodiscard]] auto GetMineCount() const
        {
            return m_mineCount;
        }

        [[nodiscard]] Cell& GetCell(SizeType row, SizeType col);

    private:
        [[nodiscard]] bool IsValidPosition(SizeType row, SizeType col) const;
    };

} 