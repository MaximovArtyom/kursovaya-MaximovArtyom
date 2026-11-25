#include "AdventureGame.hpp"
#include <iostream>

namespace minesweeper
{
    AdventureGame::AdventureGame(std::shared_ptr<Field> field, int level, int timeLimit)
        : BaseGame("Adventure", std::move(field))
        , m_level(level)
        , m_timeLimit(timeLimit)
        , m_timeRemaining(timeLimit)  
    {  
        std::cout << "[AdventureGame ctor] уровень " << m_level << ", лимит: " << m_timeLimit << " ходов\n";
    }

    AdventureGame::~AdventureGame()
    {
        std::cout << "[AdventureGame dtor] уровень " << m_level << "\n";
    }

    AdventureGame::AdventureGame(const AdventureGame& other)
        : BaseGame(other)
        , m_level(other.m_level)
        , m_timeLimit(other.m_timeLimit)
        , m_timeRemaining(other.m_timeRemaining)
    {
        m_field = std::make_shared<Field>(other.m_field->GetRows(), other.m_field->GetCols(), other.m_field->GetMineCount());
        std::cout << "[AdventureGame copy ctor] (глубокая копия)\n";
    }

    AdventureGame& AdventureGame::operator=(const AdventureGame& other)
    {
        if (this == &other) return *this;
        BaseGame::operator=(other);
        m_level = other.m_level;
        m_timeLimit = other.m_timeLimit;
        m_timeRemaining = other.m_timeRemaining;
        return *this;
    }

    void AdventureGame::Start()
    {
        std::cout << "[AdventureGame] Начало уровня " << m_level << "\n";
        m_field->PlaceMines();
        m_field->CalculateNeighborMines();
        m_gameOver = false;
        m_victory = false;
        m_timeRemaining = m_timeLimit;
    }

    void AdventureGame::MakeMove(int row, int col, bool setFlag)
    {
        if (m_gameOver) return;

        m_timeRemaining--;
        if (m_timeRemaining <= 0) {
            m_gameOver = true;
            m_victory = false;
            std::cout << "[AdventureGame] Время вышло!\n";
            return;
        }

        if (setFlag) {
            m_field->FlagCell(row, col);
        }
        else {
            m_field->OpenCell(row, col);
            if (m_field->GetCell(row, col).HasMine()) {
                m_gameOver = true;
                m_victory = false;
                std::cout << "[AdventureGame] Поражение!\n";
            }
        }
        CheckVictory();
    }

    bool AdventureGame::CheckVictory() const { return m_victory; }

    std::string AdventureGame::Describe() const
    {
        return Header() + ", уровень " + std::to_string(m_level) + ", осталось ходов: " + std::to_string(m_timeRemaining);
    }

    std::unique_ptr<BaseGame> AdventureGame::Clone() const
    {
        return std::make_unique<AdventureGame>(*this);
    }
}