package minesweeper;

import java.util.Objects;

public final class AdventureGame extends BaseGame {
    private int level;
    private int timeLimit;
    private int timeRemaining;

    public AdventureGame(Field field, int level, int timeLimit) {
        super(field, "Adventure");
        this.level = level;
        this.timeLimit = timeLimit;
        this.timeRemaining = timeLimit;
        System.out.println("[AdventureGame] Создана приключенческая игра, уровень " + level + ", лимит: " + timeLimit + " ходов");
    }

    public AdventureGame(AdventureGame other) {
        super(other);
        this.level = other.level;
        this.timeLimit = other.timeLimit;
        this.timeRemaining = other.timeRemaining;
        this.field = new Field(other.field.getRows(), other.field.getCols(), other.field.getMineCount());
        System.out.println("[AdventureGame] Скопирована приключенческая игра (глубокая копия)");
    }

    @Override
    public void start() {
        System.out.println("[AdventureGame] Начало уровня " + level + ", у вас " + timeLimit + " ходов");
        field.placeMines();
        field.calculateNeighborMines();
        gameOver = false;
        victory = false;
        timeRemaining = timeLimit;
    }

    @Override
    public void makeMove(int row, int col, boolean setFlag) {
        if (gameOver) {
            System.out.println("[AdventureGame] Ошибка: игра уже завершена");
            return;
        }
        if (setFlag) {
            field.flagCell(row, col);
        } else {
            field.openCell(row, col);
            if (field.getCell(row, col).hasMine()) {
                gameOver = true;
                victory = false;
                System.out.println("[AdventureGame] Поражение! Подорвались на мине!");
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
        return super.header() + ", уровень " + level + ", лимит: " + timeLimit + " ходов" + ", осталось: " + timeRemaining + " ходов";
    }

    @Override
    public BaseGame clone() {
        return new AdventureGame(this);
    }

    public int getLevel() { return level; }
    public int getTimeLimit() { return timeLimit; }

}