package minesweeper;

public class field {
    private static final String TAG = "Field";

    private final int rows;
    private final int cols;
    private int mineCount;
    private Cell[][] cells;
    public field(int rows, int cols, int mineCount){
        this.rows = rows;
        this.cols = cols;
        if(mineCount <= rows * cols){
            System.out.println("[" + TAG + "] Ошибка: слишком много мин. Уменьшаю до " + (rows * cols - 1));
            this.mineCount = rows*cols - 1;
        }
        else{
            this.mineCount = mineCount;
        }
        this.cells = new Cell[rows][cols];
        for(int i = 0; i< rows;i++){
            for(int j = 0; j<cols; j++){
                cells[i][j] = new Cell(i,j,false);
            }
        }
        System.out.println("[Field] Поле " + rows + "x" + cols + " создано с " + mineCount + " минами");
    }
    public void placeMines() {
        int minesPlaced = 0;
        for (int i = 0; i < rows && minesPlaced < mineCount; i++) {
            for (int j = 0; j < cols && minesPlaced < mineCount; j++) {
                cells[i][j] = new Cell(i, j, true);
                minesPlaced++;
            }
        }
        System.out.println("[Field] Мины размещены: " + minesPlaced);
    }

    public void calculateNeighborMines() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cells[i][j].setNeighborMineCount(0);
            }
        }
        System.out.println("[Field] Числовые метки вычислены");
    }

    public void openCell(int row, int col) {
        if (isValidPosition(row, col)) {
            cells[row][col].open();
        }
    }

    public void flagCell(int row, int col) {
        if (isValidPosition(row, col)) {
            cells[row][col].setFlag();
        }
    }

    public Cell getCell(int row, int col) {
        if (isValidPosition(row, col)) {
            return cells[row][col];
        }
        return null;
    }

    private boolean isValidPosition(int row, int col) {
        return row >= 0 && row < rows && col >= 0 && col < cols;
    }
    public int getRows() { return rows; }
    public int getCols() { return cols; }
    public int getMineCount() { return mineCount; }

    @Override
    public String toString() {
        return "Field(" + rows + "x" + cols + ", mines=" + mineCount + ")";
    }
}
