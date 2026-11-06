package minesweeper;

public class Cell {
    private static final String TAG = "Cell";
    private final int row;
    private final int col;
    private final boolean hasMine;

    private CellState state;
    private int neighborMineCount;

    public Cell(int row, int col, boolean hasMine) {
        this.row = row;
        this.col = col;
        this.hasMine = hasMine;
        this.state = CellState.CLOSED;

        System.out.println("Cell(" + row + "," + col + ") создан");
    }
    public void open() {
        if (state == CellState.FLAGGED) {
            System.out.println("[" + TAG + "] Ошибка: нельзя открыть клетку с флагом");
            return;
        }
        if (state == CellState.OPENED) {
            System.out.println("[" + TAG + "] Клетка уже открыта");
            return;
        }

        state = CellState.OPENED;

        System.out.print("[" + TAG + "] Клетка(" + row + "," + col + ") открыта");

        if (hasMine) {
            System.out.println(" — БУМ! Мина!");
        } else {
            System.out.println(", соседних мин: " + neighborMineCount);
        }
    }

    public void setFlag() {
        if (state == CellState.OPENED) {
            System.out.println("[" + TAG + "] Ошибка: нельзя поставить флаг на открытую клетку");
            return;
        }
        state = CellState.FLAGGED;
        System.out.println("[" + TAG + "] Флаг поставлен на клетку(" + row + "," + col + ")");
    }

    public void removeFlag() {
        if (state == CellState.FLAGGED) {
            state = CellState.CLOSED;
            System.out.println("[" + TAG + "] Флаг снят с клетки(" + row + "," + col + ")");
        }
    }

    public void setNeighborMineCount(int count) {
        if (count < 0 || count > 8) {
            System.out.println("[" + TAG + "] Ошибка: число соседних мин должно быть от 0 до 8");
            return;
        }
        this.neighborMineCount = count;
    }

    public int getRow() {
        return row;
    }

    public int getCol() {
        return col;
    }

    public boolean hasMine() {
        return hasMine;
    }

    public CellState getState() {
        return state;
    }

    public int getNeighborMineCount() {
        return neighborMineCount;
    }

    @Override
    public String toString() {
        return "Cell(" + row + "," + col + ", state=" + state + ", mine=" + hasMine + ", neighbors=" + neighborMineCount + ")";
    }
}

