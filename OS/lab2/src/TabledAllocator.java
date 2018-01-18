public class TabledAllocator implements Allocator {
    private int frameSize, nFrames, allocFrames;
    Frame[] frames;

    TabledAllocator(int total, int pSize) {
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

    public String toString() {
        StringBuilder fig = new StringBuilder();
        for (int i = 0; i < nFrames; ++i) {
            if (frames[i] == null)
                fig.append("| -- ");
            else
                fig.append(String.format("| %s,%d ", frames[i].pro.getName(), frames[i].whichFrame));
        }
        if (fig.length() != 0)
            fig.append("|");
        return fig.toString();
    }
}
