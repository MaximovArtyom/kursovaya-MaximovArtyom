package minesweeper;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class ClassicGame extends BaseGame {
    private int selectedFieldIndex;

    private static final List<int[]> presetFields = new ArrayList<>();

    static {
        presetFields.add(new int[]{8, 8});      // Новичок
        presetFields.add(new int[]{15, 15});    // Любитель
        presetFields.add(new int[]{18, 30});    // Профессионал
        presetFields.add(new int[]{20, 40});    // Эксперт
    }

    public ClassicGame(Field field, int selectedFieldIndex) {
        super(field, "Classic");
        this.selectedFieldIndex = selectedFieldIndex;
        System.out.println("[ClassicGame] Создана классическая игра, выбрано поле #" + selectedFieldIndex);
    }

    public ClassicGame(ClassicGame other) {
        super(other);
        this.selectedFieldIndex = other.selectedFieldIndex;
        System.out.println("[ClassicGame] Скопирована классическая игра");
    }

    @Override
    public void start() {
        System.out.println("[ClassicGame] Начало классической игры на поле #" + selectedFieldIndex);
        field.placeMines();
        field.calculateNeighborMines();
        gameOver = false;
        victory = false;
    }

    @Override
    public void makeMove(int row, int col, boolean setFlag) {
        if (gameOver) {
            System.out.println("[ClassicGame] Ошибка: игра уже завершена");
            return;
        }

        if (setFlag) {
            field.flagCell(row, col);
        } else {
            field.openCell(row, col);
            if (field.getCell(row, col).hasMine()) {
                gameOver = true;
                victory = false;
                System.out.println("[ClassicGame] Поражение! Подорвались на мине!");
                return;
            }
        }

        checkVictory();
    }

    @Override
    public boolean checkVictory() {
        return victory;
    }

    @Override
    public String describe() {
        return "Классический режим, поле #" + selectedFieldIndex + " (" + field.getRows() + "x" + field.getCols() + ", мин: " + field.getMineCount() + ")";
    }

    @Override
    public BaseGame clone() {
        return new ClassicGame(this);
    }


    public int getSelectedFieldIndex() { return selectedFieldIndex; }

}