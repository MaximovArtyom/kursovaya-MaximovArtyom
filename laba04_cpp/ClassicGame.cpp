#include "ClassicGame.hpp"
#include <iostream>

namespace minesweeper
{
	const std::vector<std::pair<int, int>> ClassicGame::m_presetFields =
	{
		{8,8},
		{15,15},
		{18,30},
		{20,40}
	};
    ClassicGame::ClassicGame(std::shared_ptr<Field> field, int selectedFieldIndex)
        : BaseGame("Classic",std::move(field))
        , m_selectedFieldIndex(selectedFieldIndex)
    {
        std::cout << "[ClassicGame] Создана классическая игра, выбрано поле #"<< m_selectedFieldIndex << std::endl;
    }

    ClassicGame::~ClassicGame()
    {
        std::cout << "[ClassicGame] Уничтожена классическая игра" << std::endl;
    }

    ClassicGame::ClassicGame(const ClassicGame& other)
        : BaseGame(other)
        , m_selectedFieldIndex(other.m_selectedFieldIndex)
    {
        std::cout << "[ClassicGame] Скопирована классическая игра" << std::endl;
    }

    ClassicGame::ClassicGame(ClassicGame&& other) noexcept
        : BaseGame(std::move(other))
        , m_selectedFieldIndex(other.m_selectedFieldIndex)
    {
        other.m_selectedFieldIndex = 0;
        std::cout << "[ClassicGame] Перемещена классическая игра" << std::endl;
    }

    void ClassicGame::Start()
    {
        std::cout << "[ClassicGame] Начало классической игры на поле #"<< m_selectedFieldIndex << std::endl;
        m_field->PlaceMines();
        m_field->CalculateNeighborMines();
        m_gameOver = false;
        m_victory = false;
    }

    void ClassicGame::MakeMove(Field::SizeType row, Field::SizeType col, bool setFlag)
    {
        if (m_gameOver)
        {
            std::cout << "[ClassicGame] Ошибка: игра уже завершена" << std::endl;
            return;
        }

        if (setFlag)
        {
            m_field->FlagCell(row, col);
        }
        else
        {
            m_field->OpenCell(row, col);
            if (m_field->GetCell(row, col).HasMine())
            {
                m_gameOver = true;
                m_victory = false;
                std::cout << "[ClassicGame] Поражение! Подорвались на мине!" << std::endl;
            }
        }

        CheckVictory();
    }

    bool ClassicGame::CheckVictory() const
    {
        return m_victory;
    }

    std::string ClassicGame::Describe() const
    {
        return Header() + ", классический режим, поле #" + std::to_string(m_selectedFieldIndex);
    }

    std::unique_ptr<BaseGame> ClassicGame::Clone() const
    {
        return std::make_unique<ClassicGame>(*this);
    }

}