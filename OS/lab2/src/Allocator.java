public abstract class Allocator {
    int frameSize, nFrames, allocFrames;
    Frame[] frames;

    abstract Process alloc(String name, int size);

    abstract void dealloc(Process pro);

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
