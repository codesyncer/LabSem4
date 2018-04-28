public class Main {

    public static void main(String[] args) {
        Allocator allocator1 = new TabledAllocator(100, 10);
        test(allocator1);
        System.out.println(allocator1);
        Allocator allocator2 = new LinkedAllocator(100, 10);
        test(allocator2);
        System.out.println(allocator2);
    }

    private static void test(Allocator allocator) {
        Process pro1 = allocator.alloc("p1", 25);
        Process pro2 = allocator.alloc("p2", 18);
        allocator.dealloc(pro1);
        Process pro3 = allocator.alloc("p3", 50);
        allocator.alloc("p4", 30);
        allocator.dealloc(pro3);
    }
}
