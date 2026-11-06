
#include "Game.hpp"
#include <iostream>

namespace minesweeper
{
    Game::Game(std::shared_ptr<Field> field)
        : m_field(field)

    {
        std::cout << "[" << TAG << "] Game создана" << std::endl;
    }

    Game::~Game()
    {
        std::cout << "[" << TAG << "] Game уничтожена" << std::endl;
    }

    void Game::Start()
    {
        
        if (auto fieldPtr = m_field.lock()) {
            fieldPtr->PlaceMines();
            fieldPtr->CalculateNeighborMines();
            std::cout << "[" << TAG << "] Партия началась на поле "
                << fieldPtr->GetRows() << "x" << fieldPtr->GetCols()
                << " с " << fieldPtr->GetMineCount() << " минами" << std::endl;
        }
        else {
            std::cout << "[" << TAG << "] Ошибка: поле уже уничтожено!" << std::endl;
        }
    }

    void Game::MakeMove(Field::SizeType row, Field::SizeType col, bool setFlag)
    {
        if (m_gameOver) {
            std::cout << "[" << TAG << "] Ошибка: игра уже завершена" << std::endl;
            return;
        }

        if (auto fieldPtr = m_field.lock()) {
            if (setFlag) {
                fieldPtr->FlagCell(row, col);
            }
            else {
                fieldPtr->OpenCell(row, col);
                if (fieldPtr->GetCell(row, col).HasMine()) {
                    m_gameOver = true;
                    std::cout << "[" << TAG << "] Поражение!" << std::endl;
                }
            }
        }
        else {
            std::cout << "[" << TAG << "] Ошибка: поле уже уничтожено!" << std::endl;
            m_gameOver = true;
        }
    }

    void Game::CheckVictory()
    {
        m_victory = true;
        std::cout << "[" << TAG << "] Победа!" << std::endl;
    }

}