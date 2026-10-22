
#pragma once

#include "Field.hpp"

namespace minesweeper
{
    class Game
    {
    private:
        static constexpr auto TAG = "Game";

        Field& m_field;
        bool m_gameOver{ false };
        bool m_victory{ false };

    public:
        explicit Game(Field& field);

        Game() = delete;
        Game(const Game&) = delete;
        Game(Game&&) = delete;
        Game& operator=(const Game&) = delete;
        Game& operator=(Game&&) = delete;
        ~Game();

        // Содержательные методы
        void Start();
        void MakeMove(Field::SizeType row, Field::SizeType col, bool setFlag);
        void CheckVictory();

        // Геттеры
        [[nodiscard]] auto IsGameOver() const
        {
            return m_gameOver;
        }

        [[nodiscard]] auto IsVictory() const
        {
            return m_victory;
        }

        [[nodiscard]] Field& GetField()
        {
            return m_field;
        }
    };

}