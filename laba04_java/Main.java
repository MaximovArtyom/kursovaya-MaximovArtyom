package minesweeper;

import java.util.ArrayList;
import java.util.List;

public class Main
{
    public static void main(String[] args)
    {
        demoPolymorphism();
        demoClone();
        demoShallowCopy();
        demoDeepCopy();
        demoEqualsAndHashCode();
        demoThis();

    }

    // === 1. Полиморфный массив ===
    private static void demoPolymorphism()
    {
        System.out.println("\n=== 1. Полиморфный массив ===");

        BaseGame[] games = new BaseGame[3];
        games[0] = new AdventureGame(new Field(5, 5, 2), 1, 10);
        games[1] = new ClassicGame(new Field(9, 9, 10), 0);
        games[2] = new ClassicGame(new Field(16, 16, 40), 1);

        for (BaseGame g : games) {
            g.start();
            System.out.println(g.describe() + " -> " + g.getStatus());
        }
    }

    // === 2. Клонирование через базовый класс ===
    private static void demoClone()
    {
        System.out.println("\n=== 2. Клонирование (Clone) ===");

        AdventureGame orig = new AdventureGame(new Field(5, 5, 2), 1, 10);
        BaseGame clone = orig.clone();

        System.out.println("Оригинал: " + orig.describe());
        System.out.println("Копия:    " + clone.describe());
        System.out.println("Разные объекты в памяти? " + (orig != clone));
    }

    // === 3. Поверхностная копия ===
    private static void demoShallowCopy()
    {
        System.out.println("\n=== 3. Поверхностная копия (Shallow Copy) ===");

        // Создаём поле и сохраняем ссылку в двух местах
        Field originalField = new Field(3, 3, 1);
        Field copyField = originalField;  // копируется ССЫЛКА, не объект

        System.out.println("originalField == copyField? " + (originalField == copyField));
        System.out.println("Это ОДИН объект в памяти");

        // Меняем через одну ссылку — видно через другую
        originalField.flagCell(0, 0);
        System.out.println("После изменения через originalField, copyField тоже изменился:");
        System.out.println("  copyField.getCell(0,0).getState() = " + copyField.getCell(0, 0).getState());
    }

    // === 4. Глубокая копия ===
    private static void demoDeepCopy()
    {
        System.out.println("\n=== 4. Глубокая копия (Deep Copy) ===");

        AdventureGame orig = new AdventureGame(new Field(5, 5, 2), 1, 10);
        orig.start();

        // Конструктор копирования создаёт НОВОЕ поле внутри
        AdventureGame copy = new AdventureGame(orig);

        System.out.println("Поле оригинала: " + orig.getField());
        System.out.println("Поле копии:    " + copy.getField());
        System.out.println("Разные поля? " + (orig.getField() != copy.getField()));

        // Меняем через копию — оригинал не тронут
        copy.getField().flagCell(0, 0);
        System.out.println("После copy.field.flagCell(0,0):");
        System.out.println("  orig.field.getCell(0,0).getState() = " + orig.getField().getCell(0, 0).getState());
        System.out.println("  copy.field.getCell(0,0).getState() = " + copy.getField().getCell(0, 0).getState());
    }

    // === 5. Сравнение equals и hashCode ===
    private static void demoEqualsAndHashCode()
    {
        System.out.println("\n=== 5. Сравнение equals и hashCode ===");

        AdventureGame g1 = new AdventureGame(new Field(5, 5, 2), 1, 10);
        AdventureGame g2 = new AdventureGame(new Field(5, 5, 2), 1, 10);
        AdventureGame g3 = g1;  // та же ссылка

        System.out.println("g1 == g2 (ссылки): " + (g1 == g2) + " (разные объекты)");
        System.out.println("g1 == g3 (ссылки): " + (g1 == g3) + " (один и тот же объект)");
        System.out.println("g1.equals(g2): " + g1.equals(g2) + " (сравнение по содержимому)");
        System.out.println("g1.equals(g3): " + g1.equals(g3) + " (та же ссылка)");
        System.out.println("g1.hashCode() == g2.hashCode(): " + (g1.hashCode() == g2.hashCode()));
        System.out.println("g1.hashCode() == g3.hashCode(): " + (g1.hashCode() == g3.hashCode()));
    }

    // === 6. Использование this ===
    private static void demoThis()
    {
        System.out.println("\n=== 6. Использование this ===");
        AdventureGame game = new AdventureGame(new Field(5, 5, 2), 1, 10);
        ClassicGame classic = new ClassicGame(new Field(9, 9, 10), 0);
        BaseGame game_copy = game.Save(classic);
        game_copy.Save(classic);
    }

}
