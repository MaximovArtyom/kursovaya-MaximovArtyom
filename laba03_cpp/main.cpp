
#include "Cell.hpp"
#include "Field.hpp"
#include "Game.hpp"
#include <iostream>
#include <locale>

int main()
{
    using namespace minesweeper;
    setlocale(LC_ALL, "");
    std::cout << "=== Демонстрация работы классов Сапёр ===" << std::endl;
   
    std::cout << "--- 1. std::unique_ptr ---" << std::endl;
    {
        auto field = std::make_unique<Field>(3, 3, 2);
        field->PlaceMines();
        field->CalculateNeighborMines();
        std::cout << "Поле создано" << std::endl;
        std::cout << "Передаем владение через std::move" << std::endl;
        auto anoField = std::move(field);
        std::cout << "Владение передано через std::move\n";
        std::cout << "field пуст? " << (field == nullptr ? "да" : "нет") << "\n";
        std::cout << "anotherField валиден? " << (anoField != nullptr ? "да" : "нет") << "\n";
    }
    std::cout << "Блок завершён. Поле и клетки уничтожены без delete.\n\n";
   
    std::cout << "--- 2. shared_ptr ---" << std::endl;
    auto sharedField = std::make_shared<Field>(10, 10, 15);
    std::cout << "Создано поле. Счётчик владельцев: " << sharedField.use_count() << "\n";

    {
        auto sharedFieldCopy = sharedField;  
        std::cout << "Создана копия shared_ptr. Счётчик: " << sharedField.use_count() << "\n";

        Game game(sharedFieldCopy);
        std::cout << "Игра создана. Счётчик: " << sharedField.use_count() << "\n";
    } 
    std::cout << "Копия уничтожена. Счётчик: " << sharedField.use_count() << "\n";
    std::cout << "Поле всё ещё живо, счётчик > 0.\n\n";

    std::cout << "=== 3. weak_ptr: агрегация ===\n";
    auto aggregatedField = std::make_shared<Field>(8, 8, 10);
    std::cout << "Создано поле для агрегации. Счётчик: " << aggregatedField.use_count() << "\n";

    Game game(aggregatedField); 
    std::cout << "Игра создана (хранит weak_ptr). Счётчик поля: " << aggregatedField.use_count() << "\n";

    if (auto fieldPtr = aggregatedField) {
        std::cout << "Поле живо, размеры: " << fieldPtr->GetRows() << "x" << fieldPtr->GetCols() << "\n";
    }

    aggregatedField.reset();
    std::cout << "Последний владелец уничтожен (reset).\n";

    std::cout << "Поле уничтожено. Счётчик: " << aggregatedField.use_count() << "\n\n";

    std::cout << "=== 4. Проверка правила ===\n";
    auto ruleField = std::make_unique<Field>(3, 3, 999);  
    std::cout << "Итоговый размер: " << ruleField->GetRows() << "x" << ruleField->GetCols() << "\n";
    std::cout << "Фактическое количество мин: " << ruleField->GetMineCount() << "\n\n";

    std::cout << "=== 5. Массив unique_ptr ===\n";
    std::vector<std::unique_ptr<Field>> fieldArray;
    for (int i = 0; i < 3; ++i) {
        fieldArray.push_back(std::make_unique<Field>(4, 4, 2));
        std::cout << "Создано поле [" << i << "]: "
            << fieldArray[i]->GetRows() << "x" << fieldArray[i]->GetCols() << "\n";
    }
    std::cout << "Массив содержит " << fieldArray.size() << " полей\n";
    fieldArray.clear();
    std::cout << "Массив очищен. Все поля уничтожены.\n\n";

    std::cout << "\n=== Демонстрация завершена ===" << std::endl;

    return 0;
}