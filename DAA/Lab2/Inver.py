def naive(arr):
    n = len(arr)
    count = 0
    for i in range(n - 1):
        for j in range(i + 1, n):
            if arr[i] > arr[j]:
                count += 1
    return count


def solve(arr, low, high):
    pass


if __name__ == '__main__':
    seq = [int(num) for num in input("Sequence: ").split()]
    print(naive(seq))
