package minesweeper;

public class game {
    private static final String TAG = "Game";
    private field Field;
    private boolean gameOver;
    private boolean victory;

    public game(field field) {
        this.Field = field;
        this.gameOver = false;
        this.victory = false;
        System.out.println("[Game] Игра создана, использует внешнее поле " +
                field.getRows() + "x" + field.getCols());
    }

    public void start() {
        System.out.println("[Game] Начинаем игру!");
        Field.placeMines();
        Field.calculateNeighborMines();
    }

    public void makeMove(int row, int col, boolean setFlag) {
        if (gameOver) {
            System.out.println("[" + TAG + "] Ошибка: игра уже завершена");
            return;
        }

        if (setFlag) {
            Field.flagCell(row, col);
        } else {
            Field.openCell(row, col);
            Cell cell = Field.getCell(row, col);
            if (cell != null && cell.hasMine()) {
                gameOver = true;
                System.out.println("[" + TAG + "] Поражение! Вы наступили на мину!");
            }
        }

        checkVictory();
    }

    private void checkVictory() {
        System.out.println("[" + TAG + "] Проверка победы...");
    }

    public boolean isGameOver() { return gameOver; }
    public boolean isVictory() { return victory; }
    public field getField() { return Field; }


}
