#include "BaseGame.hpp"
#include "AdventureGame.hpp"
#include "ClassicGame.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <string>


namespace minesweeper
{
    struct SharedFieldDemo
    {
        std::shared_ptr<Field> field;
    };
} 

using namespace minesweeper;

int main() 
{
    setlocale(LC_ALL, "RUS");
    std::cout << "=== Тест иерархии классов Сапёр (ЛР №4) ===\n";

    auto field1 = std::make_shared<Field>(5, 5, 3);
    AdventureGame adventure{ field1, 1, 10 };

    auto field2 = std::make_shared<Field>(9, 9, 10);
    ClassicGame classic{ field2, 0 };

    std::cout << "\n=== Описания ===\n";
    std::cout << adventure.Describe() << "\n";
    std::cout << classic.Describe() << "\n";

    std::cout << "\n=== Статусы игр ===\n";
    adventure.Start();
    classic.Start();
    std::cout << "Adventure: " << adventure.Describe() << "\n";
    std::cout << "Classic: " << classic.Describe() << "\n";

    std::cout << "\n=== 1. Создание полиморфного массива ===\n";
    std::vector<std::unique_ptr<BaseGame>> games;

    games.push_back(std::make_unique<AdventureGame>(std::make_shared<Field>(5, 5, 2), 2, 5));
    games.push_back(std::make_unique<ClassicGame>(std::make_shared<Field>(9, 9, 10), 0));
    games.push_back(std::make_unique<ClassicGame>(std::make_shared<Field>(16, 16, 40), 1));

    for (const auto& game : games)
    {
        game->Start();
        std::cout  << " Статус: " << game->Describe() << "\n";
    }

    std::cout << "\n=== 2. Демонстрация Clone() ===\n";
    std::unique_ptr<BaseGame> clone = games[0]->Clone();
    std::cout << "Оригинал: " << games[0]->Describe() << "\n";
    std::cout << "Копия:    " << clone->Describe() << "\n";

   
    if (games[0].get() != clone.get())
    {
        std::cout << "Успех: это два разных объекта в памяти \n";
    }

    std::cout << "\n=== 3. Поверхностная копия (Shallow Copy) ===\n";
    SharedFieldDemo originalShallow;
    originalShallow.field = std::make_shared<Field>(3, 3, 1);

    SharedFieldDemo copyShallow = originalShallow; 

    std::cout << "Адрес поля в оригинале: " << originalShallow.field.get() << "\n";
    std::cout << "Адрес поля в копии:     " << copyShallow.field.get() << "\n";

    if (originalShallow.field.get() == copyShallow.field.get())
    {
        std::cout << "Эти оба объекта ссылаются на ОДНО и то же поле !(поверхностная копия)\n";
    }

    std::cout << "\n=== 4. Глубокая копия ===\n";
    
    AdventureGame deepOriginal{ std::make_shared<Field>(5, 5, 2), 1, 5 };
    deepOriginal.Start();
    AdventureGame deepCopy = deepOriginal;
    std::cout << "Адрес игры Оригинал: " << &deepOriginal << "\n";
    std::cout << "Адрес игры Копия:    " << &deepCopy << "\n";

    if (deepOriginal.GetField().get() != deepCopy.GetField().get())
    {
        std::cout << "Успех: поля внутри игр разные (глубокая копия)\n";
    }
    else
    {
        std::cout << "Примечание: поля одинаковые, но сами объекты игр разные.\n";
    }

    std::cout << "\n=== 5. Работа со строками (find, substr, сравнение) ===\n";
    std::string gameDescription = "Adventure_Mode_Level_3";
    std::cout << "Полное описание: " << gameDescription << "\n";

    size_t pos = gameDescription.find("_");
    if (pos != std::string::npos)
    {
        std::cout << "Символ '_' найден на позиции: " << pos << "\n";
        std::string prefix = gameDescription.substr(0, pos);
        std::cout << "Тип игры (подстрока): " << prefix << "\n";

        if (prefix == "Adventure")
        {
            std::cout << "Сравнение прошло успешно: это приключенческий режим\n";
        }
    }

    std::cout << "\n=== 6. Использование this для передачи объекта ===\n";
    AdventureGame adventure1{ field1, 1, 10 };
    ClassicGame classic1{ field2, 0 };
    std::cout << "Вызов метода, который использует *this:\n";
    adventure1.Save(classic1);

    std::cout << "\n=== Конец программы ===\n";
    return 0;
}