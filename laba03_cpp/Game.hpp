
#pragma once
#include <memory>
#include "Field.hpp"

namespace minesweeper
{
    class Game
    {
    private:
        static constexpr auto TAG = "Game";

        std::weak_ptr<Field> m_field;
        bool m_gameOver{ false };
        bool m_victory{ false };

    public:
        Game(std::shared_ptr<Field> field);
        ~Game();
        void Start();
        void MakeMove(Field::SizeType row, Field::SizeType col, bool setFlag);
        void CheckVictory();

        [[nodiscard]] auto IsGameOver() const
        {
            return m_gameOver;
        }

        [[nodiscard]] auto IsVictory() const
        {
            return m_victory;
        }

        std::shared_ptr<Field> GetField() const { return m_field.lock(); }
    };

}