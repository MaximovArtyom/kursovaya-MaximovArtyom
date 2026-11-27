package minesweeper;

import java.util.Objects;

public abstract class BaseGame {

    private static int gameCounter = 0;
    public static final int MAX_LEVEL = 10;
    protected Field field;
    protected boolean gameOver;
    protected boolean victory;

    private final int gameNumber;
    private final String title;

    public BaseGame(Field field, String title) {
        this.field = field;
        this.title = title;
        this.gameOver = false;
        this.victory = false;
        this.gameNumber = nextGameNumber();
        System.out.println("[BaseGame] Создана базовая игра №" + gameNumber + ": " + title);
    }

    protected BaseGame(BaseGame other) {
        this.field = other.field;
        this.title = other.title;
        this.gameOver = other.gameOver;
        this.victory = other.victory;
        this.gameNumber = nextGameNumber();
        System.out.println("[BaseGame] Скопирована базовая игра");
    }

    public static int nextGameNumber() {
        return ++gameCounter;
    }

    public static int getGameCount() {
        return gameCounter;
    }


    public abstract boolean checkVictory();
    public abstract void start();
    public abstract void makeMove(int row, int col, boolean setFlag);
    public abstract String describe();
    public abstract BaseGame clone();

    public String getStatus() {
        if (victory) return "Победа!";
        if (gameOver) return "Поражение!";
        return "Игра продолжается";
    }

    protected String header() {
        return "Поле: " + field.getRows() + "x" + field.getCols() + ", мин: " + field.getMineCount();
    }

    public boolean isGameOver() { return gameOver; }
    public boolean isVictory() { return victory; }
    public Field getField() { return field; }
    public String getTitle() { return title; }

    public BaseGame Save(BaseGame other) {
        System.out.println("[this]"+ "Игра" + this.getTitle()+  " передана в архив");
        return this;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;  // сравнение ссылок
        if (!(o instanceof BaseGame other)) return false;
        return gameNumber == other.gameNumber && Objects.equals(title, other.title);
    }

    @Override
    public int hashCode() {
        return Objects.hash(gameNumber, title);
    }

    @Override
    public String toString() {
        return describe();
    }
}