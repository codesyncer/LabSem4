public class Main {

    public static void main(String[] args) {
        Allocator allocator = new LinkedAllocator(100, 10);
        Process pro1 = allocator.alloc("p1", 25);
        Process pro2 = allocator.alloc("p2", 18);
        allocator.dealloc(pro1);
        Process pro3 = allocator.alloc("p3", 50);
        allocator.alloc("p4", 30);
//        allocator.dealloc(pro3);
        System.out.println(allocator);
    }
}
