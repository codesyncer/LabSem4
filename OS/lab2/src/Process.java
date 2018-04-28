public class Process {
    private int size;
    private String name;
    private Frame head;

    Process(String name, int size) {
        this.size = size;
        this.name = name;
    }

    void setHead(Frame head) {
        this.head = head;
    }

    String getName() {
        return name;
    }

    public Frame getHead() {
        return head;
    }
}