def solve(ints):
    class Interval:
        sort_by_start = None

        def __init__(self, start, end):
            self.start, self.end = start, end
            self.discarded = False

        def __lt__(self, other):
            return self.start < other.start if Interval.sort_by_start else self.end < other.end

    intervals = [Interval(x, y) for x, y in ints]
    Interval.sort_by_start = False
    end_sorted = sorted(intervals)
    Interval.sort_by_start = True
    start_sorted, start_start = sorted(intervals), 0
    discard_state = False
    ret = []
    for interval in end_sorted:
        if discard_state == interval.discarded:
            ret.append((interval.start, interval.end))
            while start_start < len(start_sorted) and start_sorted[start_start].start < interval.end:
                start_sorted[start_start].discarded = True
                start_start += 1
    return ret


def main():
    ints = [(1, 3),
            (1, 6),
            (1, 3),
            (4, 6),
            (4, 10),
            (8, 12),
            (8, 12),
            (11, 15),
            (13, 15),
            (13, 15)]
    print(solve(ints))


if __name__ == '__main__':
    main()
