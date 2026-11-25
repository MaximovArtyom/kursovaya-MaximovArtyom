#pragma once
#include <memory>
#include <chrono>
#include "BaseGame.hpp"

#pragma once

namespace minesweeper
{
    class AdventureGame : public BaseGame
    {
    private:
        int m_level;
        int m_timeLimit;
        int m_timeRemaining;
    public:
        AdventureGame(std::shared_ptr<Field> field,int level, int timeLimit);
        ~AdventureGame() override;
        AdventureGame& operator=(const AdventureGame& other);
        AdventureGame(const AdventureGame& other);
        AdventureGame(AdventureGame&& other) noexcept;

        bool CheckVictory() const override;
        void MakeMove(int row, int col, bool setFlag) override;
        void Start() override;
        std::string Describe() const override;
        std::unique_ptr<BaseGame> Clone() const override;

        int GetLevel() const { return m_level; }
        int GetTimeLimit() const{ return m_timeLimit; }
    };
}