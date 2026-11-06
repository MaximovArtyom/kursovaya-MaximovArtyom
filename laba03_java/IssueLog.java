package minesweeper;

public class IssueLog implements AutoCloseable{
    private final String title;

    public IssueLog(String title){
        this.title = title;
        System.out.println("[+] журнал открыт: " + title);
    }
    public void write(String line) {
        System.out.println("    " + line);
    }
    @Override
    public void close() {
        System.out.println("[-] журнал закрыт: " + title);
    }
}

