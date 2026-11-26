
#include "BaseGame.hpp"
#include <iostream>

namespace minesweeper
{
    BaseGame::BaseGame(std::string_view title, std::shared_ptr<Field> field)
        : m_title{ title }
        , m_field{ std::move(field) }
    {
        std::cout << "[BaseGame ctor] " << GetTitle() <<"\n";
    }

    BaseGame::BaseGame(const BaseGame& other)
        : m_title{ other.m_title }
        , m_gameOver{ other.m_gameOver }
        , m_victory{ other.m_victory }
        , m_field{ std::make_shared<Field>(
            other.m_field->GetRows(),
            other.m_field->GetCols(),
            other.m_field->GetMineCount()
        ) }
    {
        std::cout << "[BaseGame copy ctor] " << m_title << "\n";
    }

    BaseGame& BaseGame::operator=(const BaseGame& other)
    {
        if (this == &other)
        {
            return *this;
        }

        m_title = other.m_title;
        m_gameOver = other.m_gameOver;
        m_victory = other.m_victory;
        m_field = std::make_shared<Field>(
            other.m_field->GetRows(),
            other.m_field->GetCols(),
            other.m_field->GetMineCount()
        );

        return *this;
    }

    std::string_view BaseGame::GetTitle() const { return m_title; }
    std::shared_ptr<Field> BaseGame::GetField() const { return m_field; }
    bool BaseGame::IsGameOver() const { return m_gameOver; }
    bool BaseGame::IsVictory() const { return m_victory; }

    int BaseGame::NextGameNumber()
    {
        return ++m_gameCounter;
    }

    int BaseGame::GetGameCount()
    {
        return m_gameCounter;
    }

    int BaseGame::GetGameNumber() const { return m_gameNumber; }

    void BaseGame::Save(const BaseGame& other) const
    {
        std::cout << "  [this] Игра \"" << this->GetTitle()<< "\" передана в архив\n";
    }

    std::string BaseGame::Header() const
    {
        return m_title + " [Поле: " + std::to_string(m_field->GetRows()) +
            "x" + std::to_string(m_field->GetCols()) + "]";
    }

    std::string BaseGame::Describe() const
    {
        if (m_victory) {
            return Header() + " (Победа)";
        }
        if (m_gameOver) {
            return Header() + " (Поражение)";
        }
        return Header() + " (В процессе)";
    }
    BaseGame::~BaseGame()
    {
        std::cout << "[BaseGame dtor] " << m_title << "\n";
    }
}