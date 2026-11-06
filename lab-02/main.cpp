
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
    // 1. Статическая инициализация
    std::cout << "--- 1. Статическая инициализация ---" << std::endl;
    {
        Field staticField(3, 3, 2);
        staticField.PlaceMines();
        staticField.CalculateNeighborMines();
        std::cout << "Поле создано статически" << std::endl;
    }
    std::cout << std::endl;
    // 2. Динамическая инициализация
    std::cout << "--- 2. Динамическая инициализация и работа с указателем и с ссылкой ---" << std::endl;
    Field* dynamicField = new Field(4, 4, 3);
    dynamicField->PlaceMines();
    dynamicField->CalculateNeighborMines();
    // Работа с указателем
    Field* fieldPtr = dynamicField;
    std::cout << "Размер поля через указатель: "
        << fieldPtr->GetRows() << "x" << fieldPtr->GetCols() << std::endl;
    // Работа со ссылкой
    Field& fieldRef = *dynamicField;
    std::cout << "Размер поля через ссылку: "
        << fieldRef.GetRows() << "x" << fieldRef.GetCols() << std::endl;
    delete dynamicField;
    std::cout << std::endl;
    // 3. Демонстрация композиции и агрегации
    std::cout << "--- 3. Композиция , агрегаци и нарушение правила ---" << std::endl;
    // Создаем поле ВНЕ игры (для агрегации)
    std::cout << "Создаем поле во внешнем блоке:" << std::endl;
    Field* gameField = new Field(5, 5, 5);
    {
        std::cout << "\nВходим во внутренний блок..." << std::endl;
        // Агрегация: игра использует поле, созданное вне
        Game* game = new Game(*gameField);
        game->Start();
        // Делаем ход
        std::cout << "\n--- Ход 1: открываем клетку (0,0) ---" << std::endl;
        game->MakeMove(0, 0, false);
        std::cout << "\n--- Ход 2: ставим флаг на клетку (1,1) ---" << std::endl;
        game->MakeMove(1, 1, true);
        // Попытка нарушить правило: открыть клетку с флагом
        std::cout << "\n--- Попытка нарушить правило: открыть клетку с флагом ---" << std::endl;
        game->GetField().GetCell(1, 1).Open();
        delete game;
        std::cout << "Игра уничтожена, но поле продолжает существовать" << std::endl;
    }
    std::cout << "\nВыходим из блока. Проверяем, что поле живо:" << std::endl;
    std::cout << "Размер поля: " << gameField->GetRows() << "x" << gameField->GetCols() << std::endl;
    delete gameField;
    std::cout << std::endl;
    // 4. Массив динамических объектов класса 
    std::cout << "--- 4. Массив динамических объектов класса (Field) ---" << std::endl;
    const int fieldArraySize = 3;
    Field** fieldArray = new Field * [fieldArraySize];
    std::cout << "\n[Массив полей]" << std::endl;
    fieldArray[0] = new Field(3, 3, 2);
    fieldArray[1] = new Field(4, 4, 3);
    fieldArray[2] = new Field(5, 5, 5);

    for (int i = 0; i < fieldArraySize; ++i)
    {
        fieldArray[i]->PlaceMines();
        fieldArray[i]->CalculateNeighborMines();
        std::cout << "  Поле[" << i << "]: "
            << fieldArray[i]->GetRows() << "x" << fieldArray[i]->GetCols()
            << " мин: " << fieldArray[i]->GetMineCount() << std::endl;
    }
    std::cout << "\n  Удаление массива полей..." << std::endl;
    for (int i = fieldArraySize - 1; i >= 0; --i)
    {
        delete fieldArray[i];
    }
    delete[] fieldArray;
    std::cout << std::endl;
    // 5. Разница во времени жизни
    std::cout << "--- 5. Разница во времени жизни ---" << std::endl;
    std::cout << "\nКомпозиция: поле уничтожается вместе с клетками" << std::endl;
    {
        std::cout << "Входим в блок..." << std::endl;
        Field compositeField(3, 3, 1);
        std::cout << "Поле создано" << std::endl;
        std::cout << "Выходим из блока..." << std::endl;
    }
    std::cout << "Поле и все клетки уничтожены автоматически" << std::endl;

    std::cout << "\nАгрегация: поле продолжает жить после уничтожения игры" << std::endl;
    Field* aggregatedField = new Field(4, 4, 2);
    {
        Game tempGame(*aggregatedField);
        std::cout << "Игра создана" << std::endl;
        std::cout << "Выходим из блока..." << std::endl;
    }
    std::cout << "Игра уничтожена, но поле живо: "
        << aggregatedField->GetRows() << "x" << aggregatedField->GetCols() << std::endl;
    delete aggregatedField;

    std::cout << "\n=== Демонстрация завершена ===" << std::endl;

    return 0;
}