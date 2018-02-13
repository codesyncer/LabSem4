class Frame {
    int frameIndex, whichFrame;
    Process pro;
    private Frame next;

    Frame(Process pro, int whichFrame, int frameIndex) {
        this.pro = pro;
        this.whichFrame = whichFrame;
        this.frameIndex = frameIndex;
    }

    void setNext(Frame next) {
        this.next = next;
    }

    public Frame getNext() {
        return next;
    }
}

public class LinkedAllocator extends Allocator {

    LinkedAllocator(int total, int pSize) {
        frameSize = pSize;
        nFrames = total / frameSize;
        frames = new Frame[nFrames];
        allocFrames = 0;
    }


    public Process alloc(String name, int size) {
        if (allocFrames + (size % frameSize == 0 ? size / frameSize : size / frameSize + 1) > nFrames)
            return null;
        Process pro = new Process(name, size);
        Frame prev = null, frame;
        int loc = 0, count = 0;
        while (size > 0) {
            while (loc < nFrames && frames[loc] != null)
                loc++;
            if (loc < nFrames) {
                frame = new Frame(pro, count++, loc);
                frames[loc] = frame;
                if (prev != null)
                    prev.setNext(frame);
                else
                    pro.setHead(frames[loc]);
                prev = frame;
                allocFrames++;
            }
            size -= frameSize;
        }
        return pro;
    }

    public void dealloc(Process pro) {
        Frame frame = pro.getHead(), prev = null;
        while (frame != null) {
            frames[frame.frameIndex] = null;
            if (prev != null)
                prev.setNext(null);
            prev = frame;
            frame = frame.getNext();
            allocFrames--;
        }
        pro.setHead(null);
    }
}
