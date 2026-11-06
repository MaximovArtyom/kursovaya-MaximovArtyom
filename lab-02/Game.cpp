
#include "Game.hpp"
#include <iostream>

namespace minesweeper
{

    Game::Game(Field& field)
        : m_field{ field }
    {
        std::cout << "[" << TAG << "] Game создана " << std::endl;
    }

    Game::~Game()
    {
        std::cout << "[" << TAG << "] Game уничтожена" << std::endl;
    }

    void Game::Start()
    {
        m_field.PlaceMines();
        m_field.CalculateNeighborMines();
        std::cout << "[" << TAG << "] Партия началась на поле "
            << m_field.GetRows() << "x" << m_field.GetCols()
            << " с " << m_field.GetMineCount() << " минами" << std::endl;
    }

    void Game::MakeMove(Field::SizeType row, Field::SizeType col, bool setFlag)
    {
        if (m_gameOver)
        {
            std::cout << "[" << TAG << "] Ошибка: игра уже завершена" << std::endl;
            return;
        }

        if (setFlag)
        {
            m_field.FlagCell(row, col);
        }
        else
        {
            m_field.OpenCell(row, col);
            if (m_field.GetCell(row, col).HasMine())
            {
                m_gameOver = true;
                std::cout << "[" << TAG << "] Поражение!" << std::endl;
            }
        }
    }

    void Game::CheckVictory()
    {
        m_victory = true;
        std::cout << "[" << TAG << "] Победа!" << std::endl;
    }

}