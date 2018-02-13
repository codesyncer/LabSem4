import java.util.HashMap;

public class TabledAllocator extends Allocator {
    private HashMap<String, Frame> frameTable = new HashMap<>();

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
        Frame frame;
        int loc = 0, count = 0;
        while (size > 0) {
            while (loc < nFrames && frames[loc] != null)
                loc++;
            if (loc < nFrames) {
                frame = new Frame(pro, count++, loc);
                frameTable.put(pro.getName() + frame.whichFrame, frame);
                frames[loc] = frame;
                allocFrames++;
            }
            size -= frameSize;
        }
        return pro;
    }

    public void dealloc(Process pro) {
        int whichFrame = 0;
        Frame frame = frameTable.remove(pro.getName() + whichFrame);
        while (frame != null) {
            frames[frame.frameIndex] = null;
            allocFrames--;
            whichFrame++;
            frame = frameTable.remove(pro.getName() + whichFrame);
        }
    }

}
