#pragma once

#include "BaseGame.hpp"
#include <vector>

namespace minesweeper
{

    class ClassicGame : public BaseGame
    {
    private:
        int m_selectedFieldIndex;
        static const std::vector<std::pair<int, int>> m_presetFields;  

    public:
        ClassicGame(std::shared_ptr<Field> field, int selectedFieldIndex);
        ~ClassicGame() override;

        ClassicGame(const ClassicGame& other);
        ClassicGame(ClassicGame&& other) noexcept;

        bool CheckVictory() const override;
        void Start() override;
        void MakeMove(int row, int col, bool setFlag) override;
        std::string Describe() const override;
        std::unique_ptr<BaseGame> Clone() const override;

        int GetSelectedFieldIndex() const { return m_selectedFieldIndex; }
       
    };

}



