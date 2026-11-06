package minesweeper;

import java.lang.ref.WeakReference;

public class Main {
    public static void main(String[] args) {
        demoComposition();
        demoAggregation();
        demoRuleCheck();
        demoReferencesAndCopies();
        demoAutoCloseable();
        demoGarbageCollector();
    }

    private static void demoComposition() {
        System.out.println("========= 1. Композиция: Field создаёт Cell =========");
        field Field = new field(5, 5, 3);
        Field.placeMines();
        Field.calculateNeighborMines();
        System.out.println("Поле создано: " + Field);
        System.out.println("(Поле и его клетки будут уничтожены GC когда-нибудь)");
    }

    private static void demoAggregation() {
        System.out.println("\n========= 2. Агрегация: Game использует внешний Field =========");
        field sharedField = new field(10, 10, 15);

        {
            game Game = new game(sharedField);
            Game.start();
            System.out.println("Игра создана: поле " + Game.getField().getRows() + "x" + Game.getField().getCols());
            Game.makeMove(2, 2, false);
            Game.makeMove(3, 3, true);
        }
        System.out.println("\n--- После выхода из блока game поле всё ещё работает: ---");
        System.out.println("Размеры поля: " + sharedField.getRows() + "x" + sharedField.getCols());
        System.out.println("Количество мин: " + sharedField.getMineCount());
    }

    private static void demoRuleCheck() {
        System.out.println("\n========= 3. Проверка правила =========");
        field badField = new field(3, 3, 999);
        System.out.println("Итоговое поле: " + badField);
    }

    private static void demoReferencesAndCopies() {
        System.out.println("========= 4. Ссылки и копии =========");
        field Field = new field(5, 5, 3);
        Field.placeMines();
        Field.calculateNeighborMines();

        Cell cellA = Field.getCell(1, 1);
        Cell cellB = cellA;
        System.out.println("cellA == cellB: " + (cellA == cellB) + "  (это ОДИН объект в памяти)");
        System.out.println("cellA до изменения: " + cellA);
        cellB.setFlag();

        System.out.println("cellA после cellB.setFlag(): " + cellA + "  ← изменился, т.к. это тот же объект");
        Cell cellC = Field.getCell(2, 2);
        System.out.println("cellA == cellC: " + (cellA == cellC) + "  (это РАЗНЫЕ объекты)");
        System.out.println("cellA.equals(cellC): " + cellA.equals(cellC) + "  (equals по умолчанию сравнивает ссылки)\n");
    }
    private static void demoAutoCloseable() {
        System.out.println("\n========= 5. AutoCloseable / try-with-resources =========");
        IssueLog newlog;
        try (IssueLog log = new IssueLog("Партия #1")) {
            newlog = log;
            log.write("Игра началась");
            log.write("Размещены мины");
            log.write("Игрок сделал ход");
            System.out.println("    Внутри блока try — журнал ещё открыт");
        }
        System.out.println("После блока try — журнал закрыт (close() вызван автоматически)");
    }

    private static void demoGarbageCollector() {
        System.out.println("\n========= 6. Сборщик мусора =========");

        WeakReference<Cell> watcher = createTemporaryCell();

        System.out.println("После выхода из createTemporaryCell: объект жив? " + (watcher.get() != null));
        System.out.println("(Локальная переменная temp уже вне области видимости,");
        System.out.println(" но GC её ещё не собрал — момент неизвестен)");

        for (int i = 0; i < 3; i++) {
            System.gc();
            try {
                Thread.sleep(50);
            } catch (InterruptedException ignored) {
            }
        }

        boolean alive = watcher.get() != null;
        System.out.println("После System.gc(): объект жив? " + alive);
        if (alive) {
            System.out.println("(GC не собрал объект — момент не определён)");
        } else {
            System.out.println("(GC собрал объект)");
        }
    }

    private static WeakReference<Cell> createTemporaryCell() {
        field tempField = new field(1, 1, 0);
        Cell temp = tempField.getCell(0, 0);
        System.out.println("Создана временная клетка: " + temp);
        return new WeakReference<>(temp);
    }
}