
#pragma once
#include <string>
#include <string_view>
#include <memory>
#include "Field.hpp"

namespace minesweeper
{
    class BaseGame
    {
    public:
        BaseGame(std::string_view title, std::shared_ptr<Field> field);
        BaseGame(const BaseGame& other);
        BaseGame& operator=(const BaseGame& other);

        BaseGame(BaseGame&&) noexcept = default;
        BaseGame& operator=(BaseGame&&) noexcept = default;

        virtual ~BaseGame();

        [[nodiscard]] std::string_view GetTitle() const;
        [[nodiscard]] std::shared_ptr<Field> GetField() const;
        [[nodiscard]] bool IsGameOver() const;
        [[nodiscard]] bool IsVictory() const;
        [[nodiscard]] int GetGameNumber() const;

        void Save(const BaseGame& game) const;
        virtual std::string Describe() const;
        virtual void Start() = 0;
        virtual bool CheckVictory() const = 0;
        virtual void MakeMove(int row, int col, bool setFlag) = 0;
        virtual std::unique_ptr<BaseGame> Clone() const = 0;
        static int NextGameNumber();
        static int GetGameCount();
        static constexpr int MAX_LEVEL = 10;
    private:
        std::string m_title;
        int m_gameNumber{};                    
        inline static int m_gameCounter{ 0 };
    protected:
        std::shared_ptr<Field> m_field;
        bool m_gameOver{ false };
        bool m_victory{ false };
        std::string Header() const;
    };
}