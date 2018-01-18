public interface Allocator {
    Process alloc(String name, int size);

    void dealloc(Process pro);
}
